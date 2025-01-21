/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:58:44 by mmarinov          #+#    #+#             */
/*   Updated: 2025/01/21 16:07:24 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_forks(pthread_mutex_t *forks, int num_of_forks)
{
    int	i;

    i = 0;
    while (i < num_of_forks)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}

void	init_philosophers(t_philosopher *philosophers, pthread_mutex_t *forks, t_data *data)
{
    int	i;

    i = 0;
    while (i < data->num_philosophers)
    {
        philosophers[i].id = i + 1;
        philosophers[i].meals_eaten = 0;
        philosophers[i].data = data;
        philosophers[i].left_fork = &forks[i];
        philosophers[i].right_fork = &forks[(i + 1) % data->num_philosophers];
        philosophers[i].last_meal_time = get_time_in_ms();
        philosophers[i].is_dead = 0;
        i++;
    }
}

void	*philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    while (!philo->is_dead && !philo->data->all_fed)
    {
        printf("%ld %d is thinking\n", get_time_in_ms(), philo->id);
        pthread_mutex_lock(philo->left_fork);
        printf("%ld %d has taken a fork\n", get_time_in_ms(), philo->id);
        pthread_mutex_lock(philo->right_fork);
        printf("%ld %d has taken a fork\n", get_time_in_ms(), philo->id);
        printf("%ld %d is eating\n", get_time_in_ms(), philo->id);
        philo->last_meal_time = get_time_in_ms();
        usleep(philo->data->time_to_eat * 1000);
        philo->meals_eaten++;
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        printf("%ld %d is sleeping\n", get_time_in_ms(), philo->id);
        usleep(philo->data->time_to_sleep * 1000);
    }
    return (NULL);
}

void	create_threads(t_philosopher *philosophers, int num_philosophers)
{
    int i;

    i = 0;
    while (i < num_philosophers)
    {
        pthread_create(&philosophers[i].thread, NULL, philosopher_routine, &philosophers[i]);
        i++;
    }
}

int	main(int argc, char **argv)
{
    int i;

    if (argc < 5 || argc > 6)
    {
        printf("Use: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_philosophers_must_eat]\n");
        return (1);
    }

    t_data data;
    data.num_philosophers = ft_atoi(argv[1]);
    data.time_to_die = ft_atoi(argv[2]);
    data.time_to_eat = ft_atoi(argv[3]);
    data.time_to_sleep = ft_atoi(argv[4]);
    data.all_fed = 0;

    if (argc == 6)
        data.n_times_each_phil_must_eat = ft_atoi(argv[5]);
    else
        data.n_times_each_phil_must_eat = -1;

    pthread_t monitor_thread;
    pthread_mutex_t forks[data.num_philosophers];
    t_philosopher philosophers[data.num_philosophers];

    init_forks(forks, data.num_philosophers);
    init_philosophers(philosophers, forks, &data);

    // Crear hilos para los filósofos
    create_threads(philosophers, data.num_philosophers);

    // Crear el hilo de monitoreo para verificar si algún filósofo muere
    pthread_create(&monitor_thread, NULL, monitor_philo, philosophers);

    // Esperar a que termine el hilo de monitoreo
    pthread_join(monitor_thread, NULL);

    // Esperar a que terminen los hilos de los filósofos
    i = 0;
    while (i < data.num_philosophers)
    {
        pthread_join(philosophers[i].thread, NULL);
        i++;
    }

    return (0);
}
