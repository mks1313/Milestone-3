/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:06:17 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/07 15:02:50 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	time_now(void)
{
	struct timeval	now;
	long long		mlsec;

	gettimeofday(&now, NULL);
	mlsec = ((now.tv_sec * 1000) + (now.tv_usec / 1000));
	return (mlsec);
}

int	ft_usleep(long long time)
{
	struct timespec	ts;
	long long		start_time;

	start_time = time_now();
	ts.tv_sec = time / 1000;
	ts.tv_nsec = (time % 1000) * 1000000;
	while ((time_now() - start_time) < time)
		nanosleep(&ts, NULL);
	return (1);
}
