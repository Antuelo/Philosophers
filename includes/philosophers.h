/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 22:16:44 by anoviedo          #+#    #+#             */
/*   Updated: 2025/10/15 13:40:46 by anoviedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo t_philo;

/*
n 			=	number to philosophers
start_ms 	= 	start timestamp
print 		=	para no mezclar printf
*forks 		= 	array de mutex ... tenedores
must_eat 	=	-1 si no se pasó el 5to elemento
philos			guarda el array para que el monitor lo vea

*/
typedef struct s_args
{
	int				n;
	int				stop;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			start_ms;
	long			must_eat;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	pthread_mutex_t	state;
	t_philo			*philos;
}					t_args;

/*
id =			numero de philos
left & right	indices de fork
*g				puntero a lo compartido
*/
typedef struct s_philo
{
	int				id;
	int				left;
	int				right;
	long			last_meal;
	int				meals;
	t_args			*g;
}					t_philo;

/*checker and free*/
int					checker(int n, char **args, long **dest);

/*body*/
long				now_ms(void);
int					preparing_table(t_args *g, long *nums, int ac);
t_philo				*init_philos(t_args *g);
int					timetoeat(t_philo *ph, t_args *g);
void				log_action(t_philo *ph, const char *msg);
void				safe_usleep(t_args *g, long ms);

/* philosophers loops and stubs to forks */
void				*routine_philo(void *p);
void				take_forks(t_philo *ph);
void				put_forks(t_philo *ph);

/* locks de estado y helpers de stop/monitor */
void				*monitor(void *p);
int					get_stop(t_args *g);
void				set_s(t_args *g, int v);

/*free everythingggg */
void	destroy_and_free(t_args *g, t_philo *ph);

#endif
