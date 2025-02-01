/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:19:27 by mmarinov          #+#    #+#             */
/*   Updated: 2025/01/28 17:13:43 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		if (!is_digit(s[i]))
			error_exit("Invalid character detected in the input!");
		if (res > (INT_MAX - (s[i] - '0')) / 10)
			return (INT_MAX);
		res = res * 10 + (s[i] - '0');
		i++;
	}
	return (res);
}

