/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:48:18 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/13 14:45:41 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_death(t_dta *dta, int i)
{
	long long	t_last_meal;

	t_last_meal = time_now() - dta->filos[i].last_meal;
	if (t_last_meal > dta->tto_die)
	{
		pthread_mutex_lock(&dta->dead_lock);
		if (!dta->death)
		{
			ft_prints(dta, i + 1, RED"HAS DIED"RES);
			dta->death = true;
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

static int	check_death_status(t_dta *dta)
{
	pthread_mutex_lock(&dta->dead_lock);
	if (dta->death)
	{
		pthread_mutex_unlock(&dta->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&dta->dead_lock);
	return (0);
}

void	*monitor(void *arg)
{
	t_dta	*dta;
	int		i;

	dta = (t_dta *)arg;
	while (1)
	{
		if (check_death_status(dta))
			return (NULL);
		i = 0;
		while (i < dta->n_filos)
		{
			check_death(dta, i);
			i++;
		}
		if (dta->n_meals > 0)
			check_meals(dta);
		if (check_death_status(dta))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
