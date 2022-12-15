#include "philo.h"

/*void	ft_eat(t_philo *ph)
{
	pthread_mutex_lock(ph->check);
	pthread_mutex_lock(&ph->fork[ph->no - 1]);
	ft_display(ph, timestamp(ph), "has taken a left fork");
	pthread_mutex_lock(&ph->fork[ph->no % ph->input->n_phi]);
	*ph->is_eat = 1;
	ft_display(ph, timestamp(ph), "has taken a right fork");
	ft_display(ph, timestamp(ph), "is eating");
	ph->lastmeal = timestamp(ph);
	ph->n_meal += 1;
	usleep(ph->input->t_eat * 1000);
	*ph->is_eat = 0;
	pthread_mutex_unlock(&ph->fork[ph->no % ph->input->n_phi]);
	pthread_mutex_unlock(&ph->fork[ph->no - 1]);
	pthread_mutex_unlock(ph->check);
}*/
