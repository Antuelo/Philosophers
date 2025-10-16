/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:15:57 by anoviedo          #+#    #+#             */
/*   Updated: 2025/10/16 00:57:29 by anoviedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
t_args g: “global/shared”. Config y recursos comunes: cantidad de
filósofos, tiempos, start_ms, must_eat, stop, print (mutex de logs) y
forks (array de mutex/tenedores).
g.n: número de filósofos (y de forks).
g.t_die / g.t_eat / g.t_sleep: tiempos en ms para morir si no come,
comer y dormir.
g.start_ms: timestamp inicial de la simulación para calcular logs relativos.
g.must_eat: cuántas veces debe comer cada filósofo (-1 si no se exige).
g.print: mutex para que los printf no se mezclen.
g.forks: array de mutex; cada índice es un tenedor entre dos filósofos.
g.stop: bandera para cortar todo (muerte o condición de fin).
t_philo ph: datos del filósofo individual.
ph.id: identificador humano (1..n) para los logs.
ph.left / ph.right: índices de forks que usa ese filósofo.
ph.last_meal: último momento en que empezó a comer (para calcular muerte).
ph.meals: contador de comidas (para must_eat).
ph.g: puntero al t_args compartido (acceso a tiempos/mutexes).
log_action: imprime “<ms> <id> <msg>” protegido por g.print.
safe_usleep: duerme en tramos cortos, chequeando g.stop.
routine_philo: loop pensar→(forks)→comer→soltar→dormir, respetando stop.
take_forks / put_forks: tomar/soltar forks (ahora stubs; luego mutex).
timetoeat: crea/join de los threads, uno por filósofo.
	Rutina principal del filósofo:
	- Ciclo: pensar -> (tomar forks) -> comer -> soltar -> dormir.
	- Actualiza last_meal al comenzar a comer.
	- Incrementa meals tras terminar de comer.
	- Usa log_action y safe_usleep; respeta g->stop.
*/
void	*routine_philo(void *p)
{
	t_philo	*ph;
	t_args	*g;

	ph = (t_philo *)p;
	g = ph->g;
	if ((g->n % 2) && (ph->id % 2 == 0))
    	safe_usleep(g, g->t_eat / 2);
	while (!get_stop(g))
	{
		if (ph->id % 2 == 0)
			safe_usleep(g, 1);
		take_forks(ph);
		if (get_stop(g))
			return(put_forks(ph), NULL);
		pthread_mutex_lock(&g->state);
		ph->last_meal = now_ms();
		pthread_mutex_unlock(&g->state);
		log_action(ph, "is eating");
		safe_usleep(g, g->t_eat);
		pthread_mutex_lock(&g->state);
		ph->meals++;
		pthread_mutex_unlock(&g->state);
		put_forks(ph);
		log_action(ph, "is sleeping");
		safe_usleep(g, g->t_sleep);
		log_action(ph, "is thinking");
	}
	return (NULL);
}

/*		if ((g->n % 2) && (ph->id % 2 == 0)
			safe_usleep(g, g->t_eat/2);
		if (!(g->n % 2) && (ph->id % 2 == 0))
			safe_usleep(g, 1);

			if ((g->n % 2) && (ph->id % 2 == 0))
		safe_usleep(g, g->t_eat / 2);
	else if (!(g->n % 2) && (ph->id % 2 == 0))
		safe_usleep(g, 1);
*/
