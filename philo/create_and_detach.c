#include "philo.h"

static int	eat_full(t_philo *ph)
{
	int	i;
	int	count;
	int	n_phi;

	i = 0;
	count = 0;
	n_phi = ph[0].input->n_phi;
	if (ph->input->n_eat == 0)
		return (0);
	while (i < n_phi)
	{
		if (ph[i].n_meal == ph[i].input->n_eat)
			++count;
		++i;
	}
	if (count == ph->input->n_phi)
		return (1);
	return (0);
}

static int	is_dead(t_philo *ph, int i)
{
	if (timestamp(ph) - ph[i].lastmeal > (unsigned long)ph[i].input->t_die)
	{
		ft_display(&ph[i], timestamp(ph), "died");
		return (1);
	}
	return (0);
}

static void	detach_all_thread(pthread_t *th, t_philo *ph)
{
	int	i;

	i = -1;
	while (++i < ph->input->n_phi)
	{
		if (pthread_detach(th[i]))
			ft_error(th, ph, "Error in detaching thread\n");
	}
}

void	create_and_detach(pthread_t *th, t_philo *ph)
{
	int	i;
	int	n_phi;

	i = -1;
	n_phi = ph[0].input->n_phi;
	while (++i < n_phi)
	{
		if (pthread_create(&th[i], NULL, routine, &ph[i]))
			ft_error(th, ph, "Error in creating p_thread\n");
		usleep(100);
	}
	i = 0;
	while (!is_dead(ph, i) && !eat_full(ph))
		i = (i + 1) % n_phi;
	detach_all_thread(th, ph);
}
