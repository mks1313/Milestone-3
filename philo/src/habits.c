/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   habits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:40:50 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/07 16:27:01 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_filo *filo)
{
	take_forks(filo);
	filo->eating = true;
	filo->last_meal = time_now();
	ft_prints(filo->dta, filo->id, BL"is eating"RES);
	ft_usleep(filo->dta->tto_eat);
	filo->meals_done++;
	filo->eating = false;
	put_forks(filo);
}

void	think(t_filo *filo)
{
	ft_prints(filo->dta, filo->id, MAG"is thinking"RES);
}

void	sleep_filo(t_filo *filo)
{
	ft_prints(filo->dta, filo->id, CYAN"is sleeping"RES);
	ft_usleep(filo->dta->tto_sleep);
}

void	*lifecycle(void *arg)
{
	t_filo	*filo;

	filo = (t_filo *)arg;
	if (filo->dta->n_filos == 1)
	{
		ft_prints(filo->dta, filo->id, YEL"has taken a fork"RES);
		usleep(filo->dta->tto_die * 1000);
		printf("filo %d ha muerto\n", filo->id);
		ft_prints(filo->dta, filo->id, RED"has died"RES);
		filo->dta->death = true;
		free_resources(filo->dta);
		return (NULL);
	}
	while (!filo->dta->death)
	{
		eat(filo);
		sleep_filo(filo);
		think(filo);
	}
	return (NULL);
}
