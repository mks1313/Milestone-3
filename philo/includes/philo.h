/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:28:09 by mmarinov          #+#    #+#             */
/*   Updated: 2025/01/24 15:27:42 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_filo
{
	pthread_t		thread;// Hilo del filósofo
	int				id;// Identificador del filósofo
	int				meals_done;// Número de comidas realizadas
	int				eating;// Indicador de si está comiendo
	size_t			last_meal;// Tiempo de la última comida
	size_t			time_start;// Tiempo de inicio del programa
	pthread_mutex_t	*r_fork;// Puntero al tenedor a la derecha
	pthread_mutex_t	*l_fork;// Puntero al tenedor a la izquierda
	struct s_dta	*dta; //Puntero a la estructura de datos
}					t_filo;

typedef struct s_dta
{
	pthread_mutex_t	dead_lock; // Mutex para proteger dead_flag
	pthread_mutex_t	meal_lock; // Mutex para proteger el acceso a las comidas
	pthread_mutex_t	write_lock;// Mutex para controlar la salida de datos
	t_filo			**filos; // Array de filósofos
	int				dead_flag; // Indicador de si algún filósofo ha muerto
	size_t			tto_die;// Tiempo máximo sin comer antes de morir
	size_t			tto_eat;// Tiempo que toma comer
	size_t			tto_sleep;// Tiempo que toma dormir
	int				n_filos;// Número total de filósofos
	int				n_tto_eat;// Núm de veces que cada filósofo debe comer
}					t_dta;

int			ft_atoi(char *s);
long long	get_time(void);
int			check_input(char *arg);
void		init_forks(pthread_mutex_t *forks, int n_filos);

#endif
