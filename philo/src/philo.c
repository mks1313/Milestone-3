/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:17:12 by mmarinov          #+#    #+#             */
/*   Updated: 2025/01/27 15:50:30 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	cleanup(t_filo **filos, int n_filos, t_dta *dta, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < n_filos)
	{
		pthread_join(filos[i]->thread, NULL);
		pthread_mutex_destroy(&fork[i]);
		free(filos[i]);
		i++;
	}
	pthread_mutex_destroy(&dta->dead_lock);
	pthread_mutex_destroy(&dta->meal_lock);
	pthread_mutex_destroy(&dta->write_lock);
	free(filos);
}

void	monitor_filos(t_dta *dta)
{
	int	i;

	while (!dta->dead_flag)
	{
		i = 0;
		while (i < dta->n_filos)
		{
			pthread_mutex_lock(&dta->meal_lock);
			if (get_time() - dta->filos[i]->last_meal > dta->filos[i]->dta->tto_die)
			{
				pthread_mutex_lock(&dta->write_lock);
				printf("Philosopher %d has died\n", dta->filo[i]->id);
				pthread_mutex_unlock(&dta->write_lock);
				dta->dead_flag = 1;
			}
			pthread_mutex_unlock(&dta->meal_lock);
		}
		usleep(1000);
	}
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Numbers of arameters is incorrect!\n");
		return EXIT_FAILURE;
	}
	t_dta dta;
	pthreaad_mutex_t forks[ft_atoi(argv[1])];
	init_forks(forks, ft_atoi(argv[1]));
	init_program(&dta, forks, argv);
	create_filo_threads(dta.filos, dta.n_filos);
	monitor_filos(&dta);
	cleanup(dta.filos, dta.n_filos, &dta, forks);
	return EXIT_SUCCESS;
}
