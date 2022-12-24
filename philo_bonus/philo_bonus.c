/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:07:36 by rthammat          #+#    #+#             */
/*   Updated: 2022/12/24 18:30:31 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void  ft_display(t_philo *ph, unsigned long timestamp, char *s)
{
	if (*ph->finish == 1)
		return ;
	sem_wait(ph->print);
	printf("%lu ms Philosopher %i %s\n", timestamp, ph->no, s);
	sem_post(ph->print);
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

int	is_child(t_philo *ph)
{
	int i;

	i = -1;
	while (++i < ph->input->n_phi)
	{
		if (ph->child_id[i] == 0)
			return (1);
	}
	return (0);
}

void	*ft_dead(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	sem_wait(ph->dead);
	pthread_detach(ph->th[0]);
	sem_post(ph->dead);
	exit(EXIT_SUCCESS);
	return (NULL);
}

void	ft_child(t_philo *ph)
{
	int	detach_value;
	int	i;
	pthread_t	thx;

	thx = NULL;
	i = 0;
	detach_value = -1;
	if (pthread_create(&ph->th[0], NULL, routine, ph))
		ft_error(ph, "Error in create thread");
	if (pthread_create(&ph->th[1], NULL, check_dead, ph))
		ft_error(ph, "Error in create thread");
	//////////////////dummy/////////////////////////
	pthread_create(&thx, NULL, ft_dead, ph);
	//////////////////dummy/////////////////////////
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
	int	i;

	i = -1;
	while (++i < ph->input->n_phi)
	{
		if (i > 0)
			usleep(10);
		ph->id[i] = fork();
		if (ph->id[i] == 0)
		{
			ph->no = i + 1;
			ft_child(ph);
			break;
		}
		else
			ph->child_id[i] = ph->id[i];
	}
	if (i == ph->input->n_phi)
	{
		pid_t w_pid = 0;
		while (w_pid == 0)
			w_pid = waitpid(-1, NULL, WNOHANG);
	}
	if (!is_child(ph))
		ft_parent(ph);
}

int	main(int argc, char **argv)
{
	t_input *param;
	t_philo *ph;
	int i;

	if (argc < 5 || argc > 6)
	{
		printf("Error param: n_philo time_die time_eat time_sleep n_eat\n");
		exit(0);
	}
	check_input(argc, argv);
	param = (t_input *)malloc(sizeof(t_input));
	ph = (t_philo *)malloc(sizeof(t_philo));
	input_init(param, argc - 1, argv);
	i = -1;
	struct_init(param, ph);
	fork_process(ph);
	return 0;
}