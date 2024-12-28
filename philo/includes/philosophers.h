#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

// Estructura para un filósofo
typedef struct s_philosopher {
    int id;                         // ID del filósofo
    long long last_meal_time;       // Último tiempo de comida
    int meals_eaten;                // Número de comidas
    pthread_t thread;               // Hilo del filósofo
    pthread_mutex_t *left_fork;     // Tenedor izquierdo
    pthread_mutex_t *right_fork;    // Tenedor derecho
    struct s_data *data;            // Datos compartidos
} t_philosopher;

// Estructura de datos compartidos
typedef struct s_data {
    int num_philosophers;           // Número de filósofos
    long long start_time;           // Hora de inicio
    pthread_mutex_t *forks;         // Array de mutex para los tenedores
    pthread_mutex_t print_lock;     // Mutex para evitar que los filósofos impriman al mismo tiempo
    int stop_flag;                  // Bandera para detener programa (por si hay hambre, deadlock)
} t_data;

long long get_time_ms(void);
void    *philosopher_routine(void *philosopher);
void    take_forks(t_philosopher *philosopher);
void    put_forks(t_philosopher *philosopher);
void    *check_death(void *philosopher);
void    print_status(t_philosopher *philosopher, char *status);
int     init_philosophers(t_data *data, t_philosopher **philosophers);
void    init_data(t_data *data, int num_philosophers);

#endif
