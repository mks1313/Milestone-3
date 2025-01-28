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
#include "../inc/philo.h"

void	eat(t_filo *filo)
{
	//Bloqueamos ambos tenedores
	pthread_mutex_lock(filo->l_fork);
	pthread_mutex_lock(filo->r_fork);
	//Indicamos que el filo esta comiendo
	filo->eating = 1;
	pthread_mutex_lock(&filo->dta->write_lock);
	printf("Philosopher %d is eating\n", filo->id);
	pthread_mutex_unlock(&filo->dta->write_lock);
	// Comer toma un tiempo determinado por el tto_eat
	usleep(filo->dta->tto_eat * 1000);
	//Actualizamos el tiempo de la ultima comida
	pthread_mutex_lock(&filo->dta->meal_lock);
	filo->last_meal = get_time();
	filo->meals_done += 1;
	pthread_mutex_unlock(&filo->dta->meal_lock);
	//Liberamos los tenedores
	filo->eating = 0;
	pthread_mutex_unlock(filo->r_fork);
	pthread_mutex_unlock(filo->l_fork);
}

void	*filo_routine(void *arg)
{
	t_filo	*filo;

	filo = (t_filo *)arg;
	while (!filo->dta->dead_flag)
	{
		pthread_mutex_lock(&filo->dta->write_lock);
		printf("Philosopher %d is thinking\n", filo->id);
		pthread_mutex_unlock(&filo->dta->write_lock);
		eat(filo);
		pthread_mutex_lock(&filo->dta->write_lock);
		printf("Philosopher %d is sleeping\n", filo->id);
		pthread_mutex_unlock(&filo->dta->write_lock);
		usleep(filo->dta->tto_sleep * 1000);
	}
	return (NULL);
}
