/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 22:16:44 by anoviedo          #+#    #+#             */
/*   Updated: 2025/10/03 15:31:42 by anoviedo         ###   ########.fr       */
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

/*
n 			=	quantities philosophers
start_ms 	= 	start timestamp
print 		=	para no mezclar printf
*forks 		= 	array de mutex ... tenedores
must_eat 	=	-1 si no se pasó
*/
typedef struct s_args
{
	int				n;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			start_ms;
	long			must_eat;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	int				stop;
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

#endif
