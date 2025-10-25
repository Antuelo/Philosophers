/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:48:43 by anoviedo          #+#    #+#             */
/*   Updated: 2025/10/16 01:00:29 by anoviedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static	void case2(t_philo *ph, int *f1, int *f2)
{
	*f1 = ph->left;
	*f2 = ph->right;
}

static	void case3(t_philo *ph, int *f1, int *f2)
{
	*f1 = ph->right;
	*f2 = ph->left;
}

void	take_forks(t_philo *ph)
{
	t_args	*g;
	int		f1;
	int		f2;

	g = ph->g;
	if (g->n == 1)
	{
		pthread_mutex_lock(&g->forks[ph->left]);
		log_action(ph, "has taken a fork");
		safe_usleep(g, g->t_die + 10);
		pthread_mutex_unlock(&g->forks[ph->left]);
		return ;
	}
	//if (ph->id != g->n)
	if (g->n == 3)
	{
		if (ph->id == 1)
		{
			f1 = ph->left;
			f2 = ph->right;
		}
		else if (ph->id == 2)
		{
			f1 = ph->right;
			f2 = ph->left;
		}
		else // ph->id == 3
		{
			f1 = ph->right;
			f2 = ph->left;
		}
	}
	if (ph->id % 2 == 1)
		case2(ph, &f1, &f2);
	else
		case3(ph, &f1, &f2);
	pthread_mutex_lock(&g->forks[f1]);
	log_action(ph, "has taken a fork");
	if (get_stop(g))
	{
		pthread_mutex_unlock(&g->forks[f1]);
		return ;
	}
	pthread_mutex_lock(&g->forks[f2]);
	log_action(ph, "has taken a fork");
	if (get_stop(g))
	{
		pthread_mutex_unlock(&g->forks[f1]);
		pthread_mutex_unlock(&g->forks[f2]);
		return ;
	}
}

/*
	Soltar forks del filósofo:
	- N==1: nada (ya se soltó en take_forks).
	- N>1: libera ambos forks sin importar el orden.
*/
void	put_forks(t_philo *ph)
{
	t_args	*g;

	g = ph->g;
	if (g->n == 1)
	{
		return ;
	}
	pthread_mutex_unlock(&g->forks[ph->left]);
	pthread_mutex_unlock(&g->forks[ph->right]);
}
