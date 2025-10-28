/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 23:23:35 by anoviedo          #+#    #+#             */
/*   Updated: 2025/10/28 13:08:37 by anoviedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_philosopher(t_args *g, int i, int *full)
{
	long	now;
	long	diff;

	now = now_ms();
	pthread_mutex_lock(&g->state);
	diff = now - g->philos[i].last_meal;
	if (diff > g->t_die)
	{
		pthread_mutex_unlock(&g->state);
		set_s(g, 1);
		pthread_mutex_lock(&g->print);
		printf("%ld %d died\n", now - g->start_ms, g->philos[i].id);
		pthread_mutex_unlock(&g->print);
		return (0);
	}
	if (g->must_eat != -1 && g->philos[i].meals < g->must_eat)
		*full = 0;
	pthread_mutex_unlock(&g->state);
	return (1);
}

void	*monitor(void *p)
{
	t_args	*g;
	int		i;
	int		full;

	g = (t_args *)p;
	while (!get_stop(g))
	{
		i = 0;
		full = 1;
		while (i < g->n && !get_stop(g))
		{
			if (!check_philosopher(g, i, &full))
				return (NULL);
			i++;
		}
		if (g->must_eat != -1 && full)
			return (set_s(g, 1), NULL);
		usleep(1000);
	}
	return (NULL);
}

/*void	*monitor(void *p)
{
	t_args	*g;
	int		i;
	int		full;
	long	now;
	long	diff;

	g = (t_args *)p;
	while (!get_stop(g))
	{
		i = 0;
		full = 1;
		now = now_ms();
		while (i < g->n && !get_stop(g))
		{
			pthread_mutex_lock(&g->state);
			diff = now - g->philos[i].last_meal;
			if (diff > g->t_die)
			{
				pthread_mutex_unlock(&g->state);
				set_s(g, 1);
				pthread_mutex_lock(&g->print);
				printf("%ld %d died\n", now - g->start_ms, g->philos[i].id);
				pthread_mutex_unlock(&g->print);
				return (NULL);
			}
			if (g->must_eat != -1 && g->philos[i].meals < g->must_eat)
				full = 0;
			pthread_mutex_unlock(&g->state);
			i++;
		}
		if (g->must_eat != -1 && full)
			return (set_s(g, 1), NULL);
		usleep(1000);
	}
	return (NULL);
}*/
