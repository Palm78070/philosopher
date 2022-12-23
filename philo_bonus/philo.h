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
# include <signal.h>

typedef struct s_input
{
	int	n_phi;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_eat;
	unsigned long	start_time;
}	t_input;

typedef struct s_philo
{
	sem_t	*fork;
	sem_t	*detach;
	sem_t	*print;
	t_input	*input;
	////////dummy//////////
	pthread_t	*th;
	pid_t	child_die;
	pid_t	*id;
	pid_t	*child_id;
	int	sem_value;
	//////////////
	int	no;
	int	n_meal;
	int	*is_eat;
	int	*finish;
	unsigned long	lastmeal;
}	t_philo;


//philo.c
void	ft_display(t_philo *ph, unsigned long timestamp, char *s);
void	*routine(void *arg);
int	ft_atoi(const char *str);
//init.c
void	input_init(t_input *param, int n, char **argv);
 void	init_semaphore(t_philo *ph);
void	struct_init(t_input *param, t_philo *ph);
//check_dead.c
int	is_dead(t_philo *ph);
void	sem_post_all_detach(t_philo *ph);
void	*check_dead(void *arg);
//action.c
int	can_eat(t_philo *ph);
void	ft_eat(t_philo *ph);
void	ft_sleep(t_philo *ph);
//time.c
void	super_sleep(int ms);
unsigned long	current_time(void);
unsigned long	timestamp(t_philo *ph);
//clear.c
void    destroy_mutex(pthread_t *th, t_philo *ph);
void	ft_clear(t_philo *ph);
void	ft_error(t_philo *ph, char *s);
#endif
