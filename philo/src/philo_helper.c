/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:19:27 by mmarinov          #+#    #+#             */
/*   Updated: 2025/01/21 16:05:41 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long get_time_in_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_atoi(char *s)
{
    int	res = 0;
    int	sign = 1;
    int i = 0;

    while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
        i++;
    if (s[i] == '-' || s[i] == '+')
    {
        if (s[i] == '-')
            sign = -1;
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9')
    {
        res  = res * 10 + (s[i] - '0');
        i++;
    }
    return (res * sign);
}

void	*monitor_philo(void *arg)
{
    t_philosopher *philosophers = (t_philosopher *)arg;
    int num_philosophers = philosophers[0].data->num_philosophers;
    int meals_required = philosophers[0].data->n_times_each_phil_must_eat;

    while (1)
    {
        int all_fed = 1;
        int i = 0;
        while (i < num_philosophers)
        {
            long current_time = get_time_in_ms();
            if (current_time - philosophers[i].last_meal_time > philosophers[i].data->time_to_die)
            {
                printf("%ld %d died\n", current_time, philosophers[i].id);
                philosophers[i].is_dead = 1;
                return (NULL);
            }
            if (meals_required > 0 && philosophers[i].meals_eaten < meals_required)
                all_fed = 0;
            i++;
        }
        if (all_fed)
        {
            philosophers[0].data->all_fed = 1;
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}

void	*init_philo_thread(void *arg)
{
    t_philosopher *philosophers = (t_philosopher *)arg;
    init_philosophers(philosophers, philosophers[0].left_fork, philosophers[0].data);
    return (NULL);
}

