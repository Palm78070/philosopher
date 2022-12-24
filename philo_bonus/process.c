/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 20:36:21 by rthammat          #+#    #+#             */
/*   Updated: 2022/12/24 21:19:13 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_child(t_philo *ph)
{
	int	i;

	i = -1;
	while (++i < ph->input->n_phi)
	{
		if (ph->child_id[i] == 0)
			return (1);
	}
	return (0);
}

void	ft_child(t_philo *ph)
{
	int			detach_value;
	int			i;
	pthread_t	th_dead;

	th_dead = NULL;
	i = 0;
	detach_value = -1;
	if (pthread_create(&ph->th[0], NULL, routine, ph))
		ft_error(ph, "Error in create thread");
	if (pthread_create(&ph->th[1], NULL, check_dead, ph))
		ft_error(ph, "Error in create thread");
	pthread_create(&th_dead, NULL, ft_dead, ph);
	while (detach_value != 0)
	{
		i = -1;
		while (++i < ph->input->n_phi)
			sem_wait(ph->detach);
		detach_value = pthread_detach(ph->th[0]);
		if (detach_value)
			ft_error(ph, "Error in detach thread th[0]");
	}
	sem_post(ph->detach);
	exit(EXIT_SUCCESS);
}

void	ft_parent(t_philo *ph)
{
	int	i;

	i = -1;
	while (++i < ph->input->n_phi)
	{
		if (ph->child_id[i] != 0)
			kill(ph->child_id[i], SIGKILL);
	}
	sem_close(ph->fork);
	sem_close(ph->detach);
	sem_close(ph->print);
	ft_clear(ph);
	exit(EXIT_SUCCESS);
}

void	fork_process(t_philo *ph)
{
	int		i;
	pid_t	w_pid;

	i = -1;
	w_pid = 0;
	while (++i < ph->input->n_phi)
	{
		if (i > 0)
			usleep(10);
		ph->id[i] = fork();
		if (ph->id[i] == 0)
		{
			ph->no = i + 1;
			ft_child(ph);
			break ;
		}
		else
			ph->child_id[i] = ph->id[i];
	}
	if (i == ph->input->n_phi)
		while (w_pid == 0)
			w_pid = waitpid(-1, NULL, WNOHANG);
	if (!is_child(ph))
		ft_parent(ph);
}
