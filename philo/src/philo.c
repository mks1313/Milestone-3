/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:17:12 by mmarinov          #+#    #+#             */
/*   Updated: 2025/01/28 16:59:40 by mmarinov         ###   ########.fr       */
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
	size_t t_last_meal;

	i = 0;
	while (i < dta->n_filos)
	{
		pthread_mutex_lock(&dta->meal_lock);
		t_last_meal = get_time() - dta->filos[i]->last_meal;
		pthread_mutex_unlock(&dta->meal_lock);
		if (t_last_meal > dta->tto_die)
		{
			pthread_mutex_lock(&dta->write_lock);
			printf("Philosopher %d has died\n", dta->filos[i]->id);
			pthread_mutex_unlock(&dta->write_lock);
			dta->dead_flag = 1;
			break;
		}
	}
}
int	main(int argc, char **argv)
{
	t_dta	dta;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Numbers of parameters is incorrect!\n");
		return (EXIT_FAILURE);
	}
	pthread_mutex_t	forks[ft_atoi(argv[1])];
	init_forks(forks, ft_atoi(argv[1]));
	init_program(&dta, forks, argv);
	create_filo_threads(dta.filos, dta.n_filos);
	monitor_filos(&dta);
	cleanup(dta.filos, dta.n_filos, &dta, forks);
	return (EXIT_SUCCESS);
}
