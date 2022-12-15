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
	sem_t	*sem;
	sem_t	*detach;
	sem_t	*print;
	//sem_t	*dead;
	t_input	*input;
	////////dummy//////////
	pthread_t	th;
	pid_t	child_die;
	pid_t	*id;
	pid_t	*child_id;
	pid_t	parent;
	//////////////
	//int	no;
	int	n_meal;
	int	*is_eat;
	////////dummy//////////
	int	count;
	////////dummy//////////
	unsigned long	lastmeal;
}	t_philo;


//philo.c
void	ft_display(t_philo *ph, unsigned long timestamp, char *s);
void	*routine(void *arg);
int	ft_atoi(const char *str);
//init.c
void	input_init(t_input *param, int n, char **argv);
void	struct_init(t_input *param, t_philo *ph);
//mutex.c
//void	detach_all_thread(pthread_t *th, t_philo *ph);
void	create_and_detach(pthread_t *th, t_philo *ph);
//action.c
int	can_eat(t_philo *ph);
void	ft_eat(t_philo *ph);
void	ft_sleep(t_philo *ph);
//time.c
unsigned long	current_time(void);
unsigned long	timestamp(t_philo *ph);
//sem.c
 void	init_semaphore(t_philo *ph);
//clear.c
void    destroy_mutex(pthread_t *th, t_philo *ph);
void	ft_clear(t_philo *ph);
void	ft_error(t_philo *ph, char *s);
#endif
