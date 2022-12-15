#include "philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (++i <= argc - 1)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j++]))
			{
				printf("Input is not unsigned integer\n");
				exit (EXIT_FAILURE);
			}
		}
	}
}
