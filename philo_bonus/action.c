/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:14:13 by rthammat          #+#    #+#             */
/*   Updated: 2022/12/24 18:26:50 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_eat(t_philo *ph)
{
	int i;

	i = -1;
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
		while (++i < ph->input->n_phi)
			sem_post(ph->detach);
	}
	super_sleep(ph->input->t_eat);
	sem_post(ph->fork);
	sem_post(ph->fork);
}
