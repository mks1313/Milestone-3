/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:33:32 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/06 17:55:24 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_filos(t_dta *dta)
{
	int	i;

	dta->forks = malloc(sizeof(t_fork) * dta->n_filos);
	dta->filos = malloc(sizeof(t_filo) * dta->n_filos);
	if (!dta->forks || !dta->filos)
		return (error_exit("Memory allocation failed"), 1);
	i = 0;
	while (i < dta->n_filos)
	{
		pthread_mutex_init(&dta->forks[i].mutex, NULL);
		dta->filos[i].id = i + 1;
		dta->filos[i].lf = &dta->forks[i];
		dta->filos[i].rf = &dta->forks[(i + 1) % dta->n_filos];
		dta->filos[i].dta = dta;
		dta->filos[i].eating = false;
		dta->filos[i].meals_done = 0;
		dta->filos[i].last_meal = time_now();
		i++;
	}
	return (0);
}

void	init_dta(t_dta *dta)
{
	dta->death = false;
	dta->start_time = time_now();
	pthread_mutex_init(&dta->write_lock, NULL);
	pthread_mutex_init(&dta->dead_lock, NULL);
}

void	take_forks(t_filo *filo)
{
	if (filo->id % 2 == 0)
	{
		pthread_mutex_lock(&filo->lf->mutex);
		ft_prints(filo->dta, filo->id, YEL"has taken a left fork"RES);
		pthread_mutex_lock(&filo->rf->mutex);
		ft_prints(filo->dta, filo->id, "has taken a right fork");
	}
	else
	{
		pthread_mutex_lock(&filo->rf->mutex);
		ft_prints(filo->dta, filo->id, "has taken a right fork");
		pthread_mutex_lock(&filo->lf->mutex);
		ft_prints(filo->dta, filo->id, YEL"has taken a left fork"RES);
	}
}

void	put_forks(t_filo *filo)
{
	pthread_mutex_unlock(&filo->lf->mutex);
	pthread_mutex_unlock(&filo->rf->mutex);
}
