/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:49:12 by cjulienn          #+#    #+#             */
/*   Updated: 2022/08/20 16:56:50 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define THINKING		0
# define EATING			1
# define SLEEPING		2
# define DEAD			3
# define FORK			4
# define VICTORY		5

# define MALLOC_ERR		"Philosophers: Error: Unsuccesful memory allocation\n"
# define ARG_ERR		"Philosophers: Error: Wrong number of arguments\n"
# define INVAL_ERR		"Philosophers: Error: Invalid argument format\n"

typedef struct s_sim
{
	int					nb_philo;
	int					tt_die;
	int					tt_eat;
	int					tt_sleep;
	int					win_cond;
	int					time_eaten;
	int					endgame;
	long long			start_sim;
	struct s_philo		*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_msg;
	pthread_mutex_t		add_meal_count;
	pthread_mutex_t		check_endgame;
	pthread_mutex_t		check_phi_eat;
	pthread_mutex_t		check_start;
}						t_sim;

typedef struct s_philo
{
	int					id;
	int					meal_num;
	long long			last_eat;
	int					right_fork_id;
	int					left_fork_id;
	pthread_t			thread_id;
	t_sim				*sim;
}						t_philo;

/* actions.c */
int					eat_sleep_think_pattern(t_philo *philo);
/* check_args.c */
int					check_args_validity(int argc, char **argv);
/* free.c */
void				clean_program(t_sim *sim, int code);
/* init_structs.c */
int					init_sim_struct(t_sim *sim, char **argv, int argc);
/* msgs.c */
int					display_error_msg(const char *err_specific);
int					display_msg(int id, int msg_type, t_sim *sim);
/* routines */
void				*philo_routine(void *arg);
/* time.c */
int					is_dead(long long last_eat, long long tt_die);
int					custom_usleep(long long time, t_sim *sim);
long long			get_time_now(void);
void				custom_micro_usleep(long long time);
/* utils.c */
size_t				ft_strlen(const char *s);
long long			calc_res(const char *str);

#endif
