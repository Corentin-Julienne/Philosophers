/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:23:32 by cjulienn          #+#    #+#             */
/*   Updated: 2022/08/22 15:57:43 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	int				res_func;
	long long		is_started;

	philo = (t_philo *)arg;
	is_started = -1;
	while (is_started == -1)
	{
		pthread_mutex_lock(&philo->sim->check_start);
		is_started = philo->sim->start_sim;
		pthread_mutex_unlock(&philo->sim->check_start);
		usleep(50);
	}
	
	pthread_mutex_lock(&philo->sim->check_phi_eat);
	philo->last_eat = get_time_now();
	pthread_mutex_unlock(&philo->sim->check_phi_eat);
	res_func = 0;
	while (!res_func)
		res_func = eat_sleep_think_pattern(philo);
	return (NULL);
}
