/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:08:33 by mmarinov          #+#    #+#             */
/*   Updated: 2025/01/24 15:42:46 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Iniciar los mutex de tenedores y la estrucutra de datos.!!!!
#include "../inc/philo.h"

// Init Forks
void	init_forks(pthread_mutex_t *forks, int n_filos)
{
	int	i;

	i = 0;
	while (i < n_filos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

// Init of the struct the  program and filos
void	init_program(t_dta *dta, pthread_mutex_t *forks, cahr **argv)
{
	int	i;

	dta->dead_flag = 0;
	dta->n_filos = ft_atoi(argv[1]);
	dta->tto_die = ft_atoi(argv[2]);
	dta->tto_eat = ft_atoi(argv[3]);
	dta->tto_sleep = ft_atoi(argv[4]);
	dta->n_tto_eat = ft_atoi(argv[5]);
	dta->filos = malloc(dta->n_filos * sizeof(t_filo *));
	if (!data->filos)
	{
		perror("Error to assign memory");
		exit(EXIT_FAILURE);
	}
	while (i < dta->n_filos)
	{
		dta->filos[i] = malloc(sizeof(t_filo));
		if (!dta->filos[i])
		{
			perror("Error of assign memory");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	pthread_mutex_init(&dta->write_lock, NULL);
	pthread_mutex_init(&dta->dead_lock, NULL);
	pthread_mutex_init(&dta->meal_lock, NULL);
	i = 0;
	while (i < dta->n_filos)
	{
		dta->filos[i]->id = i + 1;
		dta->filos[i]->meals_eaten = 0;
		dta->filos[i]->eating = 0;
		dta->filos[i]
	}
}

// Init of the filo
void	init_filo(t_filo *filos, t_dta *dta, pthread_mutex_t *forks, int)
