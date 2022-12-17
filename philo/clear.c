#include "philo.h"

void	destroy_mutex(pthread_t *th, t_philo *ph)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(ph->display);
	while (++i < ph->input->n_phi)
	{
		if (pthread_mutex_destroy(ph[i].fork))
			ft_error(th, ph, "Fail to destroy pthread_mutex");
	}
}

void	ft_clear(pthread_t *th, t_philo *ph)
{
	int	i;
	int	n_phi;

	i = -1;
	n_phi = ph->input->n_phi;
	if (th)
		free(th);
	if (ph)
	{
		if (ph->display)
			free(ph->display);
		if (ph->fork)
			free(ph->fork);
		if (ph->input)
			free(ph->input);
		if (ph->finish)
			free(ph->finish);
		if (ph->is_eat)
			free(ph->is_eat);
		if (ph->count_eat)
			free(ph->count_eat);
		free(ph);
	}
}

void	ft_error(pthread_t *th, t_philo *ph, char *s)
{
	printf("%s\n", s);
	ft_clear(th, ph);
	exit(1);
}
