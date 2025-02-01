/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   habits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:36:35 by mmarinov          #+#    #+#             */
/*   Updated: 2025/01/28 13:52:56 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Definir funciones de comer, pensar, dormir y funcones para tomar
// y soltar los tenedores
#include "philo.h"

void	think(t_filo *filo)
{
	printf(BL"Philosopher is thinking!\n"RES, filo->id);
	usleep(filo->dta->tto_sleep * 1000);
}

void	eat(t_filo *filo)
{
	filo->is_eating = true;
	filo->last_meal = get_time();
	printf(YEL"Philosopher is eating!\n"RES, filo->id);
	usleep(filo->dta->tto_eat * 1000);
	filo->meals_done++;
	filo->is_eating = false;
}

void	sleep(t_filo *filo)
{
	printf(MAG"Philosopher is sleeping!\n"RES, filo->id);
	usleep(filo->dta->tto_sleep * 1000);
}

