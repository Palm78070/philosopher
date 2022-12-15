#include "philo.h"

void	ft_clear(t_philo *ph)
{
	int	i;
	int	n_phi;

	i = -1;
	n_phi = ph->input->n_phi;
	if (ph)
	{
		if (ph->input)
			free(ph->input);
		/*if (ph->id)
			free(ph->id);
		if (ph->pid)
			free(ph->pid);*/
		free(ph);
	}
}

void	ft_error(t_philo *ph, char *s)
{
	printf("%s\n", s);
	ft_clear(ph);
	exit(1);
}
