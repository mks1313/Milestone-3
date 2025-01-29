/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:28:09 by mmarinov          #+#    #+#             */
/*   Updated: 2025/01/29 15:22:37 by mmarinov         ###   ########.fr       */
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
	bool			is_eating;// Indicador de si está comiendo
	size_t			last_meal;// Tiempo de la última comida
	pthread_mutex_t	*r_fork;// Puntero al tenedor a la derecha
	pthread_mutex_t	*l_fork;// Puntero al tenedor a la izquierda
	struct s_dta	*dta; //Puntero a la estructura de datos
}					t_filo;

typedef struct s_dta
{
	pthread_mutex_t	dead_lock; // Mutex para proteger dead_flag
	pthread_mutex_t	meal_lock; // Mutex para proteger el acceso a las comidas
	pthread_mutex_t	write_lock;// Mutex para controlar la salida de datos
	t_filo			*filos; // Array de filósofos
	int				dead_flag; // Indicador de si algún filósofo ha muerto
	size_t			tto_die;// Tiempo máximo sin comer antes de morir
	size_t			tto_eat;// Tiempo que toma comer
	size_t			tto_sleep;// Tiempo que toma dormir
	int				n_filos;// Número total de filósofos
	int				n_meals;// Núm de veces que cada filósofo debe comer
}					t_dta;

// Utils
int			ft_atoi(char *s);
long long	curr_time(void);
void		sleep_precise(long mls);

// Inicialization & cleaning
void		init_forks(pthread_mutex_t *forks, int n_filos);
void		init_program(t_dta *dta, pthread_mutex_t *forks, char **argv);
void		wash(t_filo *filos, int n_filos, tda *dta, pthread_mutex_t *forks);

// Rutines of the Philos
void		create_filo_threads(t_filo *filo, int n_filos);
void		*filo_routine(void *arg);
void		eat(t_filo *filo);
void		think(t_filo *filo);
void		sleep_filo(t_filo *filo);

#endif
