/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 23:10:32 by cjulienn          #+#    #+#             */
/*   Updated: 2022/08/22 23:23:19 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* add some fork algos to check wether you need to pick a right
fork the left fork or the opposite */

/* this function is used in order to prevent all philosophers
to take the right forks in the same time and
then causing a deadlock  */

void	anti_deadlock_algo(t_philo *philo)
{
	if (philo->sim->nb_philo % 2 != 0)
	{
		if (philo->sim->nb_philo == 1)
			return ;
		if ((philo->id - 1) == philo->sim->nb_philo)
		{
			if (philo->sim->tt_eat * 2 < philo->sim->tt_die)
				custom_usleep(philo->sim->tt_eat * 2, philo->sim);
			return ;
		}
		if ((philo->id - 1) % 2 != 0
			&& philo->sim->tt_eat < philo->sim->tt_die)
			custom_usleep(philo->sim->tt_eat, philo->sim);
	}
}

int	case_even(int is_sim_over, t_philo *philo)
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

int	case_odd(int is_sim_over, t_philo *philo)
{
	if (!is_sim_over)
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
