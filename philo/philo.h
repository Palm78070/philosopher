/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 00:52:01 by rthammat          #+#    #+#             */
/*   Updated: 2022/12/18 21:36:57 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define LLONG_MAX 9223372036854775807

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>

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
	pthread_mutex_t	*fork;
	pthread_mutex_t	*display;
	t_input			*input;
	int				no;
	int				n_meal;
	int				*count_eat;
	int				*finish;
	int				*is_eat;
	unsigned long	lastmeal;
}	t_philo;

//philo.c
void					ft_display(t_philo *ph, \
						unsigned long timestamp, char *s);
void					*routine(void *arg);
int						ft_atoi(const char *str);
//init.c
void					input_init(t_input *param, \
						int n, char **argv);
void					check_struct(t_input *param, \
						pthread_t *th, t_philo *ph);
void					ft_mutex_init(t_input *param, \
						pthread_t *th, t_philo *ph);
//mutex.c
void					create_and_join(pthread_t *th, t_philo *ph);
//void	check_dead(t_philo *ph);
//action.c
int						can_eat(t_philo *ph);
void					ft_eat(t_philo *ph);
void					ft_sleep(t_philo *ph);
//time.c
void					super_sleep(int ms);
unsigned long			current_time(void);
unsigned long			timestamp(t_philo *ph);
//utils.c
int						ft_isdigit(char c);
void					check_input(int argc, char **argv);
//clear.c
void					destroy_mutex(pthread_t *th, t_philo *ph);
void					ft_clear(pthread_t *th, t_philo *ph);
void					ft_error(pthread_t *th, t_philo *ph, char *s);
#endif
