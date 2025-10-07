/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timetoeat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 23:57:17 by anoviedo          #+#    #+#             */
/*   Updated: 2025/09/28 00:09:01 by anoviedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

static void	*routine_hello(void *p)
{
	t_args	*g;

	g = (t_args *)p;
	pthread_mutex_lock(&g->print);
	printf("t=%ldms hello from thread\n", now_ms() - g->start_ms);
	pthread_mutex_unlock(&g->print);
	return (NULL);
}

/*
	función que arma la “mesa” compartida; recibe config
 	parseada y cantidad de args para saber si vino el 5º
	*g = globals ...
	*/
int	preparing_table(t_args *g, long *nums, int ac)
{
	int	i;

	i = 0;
	g->n = (int)nums[0];
	g->t_die = nums[1];
	g->t_eat = nums[2];
	g->t_sleep = nums[3];
	if (ac == 6)
		g->must_eat = nums[4];
	else
		g->must_eat = -1;
	g->stop = 0;
	g->forks = malloc(sizeof(pthread_mutex_t) * g->n);
	if (!g->forks)
		return (perror("malloc, fork"), 1);
	while (i < g->n)
	{
		if (pthread_mutex_init(&g->forks[i], NULL) != 0)
			return (perror("mutex_init fork"), 1);
		i++;
	}
	if (pthread_mutex_init(&g->print, NULL) != 0)
		return (perror("mutex_init print"), 1);
	g->start_ms = now_ms();
	return (0);
}

t_philo	*init_philos(t_args *g)
{
	t_philo	*ph;
	int		i;

	i = 0;
	ph = (t_philo *)malloc(sizeof(t_philo) * g->n);
	if (!ph)
		return (perror("malloc philo"), NULL);
	while (i < g->n)
	{
		ph[i].id = i + 1;
		ph[i].left = i;
		ph[i].right = (i + 1) % g->n;
		ph[i].last_meal = g->start_ms;
		ph[i].meals = 0;
		ph[i].g = g;
		i++;
	}
	return (ph);
}

int	timetoeat(t_philo *ph, t_args *g)
{
	pthread_t	tid;

	(void)ph;
	if (pthread_create(&tid, NULL, routine_hello, g) != 0)
		return (perror("pthread_create"), 1);
	if (pthread_join(tid, NULL) != 0)
		return (perror("pthread_join"), 1);
	return (0);
}
