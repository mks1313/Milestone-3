/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   habits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:40:50 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/14 13:21:17 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_filo *filo)
{
	take_forks(filo);
	pthread_mutex_lock(&filo->dta->dead_lock);
	ft_prints(filo->dta, filo->id, BL"is eating"RES);
	pthread_mutex_unlock(&filo->dta->dead_lock);

	pthread_mutex_lock(&filo->dta->meal_lock);
	filo->last_meal = time_now();
	filo->eating = true;
	filo->meals_done++;
	pthread_mutex_unlock(&filo->dta->meal_lock);

	ft_usleep(filo->dta->tto_eat);
	pthread_mutex_lock(&filo->dta->dead_lock);
	filo->eating = false;
	pthread_mutex_unlock(&filo->dta->dead_lock);
	put_forks(filo);
}

void	think(t_filo *filo)
{
	pthread_mutex_lock(&filo->dta->dead_lock);
	pthread_mutex_lock(&filo->dta->meal_lock);
	if (!filo->eating && !filo->dta->death)
		ft_prints(filo->dta, filo->id, MAG"is thinking"RES);
		pthread_mutex_unlock(&filo->dta->meal_lock);
		pthread_mutex_unlock(&filo->dta->dead_lock);
}

void	sleep_filo(t_filo *filo)
{
	if (!filo->eating && !filo->dta->death)
	{
		pthread_mutex_lock(&filo->dta->dead_lock);
		pthread_mutex_lock(&filo->dta->meal_lock);
		ft_prints(filo->dta, filo->id, CYAN"is sleeping"RES);
		pthread_mutex_unlock(&filo->dta->meal_lock);
		pthread_mutex_unlock(&filo->dta->dead_lock);
		ft_usleep(filo->dta->tto_sleep);
	}
}

void	*lifecycle(void *arg)
{
	t_filo	*filo;

	filo = (t_filo *)arg;
	if (filo->dta->n_filos == 1)
	{
		pthread_mutex_lock(&filo->dta->dead_lock);
		ft_prints(filo->dta, filo->id, YEL"has taken a fork"RES);
		ft_usleep(filo->dta->tto_die);
		free_resources(filo->dta);
		pthread_mutex_unlock(&filo->dta->dead_lock);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&filo->dta->dead_lock);
		if (filo->dta->death)
		{
			pthread_mutex_unlock(&filo->dta->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&filo->dta->dead_lock);
		eat(filo);
		if (filo->meals_done == filo->dta->n_meals)
			break ;
		sleep_filo(filo);
		think(filo);
	}
	return (NULL);
}
