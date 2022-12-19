/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 01:16:44 by rthammat          #+#    #+#             */
/*   Updated: 2022/12/19 13:09:48 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_philo *ph, int i)
{
	if (timestamp(ph) - ph[i].lastmeal > (unsigned long)ph[i].input->t_die)
	{
		ft_display(&ph[i], timestamp(ph), "died");
		*ph[i].finish = 1;
		return (1);
	}
	return (0);
}

void	unlock_and_destroy(t_philo *ph)
{
	int	i;

	i = -1;
	while (++i < ph->input->n_phi)
	{
		pthread_mutex_unlock(ph[i].fork);
		pthread_mutex_destroy(ph[i].fork);
	}
	pthread_mutex_destroy(ph->display);
}

void	*check_dead(void *arg)
{
	int		i;
	t_philo	*ph;

	ph = (t_philo *)arg;
	i = 0;
	while (!is_dead(ph, i))
		i = i % ph->input->n_phi;
	return (NULL);
}

void	create_and_join(pthread_t *th, t_philo *ph)
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
	if (pthread_create(&th[i], NULL, check_dead, ph))
		ft_error(th, ph, "Error in creating p_thread\n");
	if (pthread_join(th[i], NULL))
		ft_error(th, ph, "Error in joining p_thread\n");
	unlock_and_destroy(ph);
	i = -1;
	while (++i < n_phi)
	{
		if (pthread_join(th[i], NULL))
			ft_error(th, ph, "Error in joining p_thread\n");
	}
}
