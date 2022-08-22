/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:48:46 by cjulienn          #+#    #+#             */
/*   Updated: 2022/08/22 22:59:47 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	display_error_msg(const char *err_specific)
{
	printf("%s", err_specific);
	return (1);
}

static char	*select_msg(int msg_type)
{
	char	*msg;

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
	return (msg);
}

static void	print_msg(int id, int msg_type, t_sim *sim)
{
	int				endgame_cpy;
	char			*msg;
	long long		time;

	if (msg_type != DEAD && msg_type != VICTORY)
	{
		pthread_mutex_lock(&sim->check_endgame);
		endgame_cpy = sim->endgame;
		pthread_mutex_unlock(&sim->check_endgame);
		if (endgame_cpy != 0)
			return ;
	}
	msg = select_msg(msg_type);
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
	pthread_mutex_lock(&sim->write_msg);
	if (msg_type == DEAD || msg_type == VICTORY)
	{
		pthread_mutex_lock(&sim->check_endgame);
		sim->endgame++;
		pthread_mutex_unlock(&sim->check_endgame);
		if (msg_type == DEAD)
			print_msg(id, msg_type, sim);
		pthread_mutex_unlock(&sim->write_msg);
		return (1);
	}
	return (handle_std_case(id, msg_type, sim));
}
