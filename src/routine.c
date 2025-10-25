/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:15:57 by anoviedo          #+#    #+#             */
/*   Updated: 2025/10/21 00:06:30 by anoviedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine_philo(void *p)
{
	t_philo	*ph;
	t_args	*g;

	ph = (t_philo *)p;
	g = ph->g;
	if (ph->id % 2 == 0)
		safe_usleep(g, g->t_eat * 0.9);
	while (!get_stop(g))
	{
		take_forks(ph);
		if (get_stop(g))
			return(put_forks(ph), NULL);
		log_action(ph, "is eating");
		pthread_mutex_lock(&g->state);
		ph->last_meal = now_ms();
		pthread_mutex_unlock(&g->state);
		safe_usleep(g, g->t_eat);
		pthread_mutex_lock(&g->state);
		ph->meals++;
		pthread_mutex_unlock(&g->state);
		put_forks(ph);
		log_action(ph, "is sleeping");
		if (get_stop(g))
			break;
		safe_usleep(g, g->t_sleep);
		log_action(ph, "is thinking");
		if (g->n % 2 == 1)
			safe_usleep(g, 1);
	}
	return (NULL);
}

/*		printf("DEBUG: %ld - Philosopher %d empieza a to eat\n", now_ms() - g->start_ms, ph->id);		ph->last_meal = now_ms();
*/
