/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:37:42 by cjulienn          #+#    #+#             */
/*   Updated: 2022/08/22 19:04:14 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* this part handles the fork-taking process in order to optimize 
philosophers survival and avoir deadlocks */

#include "philosophers.h"

// time_to_think = (time_to_eat * 2) - time_to_sleep)

static int case_odd(int is_sim_over, t_philo *philo) // difficult stuff there
{
	
}

static int case_even(int is_sim_over, t_philo *philo)
{
	if (!is_sim_over && (philo->id - 1) % 2 == 0)
	{
		pthread_mutex_lock(&philo->sim->forks[philo->right_fork_id]);
		display_msg(philo->id, FORK, philo->sim);
		pthread_mutex_lock(&philo->sim->forks[philo->left_fork_id]);
		display_msg(philo->id, FORK, philo->sim);
	}
	else if (!is_sim_over && (philo->id - 1) % 2 != 0)
	{
		pthread_mutex_lock(&philo->sim->forks[philo->left_fork_id]);
		display_msg(philo->id, FORK, philo->sim);
		pthread_mutex_lock(&philo->sim->forks[philo->right_fork_id]);
		display_msg(philo->id, FORK, philo->sim);
	}
	else
		return (1);
	return (0);
}

int	request_forks(t_philo *philo)
{
	int		is_sim_over;
	int		res;

	pthread_mutex_lock(&philo->sim->check_endgame);
	is_sim_over = philo->sim->endgame;
	pthread_mutex_unlock(&philo->sim->check_endgame);
	if (philo->sim->nb_philo % 2 == 0)
		res = case_even(is_sim_over, philo);
	else
		res = case_odd(is_sim_over, philo);
	if (res)
		return (1); 
	display_msg(philo->id, EATING, philo->sim);
	return (0);
}
