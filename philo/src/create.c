/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:37:31 by mmarinov          #+#    #+#             */
/*   Updated: 2025/01/27 13:41:01 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Definir funciones de crear y ejecutar los hilos tambien de monitoreo
#include "../inc/philo.h"

void	create_filo_threads(t_filo **filos, int n_filos)
{
	int	i;

	i = 0;
	while (i < n_filos)
	{
		pthread_create(&filos[i]->thread, NULL, )
	}
}
