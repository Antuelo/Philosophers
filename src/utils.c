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

/*
	Recibe: el filósofo (ph) y un mensaje corto (“has taken a fork”,
	“is eating”, etc.).

	toma el mutex print, calcula timestamp = now_ms() - start_ms,
	y loggea "<ms> <id> <msg>".
	Controla: si g->stop ya está activo, no imprime
	(evita basura después de una muerte).
	Garantiza: no se pisan los prints entre threads (mutex).
	Devuelve: nada. Solo side-effects (stdout).

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
}*/
void	log_action(t_philo *ph, const char *msg)
{
	t_args	*g;
	long	t;

	g = ph->g;
	if (get_stop(g))
		return ;
	pthread_mutex_lock(&g->print);
	if (!get_stop(g))
	{
		t = now_ms() - g->start_ms;
		printf("%ld %d %s\n", t, ph->id, msg);
	}
	pthread_mutex_unlock(&g->print);
}

/*
	Recibe: el contexto global (g) y una duración en milisegundos.
	Hace: duerme en pequeños intervalos (p. ej. 500 µs) hasta cumplir ms.
	Controla: corta temprano si g->stop se activa (respuesta rápida al
	“death check”).
	Ventaja: permite temporizaciones precisas sin bloquear un largo
	usleep(ms*1000) que ignora el stop.
	Devuelve: nada. Solo gestiona la espera cooperando con el monitor.
*/
void	safe_usleep(t_args *g, long ms)
{
	long	end;

	end = now_ms() + ms;
	while (!get_stop(g) && now_ms() < end)
		usleep(500);
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
