#include "philo.h"

void	input_init(t_input *param, int n, char **argv)
{
	int	i;

	i = 1;
	if (!param)
	{
		printf("Error in allocating t_input\n");
		exit(1);
	}
	param->n_phi = ft_atoi(argv[i++]);
	param->t_die = ft_atoi(argv[i++]);
	param->t_eat = ft_atoi(argv[i++]);
	param->t_sleep = ft_atoi(argv[i++]);
	if (i == n)
		param->n_eat = ft_atoi(argv[i]);
	else
		param->n_eat = 0;
	param->start_time = current_time();
}

void	check_struct(t_input *param, pthread_t *th, t_philo *ph)
{
	if (!th)
	{
		free(param);
		ft_error(th, ph, "Error in allocating struct pthread_t");
	}
	memset(th, 0, sizeof(pthread_t));
	if (!ph)
	{
		free(param);
		ft_error(th, ph, "Error in allocating struct t_philo");
	}
	memset(ph, 0, param->n_phi * sizeof(t_philo));
}

static void	philo_state_init(t_input *param, pthread_t *th, t_philo *ph)
{
	//int	*is_eat;
	//int	*finish;
	//int	*count_eat;
	int	i;

	i = -1;
	ph[0].is_eat = (int *)malloc(sizeof(int));
	ph[0].finish = (int *)malloc(sizeof(int));
	ph[0].count_eat = (int *)malloc(sizeof(int));
	if (!ph[0].is_eat || !ph[0].finish || !ph[0].count_eat)
	{
		free(param);
		ft_error(th, ph, "Error in allocating malloc for philo state");
	}
	memset(ph[0].is_eat, 0, sizeof(int));
	memset(ph[0].finish, 0, sizeof(int));
	memset(ph[0].count_eat, 0, sizeof(int));
	while (++i < param->n_phi)
	{
		if (i != 0)
		{
			ph[i].is_eat = ph[0].is_eat;
			ph[i].finish = ph[0].finish;
			ph[i].count_eat = ph[0].count_eat;
		}
		ph[i].no = i + 1;
		ph[i].n_meal = 0;
		//ph[i].input = param;
		ph[i].lastmeal = 0;
	}
}

static pthread_mutex_t	*malloc_mutex_fork(t_input *param, pthread_t *th, t_philo *ph)
{
	int	i;
	pthread_mutex_t	*fork;

	i = -1;
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * param->n_phi);
	if (!fork)
	{
		free(param);
		ft_error(th, ph, "Error in allocating malloc for mutex fork");
	}
	memset(fork, 0, sizeof(pthread_mutex_t) * param->n_phi);
	return (fork);
}

void	ft_mutex_init(t_input *param, pthread_t *th, t_philo *ph)
{
	int	i;
	pthread_mutex_t	*display;
	pthread_mutex_t	*fork;

	i = -1;
	check_struct(param, th, ph);
	display = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	/*if (!display)
	{
		free(param);
		ft_error(th, ph, "Fail to allocating malloc pthread_mutex");
	}*/
	fork = malloc_mutex_fork(param, th, ph);
	if (!display || pthread_mutex_init(display, NULL))
	{
		free(param);
		ft_error(th, ph, "Fail to initialize pthread_mutex");
	}
	while (++i < param->n_phi)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
		{
			free(param);
			ft_error(th, ph, "Fail to initialize pthread_mutex fork");
		}
		ph[i].fork = fork;
		ph[i].display = display;
		ph[i].input = param;
	}
	philo_state_init(param, th, ph);
}
