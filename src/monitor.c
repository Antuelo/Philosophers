/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 23:23:35 by anoviedo          #+#    #+#             */
/*   Updated: 2025/10/11 13:58:01 by anoviedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Monitor de la simulación.
	Recibe: puntero a t_args (g), con config y acceso a los filósofos.
	Bucle: mientras stop==0, recorre a todos los filósofos y verifica:
	- Muerte: si now - last_meal > t_die, imprime "<ms> <id> died"
	  protegido por el mutex print y activa stop (set_s(g,1)).
	- must_eat: si must_eat != -1, comprueba si TODOS alcanzaron ese
	  número de comidas; si sí, activa stop y termina.
	Sincronización: lee last_meal y meals bajo el mutex state para
	evitar data races; el flag stop se lee/escribe con get_stop/set_s.
	Temporización: usa un pequeño sleep (~1ms) entre barridos para no
	saturar la CPU y aún así reaccionar rápido (<10ms) ante una muerte.
	Retorno: NULL al finalizar (muerte detectada o condición de fin).
	g = (t_args *)p; → castea el puntero recibido al contexto global.

while (!get_stop(g)) → loop principal; corre mientras no haya “stop” (con mutex).

Setea i=0, full=1, now = now_ms(); → arranca barrida, asume que todos cumplieron must_eat, y toma el tiempo actual una sola vez por vuelta.

while (i < g->n && !get_stop(g)) → recorre filósofos uno por uno, chequeando stop en cada iteración.

pthread_mutex_lock(&g->state); → protege lectura de last_meal y meals.

diff = now - g->philos[i].last_meal; → cuánto hace que este filo no come.

if (diff > g->t_die) → murió: suelta state, loguea "died" con print (mutex), marca stop con set_s(g,1) y sale (return).

Si no murió: si hay must_eat y este filo no llegó, pone full = 0.

pthread_mutex_unlock(&g->state); → libera el candado y pasa al siguiente i++.

Terminada la pasada: si must_eat != -1 y full==1, todos cumplieron → set_s(g,1) y sale.

usleep(1000); → micro pausa (1 ms) para no quemar CPU y repetir la vigilancia.
*/
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
		usleep(1000);
	}
	return (NULL);
}
