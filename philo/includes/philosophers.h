/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:28:09 by mmarinov          #+#    #+#             */
/*   Updated: 2025/01/21 16:05:11 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

// Estructura para un filósofo
typedef struct s_philosopher
{
    int				id;
    long long		last_meal_time;
    int				meals_eaten;
    pthread_t		thread;
    pthread_mutex_t	*left_fork;
    pthread_mutex_t	*right_fork;
    struct s_data	*data;
    int				is_dead;
}	t_philosopher;

// Estructura de datos compartidos
typedef struct s_data
{
    int	num_philosophers;
    int	time_to_die;
    int	time_to_eat;
    int	time_to_sleep;
    int	n_times_each_phil_must_eat;
    int	all_fed;
}	t_data;

int		ft_atoi(char *s);
long	get_time_in_ms();
void	init_forks(pthread_mutex_t *forks, int num_of_forks);
void	init_philosophers(t_philosopher *philosophers, pthread_mutex_t *forks, t_data *data);
void	*philosopher_routine(void *arg);
void	create_threads(t_philosopher *philosophers, int num_philosophers);
void	*monitor_philo(void *arg);
void	*init_philo_thread(void *arg);

#endif
