/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 22:25:56 by anoviedo          #+#    #+#             */
/*   Updated: 2025/10/10 14:58:02 by anoviedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_and_free(t_args *g, t_philo *ph)
{
	int	i;

	i = 0;
	while (i < g->n)
	{
		pthread_mutex_destroy(&g->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&g->print);
	pthread_mutex_destroy(&g->state);
	free(g->forks);
	free(ph);
}
