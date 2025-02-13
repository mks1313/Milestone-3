/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:33:46 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/13 19:08:44 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		error_exit("Wrong input!\n"
			GR"Correct is (example) : ./philo 3 500 200 200 [4]\n"RES);
	}
	if (ft_atoi(av[1]) > 200)
		error_exit("Error: Number of the Philos is too big!(max = 200)");
	while (i < ac)
	{
		if (ft_atoi(av[i]) == 0)
			error_exit("Error: Params shoud be a zero number!");
		i++;
	}
	return (1);
}

static void	start(int ac, char **av, t_dta *dta)
{
	if (!check_args(ac, av))
		error_exit("Error: Something goes wrong my friend :(!");
	dta->n_filos = ft_atoi(av[1]);
	dta->tto_die = ft_atoi(av[2]);
	dta->tto_eat = ft_atoi(av[3]);
	dta->tto_sleep = ft_atoi(av[4]);
	if (ac == 6)
		dta->n_meals = ft_atoi(av[5]);
	else
		dta->n_meals = -1;
}

static void	create_threads(t_dta *dta, pthread_t *monitor_thread)
{
	int	i;

	i = 0;
	while (i < dta->n_filos)
	{
		if (pthread_create(&dta->filos[i].thread, NULL,
				lifecycle, (void *)&dta->filos[i]) != 0)
			error_exit("Error creating thread\n");
		i++;
	}
	if (pthread_create(monitor_thread, NULL, monitor, (void *)dta) != 0)
		error_exit("Error creating monitor thread\n");
}

static void	join_threads(t_dta *dta, pthread_t monitor_thread)
{
	int	i;

	i = 0;
	while (i < dta->n_filos)
	{
		pthread_join(dta->filos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

int	main(int ac, char **av)
{
	t_dta		*dta;
	pthread_t	monitor_thread;

	dta = malloc(sizeof(t_dta));
	if (!dta)
		return (1);
	start(ac, av, dta);
	init_dta(dta);
	if (init_filos(dta))
		return (1);
	create_threads(dta, &monitor_thread);
	join_threads(dta, monitor_thread);
	free_resources(dta);
	free(dta);
	return (0);
}
