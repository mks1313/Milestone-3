/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:48:18 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/11 19:05:44 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_death(t_dta *dta, int i)
{
	long long	t_from_last_meal;

	t_from_last_meal = time_now() - dta->filos[i].last_meal;
	if (t_from_last_meal > dta->tto_die)
	{
		pthread_mutex_lock(&dta->dead_lock);
		if (!dta->death)
		{
			dta->death = true;
			printf(MAG"%lld %d %s\n"RES, time_now() - dta->start_time,
				dta->filos[i].id, RED"has died"RES);
		}
		pthread_mutex_unlock(&dta->dead_lock);
	}
}

void	check_meals(t_dta *dta)
{
	int	i;
	int	full;

	full = 0;
	i = 0;
	while (i < dta->n_filos)
	{
		if (dta->filos[i].meals_done >= dta->n_meals)
			full++;
		i++;
	}
	if (full == dta->n_filos)
	{
		pthread_mutex_lock(&dta->dead_lock);
		dta->death = true;
		pthread_mutex_unlock(&dta->dead_lock);
	}
}

void	*monitor(void *arg)
{
	t_dta		*dta;
	int			i;

	dta = (t_dta *)arg;
	while (!dta->death)
	{
		i = 0;
		while (i < dta->n_filos)
		{
			check_death(dta, i);
			if (dta->death)
				return (NULL);
			i++;
		}
		if (dta->n_meals > 0)
			check_meals(dta);
		usleep(200);
	}
	return (NULL);
}
