/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 23:23:35 by anoviedo          #+#    #+#             */
/*   Updated: 2025/10/21 00:12:35 by anoviedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *p)
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
		usleep(500);
	}
	return (NULL);
}
