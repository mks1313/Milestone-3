/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:48:18 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/06 19:01:56 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_dta *dta, int i)
{
	long long	t_from_last_meal;

	t_from_last_meal = time_now() - dta->filos[i].last_meal;
	if (t_from_last_meal > dta->tto_die)
	{
		pthread_mutex_lock(&dta->dead_lock);
		if (!dta->death)
		{
			dta->death = 1;
			ft_prints(dta, dta->filos[i].id, "has died");
		}
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
		usleep(1000);
	}
	return (NULL);
}
