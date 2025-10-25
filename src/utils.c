/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:42:32 by anoviedo          #+#    #+#             */
/*   Updated: 2025/10/18 13:40:02 by anoviedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	log_action(t_philo *ph, const char *msg)
{
	t_args	*g;
	long	t;

	g = ph->g;
	pthread_mutex_lock(&g->print);
	if (!g->stop)
	{
		t = now_ms() - g->start_ms;
		printf("%ld %d %s \n", t, ph->id, msg);
	}
	pthread_mutex_unlock(&g->print);
}

void	safe_usleep(t_args *g, long ms)
{
	long	start;
	long	elapsed;

	start = now_ms();
	while (!get_stop(g))
	{
		elapsed = now_ms() - start;
		if (elapsed >= ms)
			break;
		usleep(100);
	}
}

int	get_stop(t_args *g)
{
	int	v;

	pthread_mutex_lock(&g->state);
	v = g->stop;
	pthread_mutex_unlock(&g->state);
	return (v);
}

/*setea stop*/
void set_s(t_args *g, int v)
{
	pthread_mutex_lock(&g->state);
	g->stop = v;
	pthread_mutex_unlock(&g->state);
}
