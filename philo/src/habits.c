/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   habits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:36:35 by mmarinov          #+#    #+#             */
/*   Updated: 2025/01/27 15:45:59 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Definir funciones de comer, pensar, dormir y funcones para tomar
// y soltar los tenedores
#include "../inc/philo.h"

void	eat(t_filo **filos)
{
	pthread_mutex_lock(filo->l_fork);
	pthread_mutex_lock(filo->r_fork);
	pfilo->eating = 1;
	pthread_mutex_lock(&filo->dta->write_lock);
	printf("Philosopher %d is eating\n", filo->id);
	pthread_mutex_unlock(&filo->dta->write_lock);
	usleep(filo->dta->tto_eat * 1000);
	pthread_mutex_lock(&filo->dta->meal_lock);
	filo->last_meal = get_time();
	filo->meals_eaten += 1;
	pthread_mutex_unlock(&filo->dta->meal_lock);
	filo->aeting = 0;
	pthread_mutex_unlock(filo->r_fork);
	pthread_mutex_unlock(filo->l_fork);
}
