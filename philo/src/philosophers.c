/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:58:44 by mmarinov          #+#    #+#             */
/*   Updated: 2024/12/28 14:06:25 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// Obtener el tiempo actual en milisegundos
long long get_time_ms(void) {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

// Imprimir el estado del filósofo (pensando, comiendo, durmiendo)
void print_status(t_philosopher *philosopher, char *status) {
    pthread_mutex_lock(&philosopher->data->print_lock);
    long long current_time = get_time_ms() - philosopher->data->start_time;
    printf("%lld %d %s\n", current_time, philosopher->id, status);
    pthread_mutex_unlock(&philosopher->data->print_lock);
}

// Función de la rutina del filósofo
void *philosopher_routine(void *arg) {
    t_philosopher *philosopher = (t_philosopher *)arg;

    while (TRUE) {
        print_status(philosopher, "is thinking");
        take_forks(philosopher);
        print_status(philosopher, "is eating");
        usleep(1000);  // Comer durante 1 milisegundo (ajustable)
        put_forks(philosopher);
        print_status(philosopher, "is sleeping");
        usleep(1000);  // Dormir durante 1 milisegundo (ajustable)
    }
    return NULL;
}

// Tomar los tenedores
void take_forks(t_philosopher *philosopher) {
    pthread_mutex_lock(philosopher->left_fork);
    print_status(philosopher, "has taken a left fork");
    pthread_mutex_lock(philosopher->right_fork);
    print_status(philosopher, "has taken a right fork");
}

// Dejar los tenedores
void put_forks(t_philosopher *philosopher) {
    pthread_mutex_unlock(philosopher->right_fork);
    pthread_mutex_unlock(philosopher->left_fork);
}

// Inicializar los filósofos
int init_philosophers(t_data *data, t_philosopher **philosophers) {
    int i;

    *philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
    if (!*philosophers) return -1;

    for (i = 0; i < data->num_philosophers; i++) {
        (*philosophers)[i].id = i + 1;
        (*philosophers)[i].meals_eaten = 0;
        (*philosophers)[i].last_meal_time = get_time_ms();
        (*philosophers)[i].data = data;
        (*philosophers)[i].left_fork = &data->forks[i];
        (*philosophers)[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
    }
    return 0;
}

// Inicializar los datos globales
void init_data(t_data *data, int num_philosophers) {
    data->num_philosophers = num_philosophers;
    data->start_time = get_time_ms();
    data->stop_flag = 0;

    data->forks = malloc(sizeof(pthread_mutex_t) * num_philosophers);
    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_init(&data->forks[i], NULL);
    }
    pthread_mutex_init(&data->print_lock, NULL);
}

int main(int argc, char **argv) {
    t_data data;
    t_philosopher *philosophers;
   //  pthread_t death_thread;

    if (argc != 2) {
        printf("Usage: ./philosophers <number_of_philosophers>\n");
        return 1;
    }

    int num_philosophers = atoi(argv[1]);
    init_data(&data, num_philosophers);
    init_philosophers(&data, &philosophers);

    // Crear hilos para los filósofos
    for (int i = 0; i < num_philosophers; i++) {
        pthread_create(&philosophers[i].thread, NULL, philosopher_routine, &philosophers[i]);
    }

    // Esperar a que los filósofos terminen (en este caso, nunca termina)
    for (int i = 0; i < num_philosophers; i++) {
        pthread_join(philosophers[i].thread, NULL);
    }

    return 0;
}
