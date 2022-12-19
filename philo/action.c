/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 01:16:29 by rthammat          #+#    #+#             */
/*   Updated: 2022/12/19 11:58:15 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *ph)
{
	if (*ph->finish == 1)
		return ;
	pthread_mutex_lock(&ph->fork[ph->no - 1]);
	ft_display(ph, timestamp(ph), "has taken a left fork");
	pthread_mutex_lock(&ph->fork[ph->no % ph->input->n_phi]);
	ph->lastmeal = timestamp(ph);
	ft_display(ph, timestamp(ph), "has taken a right fork");
	ft_display(ph, timestamp(ph), "is eating");
	ph->n_meal += 1;
	if (ph->n_meal == ph->input->n_eat)
		*ph->count_eat += 1;
	if (*ph->count_eat == ph->input->n_phi)
		*ph->finish = 1;
	super_sleep(ph->input->t_eat);
	pthread_mutex_unlock(&ph->fork[ph->no % ph->input->n_phi]);
	pthread_mutex_unlock(&ph->fork[ph->no - 1]);
}
