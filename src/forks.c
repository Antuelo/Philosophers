/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:48:43 by anoviedo          #+#    #+#             */
/*   Updated: 2025/10/28 13:13:11 by anoviedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static	void	distribution(t_philo *ph, int *f1, int *f2)
{
	*f1 = ph->left;
	*f2 = ph->right;
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

static int	take_forks_sequence(t_philo *ph, t_args *g, int f1, int f2)
{
	pthread_mutex_lock(&g->forks[f1]);
	log_action(ph, "has taken a fork");
	if (get_stop(g))
	{
		pthread_mutex_unlock(&g->forks[f1]);
		return (0);
	}
	pthread_mutex_lock(&g->forks[f2]);
	log_action(ph, "has taken a fork");
	if (get_stop(g))
	{
		pthread_mutex_unlock(&g->forks[f1]);
		pthread_mutex_unlock(&g->forks[f2]);
		return (0);
	}
	return (1);
}

void	take_forks(t_philo *ph)
{
	t_args	*g;
	int		left;
	int		right;

	g = ph->g;
	if (g->n == 1)
	{
		pthread_mutex_lock(&g->forks[ph->left]);
		log_action(ph, "has taken a fork");
		safe_usleep(g, g->t_die + 10);
		pthread_mutex_unlock(&g->forks[ph->left]);
		return ;
	}
	if (ph->id != g->n)
		distribution(ph, &left, &right);
	else
		distribution(ph, &right, &left);
	if (!take_forks_sequence(ph, g, left, right))
		return ;
}

/*void	take_forks(t_philo *ph)
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
	if (ph->id != g->n)
		distribution(ph, &f1, &f2);
	else
		distribution(ph, &f2, &f1);
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
}*/
