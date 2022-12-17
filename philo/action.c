/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 01:16:29 by rthammat          #+#    #+#             */
/*   Updated: 2022/12/18 01:16:38 by rthammat         ###   ########.fr       */
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
	*ph->is_eat = 1;
	ft_display(ph, timestamp(ph), "has taken a right fork");
	ft_display(ph, timestamp(ph), "is eating");
	ph->n_meal += 1;
	if (ph->n_meal == ph->input->n_eat)
		*ph->count_eat += 1;
	if (*ph->count_eat == ph->input->n_phi)
		*ph->finish = 1;
	usleep(ph->input->t_eat * 1000);
	*ph->is_eat = 0;
	pthread_mutex_unlock(&ph->fork[ph->no % ph->input->n_phi]);
	pthread_mutex_unlock(&ph->fork[ph->no - 1]);
}
