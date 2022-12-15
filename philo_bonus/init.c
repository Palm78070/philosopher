#include "philo.h"

void	input_init(t_input *param, int n, char **argv)
{
	int i;

	i = 1;
	if (!param)
	{
		printf("Error in allocating t_input\n");
		exit(1);
	}
	param->n_phi = ft_atoi(argv[i++]);
	param->t_die = ft_atoi(argv[i++]);
	param->t_eat = ft_atoi(argv[i++]);
	param->t_sleep = ft_atoi(argv[i++]);
	if (i == n)
		param->n_eat = ft_atoi(argv[i]);
	else
		param->n_eat = 0;
	param->start_time = current_time();
}

void	init_semaphore(t_philo *ph)
{
	if (sem_unlink("/philo") != 0)
		ft_error(ph, "Error in unlink semaphore /philo");
	if (sem_unlink("/detach") != 0)
		ft_error(ph, "Error in unlink semaphore /detach");
	if (sem_unlink("/print") != 0)
		ft_error(ph, "Error in unlink semaphore /print");
	/*if (sem_unlink("/dead") != 0)
		ft_error(ph, "Error in unlink semaphore /dead");*/
	ph->sem = sem_open("/philo", O_CREAT, 0644, 1);
	ph->detach = sem_open("/detach", O_CREAT, 0644, 0);
	ph->print = sem_open("/print", O_CREAT, 0644, 1);
	//ph->dead = sem_open("/dead", O_CREAT, 0644, 0);
	if (ph->sem == SEM_FAILED || ph->detach == SEM_FAILED
		|| ph->print == SEM_FAILED)
	{
		printf("error to initialize semaphore\n");
		exit(1);
	}
}

void	struct_init(t_input *param, t_philo *ph)
{
	if (!ph)
	{
		free(param);
		ft_error(ph, "Error in allocating struct t_philo");
	}
	memset(ph, 0, sizeof(t_philo));
	ph->input = param;
	printf("n_phi %i\n", ph->input->n_phi);
	init_semaphore(ph);
	//ph->th = NULL;
	ph->id = (pid_t *)malloc(sizeof(pid_t) * ph->input->n_phi);
	ph->child_id = (pid_t *)malloc(sizeof(pid_t) * ph->input->n_phi);
	if (!ph->id || !ph->child_id)
		ft_error(ph, "Error in allocating id or child_id");
	memset(ph->id, 0, sizeof(pid_t) * ph->input->n_phi);
	memset(ph->child_id, 0, sizeof(pid_t) * ph->input->n_phi);
	ph->count = 0;
	ph->child_die = 0;
	ph->parent = 0;
}
