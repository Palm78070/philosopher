#include "philo.h"

//int	is_dead(t_philo *ph, int i)
int	is_dead(t_philo *ph)
{
	if (timestamp(ph) - ph->lastmeal > (unsigned long)ph->input->t_die)
	{
		ft_display(ph, timestamp(ph), "died");
		*ph->finish = 1;
		return (1);
	}
	return (0);
}

void	sem_post_all_detach(t_philo *ph)
{
	int	i;

	i = -1;
	while (++i < ph->input->n_phi)
	{
		sem_post(ph->detach);
	}
}

void	*check_dead(void *arg)
{
	int	i;
	t_philo	*ph;

	ph = (t_philo *)arg;
	i = 0;
	while (1)
	{
		if (is_dead(ph))
			break ;
	}
	if (pthread_detach(ph->th[1]))
		ft_error(ph, "Error in detach th[1]");
	//sem_post(ph->detach);
	sem_post_all_detach(ph);
	return (NULL);
}
