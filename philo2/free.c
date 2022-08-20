/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:48:48 by cjulienn          #+#    #+#             */
/*   Updated: 2022/08/06 16:14:51 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	mutexes_elimination(t_sim *sim, int code)
{
	if (code != 2)
	{
		pthread_mutex_destroy(&sim->add_meal_count);
		pthread_mutex_destroy(&sim->write_msg);
		pthread_mutex_destroy(&sim->check_endgame);
	}
	if (code != 2 && code != 3)
	{
		pthread_mutex_destroy(&sim->check_start);
		pthread_mutex_destroy(&sim->check_phi_eat);
	}
}

void	clean_program(t_sim *sim, int code)
{
	int			i;

	mutexes_elimination(sim, code);
	if (sim->forks)
	{
		i = 0;
		while (i < sim->nb_philo)
		{
			pthread_mutex_destroy(&sim->forks[i]);
			i++;
		}
		free(sim->forks);
		sim->forks = NULL;
	}
	if (sim->philos)
	{
		free(sim->philos);
		sim->philos = NULL;
	}
	free(sim);
}
