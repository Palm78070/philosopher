#include "philo.h"

void  ft_display(t_philo *ph, unsigned long timestamp, char *s)
{
	if (ph->finish)
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
			super_sleep(ph->input->t_sleep);
		if (*ph->finish != 1)
			ft_display(ph, timestamp(ph), "is thinking");
	}
	ph->child_die = 1;
	printf("Out of loop to sem_post\n");
	sem_post(ph->detach);
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

void	ft_child(t_philo *ph, int detach_value)
{
	int	i;

	i = 0;
	if (pthread_create(&ph->th, NULL, routine, ph))
	{
		printf("Error in create thread\n");
		exit(1);
	}
	while (!is_dead(ph, i))
		i = i % ph->input->n_phi;
	while (detach_value != 0)
	{
		sem_wait(ph->detach);
		detach_value = pthread_detach(ph->th);
		if (detach_value)
		{
			printf("Error in detach thread\n");
			exit(1);
		}
		printf("Child %i  Parent %i detach\n", getpid(), getppid());
	}
	sem_post(ph->detach);
	printf("after success detach\n");
	if (ph->child_die)
	{
		ph->child_die = getpid();
		printf("child die %i\n", ph->child_die);
		printf("exit success %i\n", getpid());
		exit(EXIT_SUCCESS);
	}
}

void	ft_parent(t_philo *ph)
{
	printf("finish eating id %i\n", getpid());
	sleep(1);
	i = -1;
	while (++i < ph->input->n_phi)
	{
		if (ph->child_id[i] != 0)
		{
			printf("kill child %i\n", ph->child_id[i]);
			if (kill(ph->child_id[i], SIGKILL) == 0)
				printf("kill child success %i\n", ph->child_id[i]);
		}
	}
	sem_close(ph->sem);
	sem_close(ph->detach);
	sem_close(ph->print);
	free(ph->id);
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
			sleep(4);
		ph->id[i] = fork();
		if (ph->id[i] == 0)
		{
			ph->no = i + 1;
			ft_child(ph, detach_value);
			break;
		}
		else
		{
			ph->child_id[i] = ph->id[i];
			printf("child id %i\n", ph->child_id[i]);
		}
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
	int detach_value = -1;

	if (argc < 5 || argc > 6)
	{
		printf("Error param: n_philo time_die time_eat time_sleep n_eat\n");
		exit(0);
	}
	param = (t_input *)malloc(sizeof(t_input));
	ph = (t_philo *)malloc(sizeof(t_philo));
	input_init(param, argc - 1, argv);
	i = -1;
	struct_init(param, ph);
	fork_process(ph);
	/*while (++i < ph->input->n_phi)
	{
		if (i > 0)
			sleep(4);
		ph->id[i] = fork();
		if (ph->id[i] == 0)
		{
			ph->no = i + 1;
			printf("Fork Child %i\n", getpid());
			ft_child(ph, detach_value);
			break;
		}
		else
		{
			ph->child_id[i] = ph->id[i];
			printf("child id %i\n", ph->child_id[i]);
		}
	}
	if (i == ph->input->n_phi)
	{
		pid_t w_pid = 0;
		while (w_pid == 0)
		{
			w_pid = waitpid(-1, NULL, WNOHANG);
		}
		printf("Out of w_pid loop\n");
	}
	if (!is_child(ph))
	{
		printf("finish eating id %i\n", getpid());
		sleep(1);
		i = -1;
		while (++i < ph->input->n_phi)
		{
			if (ph->child_id[i] != 0)
			{
				printf("kill child %i\n", ph->child_id[i]);
				if (kill(ph->child_id[i], SIGKILL) == 0)
				{
					printf("kill child success %i\n", ph->child_id[i]);
				}
			}
		}
		sem_close(ph->sem);
		sem_close(ph->detach);
		sem_close(ph->print);
		free(ph->id);
		ft_clear(ph);
		exit(EXIT_SUCCESS);
	}*/
	return 0;
}
