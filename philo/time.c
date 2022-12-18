/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:25:14 by rthammat          #+#    #+#             */
/*   Updated: 2022/12/18 13:25:21 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	current_time(void)
{
	struct timeval	tv;
	unsigned long	sec;
	unsigned long	u_sec;
	unsigned long	stamp;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec * 1000;
	u_sec = tv.tv_usec / 1000;
	stamp = sec + u_sec;
	return (stamp);
}

unsigned long	timestamp(t_philo *ph)
{
	return (current_time() - ph->input->start_time);
}
