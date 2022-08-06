/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:00:25 by cjulienn          #+#    #+#             */
/*   Updated: 2022/08/06 16:59:53 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* in case of the sim stopping, release forks to avoid deadlocks
and allows phis routine to stop */

static int	release_fork_case_endsim(t_philo *philo)
{
	pthread_mutex_unlock(&philo->sim->forks[philo->right_fork_id]);
	pthread_mutex_unlock(&philo->sim->forks[philo->left_fork_id]);
	return (1);
}

/* die_alone is used when there is only one philosopher
there is also one fork so philo cannot eat,
so he is starving to death. Sad. */

static int	die_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->forks[philo->right_fork_id]);
	display_msg(philo->id, FORK, philo->sim);
	while (is_dead(philo->last_eat, philo->sim->tt_die) == 0)
		usleep(50);
	pthread_mutex_unlock(&philo->sim->forks[philo->right_fork_id]);
	return (1);
}

/* use when a philosopher wanna eat 
=> lock both forks/mutexes
=> display msg "has taken a fork"
=> update phi->last_eat 
=> realease forks if display msg problem */

static int	request_forks(t_philo *philo)
{
	int		is_sim_over;

	pthread_mutex_lock(&philo->sim->check_endgame);
	is_sim_over = philo->sim->endgame;
	pthread_mutex_unlock(&philo->sim->check_endgame);
	if (!is_sim_over)
	{
		pthread_mutex_lock(&philo->sim->forks[philo->left_fork_id]);
		display_msg(philo->id, FORK, philo->sim);
		pthread_mutex_lock(&philo->sim->forks[philo->right_fork_id]);
		display_msg(philo->id, FORK, philo->sim);
	}
	else
		return (1);
	display_msg(philo->id, EATING, philo->sim);
	return (0);
}

static int	eating_process(t_philo *philo)
{
	if (request_forks(philo) != 0)
		return (1);
	pthread_mutex_lock(&philo->sim->check_phi_eat);
	philo->last_eat = get_time_now();
	pthread_mutex_unlock(&philo->sim->check_phi_eat);
	if (custom_usleep(philo->sim->tt_eat, philo->sim) == 1)
		return (release_fork_case_endsim(philo));
	philo->meal_num++;
	pthread_mutex_unlock(&philo->sim->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->sim->forks[philo->right_fork_id]);
	if (philo->meal_num == philo->sim->win_cond)
	{
		pthread_mutex_lock(&philo->sim->add_meal_count);
		philo->sim->time_eaten++;
		pthread_mutex_unlock(&philo->sim->add_meal_count);
	}
	return (0);
}

/* in the eat/sleep procedure, a philo will :
1) request forks 
2) eat
3) add the total meal absorbed
4) release forks
5) go to sleep and print sleeping msg
6) wait while sleeping
7) go thinking and print thinking msg */

int	eat_sleep_think_pattern(t_philo *philo)
{
	if (philo->sim->nb_philo == 1)
		return (die_alone(philo));
	if (eating_process(philo) == 1)
		return (1);
	display_msg(philo->id, SLEEPING, philo->sim);
	if (custom_usleep(philo->sim->tt_sleep, philo->sim) == 1)
		return (1);
	display_msg(philo->id, THINKING, philo->sim);
	return (0);
}
