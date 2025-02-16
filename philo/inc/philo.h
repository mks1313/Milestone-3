/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:57:20 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/07 15:01:50 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

# ifndef COLOR_H
#  define COLOR_H

#  define RED   "\033[1;31m"
#  define GR    "\033[1;32m"
#  define YEL   "\033[1;33m"
#  define BL    "\033[1;34m"
#  define MAG   "\033[1;35m"
#  define CYAN  "\033[1;36m"
#  define RES   "\033[0m"
# endif

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_filo
{
	int				id;// Identificador del filósofo
	pthread_t		thread;// Hilo del filósofo
	//bool			eating;// Indicador de si está comiendo
	long long		last_meal;// Tiempo de la última comida
	t_fork			*rf;// Puntero al tenedor a la derecha
	t_fork			*lf;// Puntero al tenedor a la izquierda
	int				meals_done;// Número de comidas realizadas
	struct s_dta	*dta; //Puntero a la estructura de datos
}					t_filo;

typedef struct s_dta
{
	pthread_mutex_t	dead_lock; // Mutex para proteger dead_flag
	pthread_mutex_t	write_lock;// Mutex para controlar la salida de datos
	pthread_mutex_t	meal_lock;
	t_filo			*filos; // Array de filósofos
	t_fork			*forks; //Array de tenedorres
	bool			death; // Indicador de si algún filósofo ha muerto
	bool			full;
	long long		tto_die;// Tiempo máximo sin comer antes de morir
	long long		tto_eat;// Tiempo que toma comer
	long long		tto_sleep;// Tiempo que toma dormir
	long long		start_time;// Tiempo de inicio de la simulacion
	int				n_filos;// Número total de filósofos
	int				n_meals;// Núm de veces que cada filósofo debe comer
}					t_dta;

int			ft_atoi(const char *s);
long long	time_now(void);
int			ft_usleep(long long time);
void		error_exit(const char *error);
void		ft_prints(t_dta *dta, int id, const char *acts);
void		take_forks(t_filo *filo);
void		put_forks(t_filo *filo);
void		eat(t_filo *filo);
void		think(t_filo *filo);
void		sleep_filo(t_filo *filo);
void		*lifecycle(void *arg);
void		check_death(t_dta *dta);
void		*monitor(void *arg);
void		init_dta(t_dta *dta);
int			init_filos(t_dta *dta);
void		free_resources(t_dta *dta);
int			check_args(int ac, char **av);

#endif