#include "philo.h"

int	is_dead(t_philo *ph, int i)
{
	if (timestamp(ph) - ph[i].lastmeal > (unsigned long)ph[i].input->t_die)
	{
		ft_display(&ph[i], timestamp(ph), "died");
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
		sem_post(ph->detach);
}

void	*check_dead(void *arg)
{
	int	i;
	t_philo	*ph;

	ph = (t_philo *)arg;
	i = 0;
	while (!is_dead(ph, i))
		i = i % ph->input->n_phi;
	if (pthread_detach(ph->th[1]))
		ft_error(ph, "Error in detach th[1]");
	sem_post_all_detach(ph);
	return (NULL);
}
