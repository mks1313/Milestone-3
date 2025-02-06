/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:05:28 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/06 17:56:28 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_resources(t_dta *dta)
{
	int	i;

	i = 0;
	while (i < dta->n_filos)
	{
		pthread_mutex_destroy(&dta->forks[i].mutex);
		i++;
	}
	free(dta->filos);
	free(dta->forks);
}
