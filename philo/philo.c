/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:24:26 by rthammat          #+#    #+#             */
/*   Updated: 2022/12/18 13:25:04 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_display(t_philo *ph, unsigned long timestamp, char *s)
{
	if (*ph->finish == 1)
		return ;
	pthread_mutex_lock(ph->display);
	printf("%lu ms Philosopher %i %s\n", timestamp, ph->no, s);
	pthread_mutex_unlock(ph->display);
}

void	*routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	ph->lastmeal = timestamp(ph);
	while (*ph->finish != 1)
	{
		if (*ph->finish == 1)
			break ;
		ft_eat(ph);
		if (*ph->is_eat == 0 && *ph->finish != 1)
			ft_display(ph, timestamp(ph), "is sleeping");
		usleep(ph->input->t_sleep * 1000);
		if (*ph->is_eat == 0 && *ph->finish != 1)
			ft_display(ph, timestamp(ph), "is thinking");
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_input		*param;
	t_philo		*ph;
	pthread_t	*th;

	if (argc < 5 || argc > 6)
	{
		printf("Error param: n_philo time_die time_eat time_sleep n_eat\n");
		exit(EXIT_FAILURE);
	}
	check_input(argc, argv);
	param = (t_input *)malloc(sizeof(t_input));
	input_init(param, argc - 1, argv);
	th = (pthread_t *)malloc(sizeof(pthread_t) * param->n_phi);
	ph = (t_philo *)malloc(sizeof(t_philo) * param->n_phi);
	ft_mutex_init(param, th, ph);
	create_and_join(th, ph);
	ft_clear(th, ph);
	return (0);
}
