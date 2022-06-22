/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:48:46 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/22 13:11:42 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	display_error_msg(const char *err_specific)
{
	printf("%s", err_specific);
	return (1);
}

static void	print_msg(int id, int msg_type, t_sim *sim)
{
	char			*msg;
	long long		time;

	if (msg_type == THINKING)
		msg = "is thinking\n";
	else if (msg_type == EATING)
		msg = "is eating\n";
	else if (msg_type == SLEEPING)
		msg = "is sleeping\n";
	else if (msg_type == DEAD)
		msg = "died\n";
	else
		msg = "has taken a fork\n";
	pthread_mutex_lock(&sim->check_start);
	time = get_time_now() - sim->start_sim;
	pthread_mutex_unlock(&sim->check_start);
	printf("%lli %i %s", time, id, msg);
}

/* display msg function will print a msg for a changing state
(eat, sleep, think, dead, victory). The stop static variable,
shared by all threads,
is used as a bareer to prevent multiple philos
to win the game or die at the same time */

int	handle_std_case(int id, int msg_type, t_sim *sim)
{
	print_msg(id, msg_type, sim);
	pthread_mutex_unlock(&sim->write_msg);
	return (0);
}

int	display_msg(int id, int msg_type, t_sim *sim)
{
	static int		stop = 0;
	int				rtn;

	pthread_mutex_lock(&sim->check_static);
	if (stop != 0)
	{
		rtn = stop;
		pthread_mutex_unlock(&sim->check_static);
		return (rtn);
	}
	pthread_mutex_unlock(&sim->check_static);
	pthread_mutex_lock(&sim->write_msg);
	if (msg_type == DEAD || msg_type == VICTORY)
	{
		pthread_mutex_lock(&sim->check_static);
		stop++;
		rtn = stop;
		pthread_mutex_unlock(&sim->check_static);
		if (msg_type == DEAD)
			print_msg(id, msg_type, sim);
		pthread_mutex_unlock(&sim->write_msg);
		return (rtn);
	}
	return (handle_std_case(id, msg_type, sim));
}
