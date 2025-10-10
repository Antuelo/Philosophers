/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:48:43 by anoviedo          #+#    #+#             */
/*   Updated: 2025/10/09 23:14:14 by anoviedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static	void case2(t_philo *ph, int *f1, int *f2)
{
	*f1 = ph->right;
	*f2 = ph->left;
}

static	void case3(t_philo *ph, int *f1, int *f2)
{
	*f1 = ph->left;
	*f2 = ph->right;
}
/*
	Tomar forks con anti-deadlock:
	- 1 filósofo: toma 1 fork, espera t_die, suelta y corta (stop=1).
	- N>1: impares left->right, pares right->left.
	- Loggea cada toma con "has taken a fork".
*/
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
		safe_usleep(g, g->t_die);
		pthread_mutex_unlock(&g->forks[ph->left]);
		set_s(g, 1);
		return ;
	}
	if (ph->id % 2 == 0)
		case2(ph, &f1, &f2);
	else
		case3(ph, &f1, &f2);
	pthread_mutex_lock(&g->forks[f1]);
	log_action(ph, "has taken a fork");
	pthread_mutex_lock(&g->forks[f2]);
	log_action(ph, "has taken a fork");
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
		return ;
	pthread_mutex_unlock(&g->forks[ph->left]);
	pthread_mutex_unlock(&g->forks[ph->right]);
}
