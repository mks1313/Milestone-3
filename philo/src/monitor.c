/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:48:18 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/14 16:18:38 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_death(t_dta *dta)
{
	int			i;
	long long	t_last_meal;

	i = 0;
	while (i < dta->n_filos)
	{
		pthread_mutex_lock(&dta->meal_lock);
		t_last_meal = time_now() - dta->filos[i].last_meal;
		//pthread_mutex_unlock(&dta->meal_lock);

		//pthread_mutex_lock(&dta->meal_lock);
		if (t_last_meal > dta->tto_die && !dta->death)
		{
			ft_prints(dta, i + 1, RED"🩸🩸🩸 DIED 🩸🩸🩸"RES);
			pthread_mutex_unlock(&dta->dead_lock);
			dta->death = true;
			pthread_mutex_unlock(&dta->dead_lock);
		}
		pthread_mutex_unlock(&dta->meal_lock);

		if (dta->death)
			break ;
		i++;
	}
}

void	check_meals(t_dta *dta)
{
	int	full;
	int	i;

	i = 0;
	full = 0;
	while (i < dta->n_filos)
	{
		pthread_mutex_lock(&dta->meal_lock);
		if (dta->filos[i].meals_done >= dta->n_meals)
			full++;
		pthread_mutex_unlock(&dta->meal_lock);
		i++;
	}
	if (full == dta->n_filos)
	{
		pthread_mutex_lock(&dta->dead_lock);
		printf(GR"All Philosophers have eaten %d times!\n"RES, dta->n_meals);
		dta->death = true;
		pthread_mutex_unlock(&dta->dead_lock);
	}
}

void	*monitor(void *arg)
{
	t_dta	*dta;

	dta = (t_dta *)arg;
	while (1)
	{
		pthread_mutex_lock(&dta->dead_lock);
		if (dta->death)
		{
			pthread_mutex_unlock(&dta->dead_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&dta->dead_lock);
		check_death(dta);
		if (dta->n_meals > 0)
			check_meals(dta);
		usleep(1);
	}
	return (NULL);
}
