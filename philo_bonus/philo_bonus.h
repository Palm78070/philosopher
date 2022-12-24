/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:50:03 by rthammat          #+#    #+#             */
/*   Updated: 2022/12/24 21:19:07 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define LLONG_MAX 9223372036854775807

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_input
{
	int				n_phi;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	unsigned long	start_time;
}	t_input;

typedef struct s_philo
{
	int				no;
	int				n_meal;
	int				*is_eat;
	int				*finish;
	unsigned long	lastmeal;
	sem_t			*fork;
	sem_t			*detach;
	sem_t			*print;
	sem_t			*dead;
	t_input			*input;
	pthread_t		*th;
	pid_t			*id;
	pid_t			*child_id;
}	t_philo;

//philo.c
void				ft_display(t_philo *ph, unsigned long timestamp, char *s);
void				*routine(void *arg);
//utils.c
int					ft_atoi(const char *str);
void				check_input(int argc, char **argv);
//init.c
void				input_init(t_input *param, int n, char **argv);
void				init_semaphore(t_philo *ph);
void				struct_init(t_input *param, t_philo *ph);
//check_dead.c
int					is_dead(t_philo *ph);
void				sem_post_all_detach(t_philo *ph);
void				*check_dead(void *arg);
void				*ft_dead(void *arg);
//action.c
void				ft_display(t_philo *ph, unsigned long timestamp, char *s);
void				ft_eat(t_philo *ph);
void				*routine(void *arg);
//clear.c
void				destroy_mutex(pthread_t *th, t_philo *ph);
void				ft_clear(t_philo *ph);
void				ft_error(t_philo *ph, char *s);
//time.c
void				super_sleep(int ms);
unsigned long		current_time(void);
unsigned long		timestamp(t_philo *ph);
//process.c
int					is_child(t_philo *ph);
void				ft_child(t_philo *ph);
void				ft_parent(t_philo *ph);
void				fork_process(t_philo *ph);
#endif
