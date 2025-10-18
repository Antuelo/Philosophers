/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:44:22 by emurillo          #+#    #+#             */
/*   Updated: 2025/05/31 15:12:36 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// The thread if not sleep will take longer than the main to finish, so
// using usleep will wait for it to finish, same that the pthread_join func

int	n;

void	*test(void *arg)
{
	int			i;
	int			n;
	pthread_t	thread_id;

	thread_id = pthread_self();
	i = 1;
	n = *(int *) arg;
	printf("Initiating thread ID = {%lu}\n", thread_id);
	while (i < n)
	{
		printf("Test #%d\n", i);
		i++;
		usleep(50);
	}
	return (NULL);
}

void	*change_n(void *arg)
{
	int	n;

	n = *(int *) arg;
	if (n > 2)
		n = n + 50;
	printf("Value of n modified.\n");
	return (NULL);
}

int	main(int ac, char **av)
{
	pthread_t	thread1;
	pthread_t	thread2;

	if (ac != 2 || !av[1])
		return (1);
	n = atoi(av[1]);
	if (n < 2)
		return (1);
	printf("Value of n before: %d\n", n);
	pthread_create(&thread1, NULL, test, (void *)&n);
	pthread_create(&thread2, NULL, change_n, (void *)&n);
	usleep(1000);
	// pthread_cancel(thread1);
	pthread_join(thread1, NULL);
	printf("Value of n after: %d\n", n);
	return (0);
}
