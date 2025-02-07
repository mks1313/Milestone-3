/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:36:32 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/06 12:50:30 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *s)
{
	int			i;
	long long	res;

	i = 0;
	res = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			error_exit("Error: Number should be a positive!");
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		res = res * 10 + (s[i] - '0');
		if (res > INT_MAX)
			error_exit("Error: Number is too big!");
		i++;
	}
	if (s[i] != '\0')
		error_exit("Error: The number contains invalid characters!");
	return ((int)res);
}
