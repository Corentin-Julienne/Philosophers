/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:48:50 by cjulienn          #+#    #+#             */
/*   Updated: 2022/08/23 00:18:15 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	sim_out(t_sim *sim, int i, int type)
{
	if (type == DEAD)
		display_msg(sim->philos[i].id, DEAD, sim);
	else
		display_msg(1, VICTORY, sim);
}

static int	check_victory_condition(t_sim *sim)
{
	pthread_mutex_lock(&sim->add_meal_count);
	if (sim->time_eaten == sim->nb_philo)
	{
		pthread_mutex_unlock(&sim->add_meal_count);
		sim_out(sim, -1, VICTORY);
		return (1);
	}
	pthread_mutex_unlock(&sim->add_meal_count);
	return (0);
}

static void	wait_for_endgame(t_sim *sim, int i)
{
	long long		last_eat_cpy;

	while (42)
	{
		i = 0;
		while (i < sim->nb_philo)
		{
			pthread_mutex_lock(&sim->check_phi_eat);
			last_eat_cpy = sim->philos[i].last_eat;
			pthread_mutex_unlock(&sim->check_phi_eat);
			if (get_time_now() >= last_eat_cpy + sim->tt_die
				&& last_eat_cpy != -1)
			{
				sim_out(sim, i, DEAD);
				return ;
			}
			i++;
		}
		if (check_victory_condition(sim) != 0)
			return ;
		usleep(1000);
	}
}

/* create phi structs :
=> init all threads using pthread_create
=> put sim->phis_init = 1 (allow simulation to start)
=> use wait_for_endgame func to wait until end of sim
=> join threads
=> launch clean_program to suppress leaks and exit */

static int	init_philos_threads(t_sim *sim)
{
	int					i;

	i = 0;
	while (i < sim->nb_philo)
	{
		pthread_create(&sim->philos[i].thread_id, NULL,
			&philo_routine, (void *)&sim->philos[i]);
		i++;
	}
	pthread_mutex_lock(&sim->check_start);
	sim->start_sim = get_time_now();
	pthread_mutex_unlock(&sim->check_start);
	wait_for_endgame(sim, 0);
	i = 0;
	while (i < sim->nb_philo)
	{
		pthread_join(sim->philos[i].thread_id, NULL);
		i++;
	}
	clean_program(sim, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	int			valid;
	int			struct_status;
	t_sim		*sim;

	if (argc != 6 && argc != 5)
		return (display_error_msg(ARG_ERR));
	valid = check_args_validity(argc, argv);
	if (valid == 0)
		return (display_error_msg(INVAL_ERR));
	sim = (t_sim *)malloc(sizeof(t_sim));
	if (!sim)
		return (display_error_msg(MALLOC_ERR));
	struct_status = init_sim_struct(sim, argv, argc);
	if (struct_status)
	{
		clean_program(sim, struct_status);
		return (1);
	}
	return (init_philos_threads(sim));
}
