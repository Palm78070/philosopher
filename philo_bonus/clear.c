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
		 (ph->id)
			free(ph->id);
		if (ph->child_id)
			free(ph->child_id);
		if (ph->finish)
			free(ph->finish);
		free(ph);
	}
}

void	ft_error(t_philo *ph, char *s)
{
	printf("%s\n", s);
	ft_clear(ph);
	exit(1);
}
