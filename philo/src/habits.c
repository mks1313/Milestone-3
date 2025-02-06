/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   habits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:40:50 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/06 17:41:30 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	ft_prints(filo->dta, filo->id, "is thinking");
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
	while (!filo->dta->death)
	{
		eat(filo);
		sleep_filo(filo);
		think(filo);
	}
	return (NULL);
}
