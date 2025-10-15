/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timetoeat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 23:57:17 by anoviedo          #+#    #+#             */
/*   Updated: 2025/10/15 14:09:39 by anoviedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*tv time valu of course*/
long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

/*
	init args...
*/
static void init(t_args *g, int ac, long *nums)
{
	g->n = (int)nums[0];
	g->t_die = nums[1];
	g->t_eat = nums[2];
	g->t_sleep = nums[3];
	if (ac == 6)
		g->must_eat = nums[4];
	else
		g->must_eat = -1;
	g->stop = 0;
}
/*	función que arma la “mesa” compartida; recibe config
 	parseada y cantidad de args para saber si vino el 5º
	*g = globals ...
	*/
int	preparing_table(t_args *g, long *nums, int ac)
{
	int	i;

	i = 0;
	init(g, ac, nums);
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
	if (pthread_mutex_init(&g->state, NULL) != 0)
		return (perror("mutex_init state"), 1);
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

/*
	Lanza un thread por filósofo con routine_philo y espera a que terminen.
	Por ahora se detiene cuando g->stop sea 1 (lo manejará el monitor).
*/
int	timetoeat(t_philo *ph, t_args *g)
{
	pthread_t	*tid;
	pthread_t	mon;
	int			i;
	void		*rmon;

	rmon = NULL;
	g->philos = ph;
	tid = (pthread_t *)malloc(sizeof(pthread_t) * g->n);
	if (!tid)
		return (perror("malloc tid"), 1);
	if (pthread_create(&mon, NULL, monitor, g) != 0)
		return (perror("pthread_create monitor"), free(tid), 1);
	i = 0;
	while (i < g->n)
	{
		if (pthread_create(&tid[i], NULL, routine_philo, &ph[i]) != 0)
			return (perror("pthread_crete"), free(tid), 1);
		i++;
	}
	if (pthread_join(mon, &rmon) != 0)
		return (perror("pthread_join monitor"), free(tid), 1);;
	i = -1;
	while (++i < g->n)
		pthread_join(tid[i], NULL);
	free(tid);
	return (0);
}
