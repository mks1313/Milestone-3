/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:19:27 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/04 14:14:58 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tm;
	long long		mlsec;

	gettimeofday(&tm, NULL);
	mlsec = tm.tv_sec * 1000 + tm.tv_usec / 1000;
	printf("Time: %lld\n", mlsec);
	return (mlsec);
}

static int	ft_is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_is_digit_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_is_digit(s[i]))
			return (0);
		i++;
	}
	return (1);
}


int	ft_atoi(char *s)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-')
		error_exit("Negative numbers are not allowed!");
	while (s[i])
	{
		if (!ft_is_digit(s[i]))
			error_exit("Invalid character detected in the input!");
		if (res > (INT_MAX - (s[i] - '0')) / 10)
			return (INT_MAX);
		res = res * 10 + (s[i] - '0');
		i++;
	}
	return (res);
}

void	parse_args(t_dta *dta, char **av)
{
	if (!ft_is_digit_str(av[1]) || (dta->n_filos = ft_atoi(av[1])) <= 0)
		error_exit("Invalid number of philosohers!\n");
	if (!ft_is_digit_str(av[2]) || (dta->tto_die = ft_atoi(av[2])) <= 0)
		error_exit("Invalid time to die!\n");
	if (!ft_is_digit_str(av[3]) || (dta->tto_eat = ft_atoi(av[3])) <= 0)
		error_exit("Invalid time to eat!\n");
	if (!ft_is_digit_str(av[4]) || (dta->tto_sleep = ft_atoi(av[4])) <= 0)
		error_exit("Invalid time to sleep!\n");
	if (av[5])
	{
		if (!ft_is_digit_str(av[5]) || (dta->n_meals = ft_atoi(av[5])) <= 0)
		error_exit("Invalid number of meals");
	}
	else
		dta->n_meals = -1;

}

void	free_resources(t_dta *dta)
{
	int	i;

	i = 0;
	while (i < dta->n_filos)
	{
		pthread_mutex_destroy(&dta->forks[i].mutex);
		i++;
	}
	free(dta->forks);
	free(dta->filos);
}
