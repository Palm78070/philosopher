/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:14:13 by rthammat          #+#    #+#             */
/*   Updated: 2022/12/24 21:10:57 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_display(t_philo *ph, unsigned long timestamp, char *s)
{
	if (*ph->finish == 1)
		return ;
	sem_wait(ph->print);
	printf("%lu ms Philosopher %i %s\n", timestamp, ph->no, s);
	sem_post(ph->print);
}

void	ft_eat(t_philo *ph)
{
	int	i;

	i = -1;
	if (*ph->finish == 1)
		return ;
	sem_wait(ph->fork);
	ft_display(ph, timestamp(ph), "has taken a fork");
	sem_wait(ph->fork);
	ph->lastmeal = timestamp(ph);
	ft_display(ph, timestamp(ph), "has taken a fork");
	ft_display(ph, timestamp(ph), "is eating");
	ph->n_meal += 1;
	if (ph->n_meal == ph->input->n_eat)
	{
		while (++i < ph->input->n_phi)
			sem_post(ph->detach);
	}
	super_sleep(ph->input->t_eat);
	sem_post(ph->fork);
	sem_post(ph->fork);
}

void	*routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (*ph->finish != 1)
	{
		if (*ph->finish != 1)
			ft_eat(ph);
		if (*ph->finish != 1)
		{
			ft_display(ph, timestamp(ph), "is sleeping");
			super_sleep(ph->input->t_sleep);
		}
		if (*ph->finish != 1)
			ft_display(ph, timestamp(ph), "is thinking");
	}
	return (NULL);
}
