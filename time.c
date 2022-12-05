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
