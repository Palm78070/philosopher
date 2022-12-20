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

void	ft_eat(t_philo *ph)
{
	if (*ph->finish == 1)
		return;
	sem_wait(ph->fork);
	ft_display(ph, timestamp(ph), "has taken a fork");
	sem_wait(ph->fork);
	ph->lastmeal = timestamp(ph);
	ft_display(ph, timestamp(ph), "has taken a fork");
	ft_display(ph, timestamp(ph), "is eating");
	ph->n_meal += 1;
	if (ph->n_meal == ph->input->n_eat)
	{
		sem_post(detach);
		//*ph->count_eat += 1;
	}
	//if (*ph->count_eat == ph->input->n_phi)
	//	*ph->finish = 1;
	super_sleep(ph->input->t_eat);
	sem_wait(ph->fork);
	sem_wait(ph->fork);
}
