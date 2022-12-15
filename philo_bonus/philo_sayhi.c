#include "philo.h"

void	*child(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (ph->count < 5)
	{
		if (sem_wait(ph->sem))
		{
			printf("Error in sem_wait\n");
			exit(1);
		}
		printf("Child %i  Parent %i count %i\n", getpid(), getppid(), ph->count);
		if (sem_post(ph->sem))
		{
			printf("Error in sem_post\n");
			exit(1);
		}
		ph->count += 1;
		sleep(1);
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

void	ft_child(t_philo *ph, pthread_t th, int detach_value)
{
	if (pthread_create(&th, NULL, child, ph))
	{
		printf("Error in create thread\n");
		exit(1);
	}
	while (detach_value != 0)
	{
		sem_wait(ph->detach);
		detach_value = pthread_detach(th);
		if (detach_value)
		{
			printf("Error in detach thread\n");
			exit(1);
		}
		printf("Child %i  Parent %i detach\n", getpid(), getppid());
		ph->parent = getppid();
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

/*void	ft_parent(t_philo *ph)
{
	int	i;

	printf("finish eating id %i\n", getpid());
	sleep(1);
	i = -1;
	while (++i < ph->input->n_phi)
	{
		printf("kill child %i\n", getpid());
			if (kill(ph->id[i], SIGKILL) != 0)
			{
				printf("Error in killing child %i\n", getpid());
				exit(1);
			}
	}
	sem_close(ph->sem);
	sem_close(ph->detach);
	sem_close(ph->print);
	free(ph->id);
	ft_clear(ph);
}*/

int	main(int argc, char **argv)
{
	//pid_t	parent = 0;
	t_input *param;
	t_philo *ph;
	pthread_t th = NULL;
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
	printf("n_phi %i\n", ph->input->n_phi);
	while (++i < ph->input->n_phi)
	{
		if (i > 0)
			sleep(4);
		ph->id[i] = fork();
		if (ph->id[i] == 0)
		{
			printf("Fork Child %i\n", getpid());
			ft_child(ph, th, detach_value);
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
	/*else
	{
		if (pthread_create(&th, NULL, child, ph))
		{
			printf("Error in create thread\n");
			exit(1);
		}
		while (detach_value != 0)
		{
			sem_wait(ph->detach);
			detach_value = pthread_detach(th);
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
			printf("exit success %i\n", getpid());
			exit(EXIT_SUCCESS);
		}
	}*/
	//if (ph->id[0] != 0)
	//if (!is_child(ph))
	//if (ph->id[0] != 0)
	if (!is_child(ph))
	{
		printf("finish eating id %i\n", getpid());
		//printf("parent %i\n", ph->parent);
		sleep(1);
		//sem_post(ph->detach);
		i = -1;
		while (++i < ph->input->n_phi)
		{
			//if (ph->child_id[i] != ph->parent && ph->child_id[i] != ph->child_die)
			if (ph->child_id[i] != 0)
			{
				printf("kill child %i\n", ph->child_id[i]);
				if (kill(ph->child_id[i], SIGKILL) == 0)
				{
					printf("kill child success %i\n", ph->child_id[i]);
				}
				/*if (kill(ph->child_id[i], SIGKILL) != 0)
				{
					printf("Error in killing child %i\n", ph->child_id[i]);
					exit(1);
				}*/
			}
		}
		sem_close(ph->sem);
		sem_close(ph->detach);
		sem_close(ph->print);
		free(ph->id);
		ft_clear(ph);
		exit(EXIT_SUCCESS);
	}
	return 0;
}
