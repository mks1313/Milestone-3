/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   habits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:40:50 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/13 17:49:13 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_filo *filo)
{
	take_forks(filo);
	pthread_mutex_lock(&filo->dta->dead_lock);
	filo->eating = true;
	filo->last_meal = time_now();
	ft_prints(filo->dta, filo->id, BL"is eating"RES);
	pthread_mutex_unlock(&filo->dta->dead_lock);
	pthread_mutex_lock(&filo->dta->meal_lock);
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
	if (!filo->eating)
		ft_prints(filo->dta, filo->id, MAG"is thinking"RES);
}

void	sleep_filo(t_filo *filo)
{
	if (!filo->eating)
	{
		ft_prints(filo->dta, filo->id, CYAN"is sleeping"RES);
		ft_usleep(filo->dta->tto_sleep);
	}
}

void	*lifecycle(void *arg)
{
	t_filo	*filo;

	filo = (t_filo *)arg;
	if (filo->dta->n_filos == 1)
	{
		ft_prints(filo->dta, filo->id, YEL"has taken a fork"RES);
		usleep(filo->dta->tto_die * 1000);
		ft_prints(filo->dta, filo->id, RED"HAS DIED"RES);
		filo->dta->death = true;
		return (NULL);
	}
	while (!filo->dta->death)
	{
		eat(filo);
		if (filo->meals_done == filo->dta->n_meals)
			break ;
		sleep_filo(filo);
		think(filo);
	}
	return (NULL);
}
