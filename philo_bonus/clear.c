/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:14:32 by rthammat          #+#    #+#             */
/*   Updated: 2022/12/24 18:15:59 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_clear(t_philo *ph)
{
	if (ph)
	{
		if (ph->input)
			free(ph->input);
		if (ph->id)
			free(ph->id);
		if (ph->child_id)
			free(ph->child_id);
		if (ph->finish)
			free(ph->finish);
		if (ph->th)
			free(ph->th);
		free(ph);
	}
}

void	ft_error(t_philo *ph, char *s)
{
	printf("%s\n", s);
	ft_clear(ph);
	exit(1);
}
