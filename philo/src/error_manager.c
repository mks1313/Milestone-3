/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:11:14 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/07 16:19:13 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	error_exit(const char *error)
{
	printf(RED"%s\n"RES, error);
	exit(EXIT_FAILURE);
}

void	ft_prints(t_dta *dta, int id, const char *acts)
{
	pthread_mutex_lock(&dta->write_lock);
	if (!dta->death)
		printf(MAG"%lld %d %s\n"RES, time_now() - dta->start_time, id, acts);
	pthread_mutex_unlock(&dta->write_lock);
}
