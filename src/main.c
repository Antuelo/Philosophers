/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 22:16:08 by anoviedo          #+#    #+#             */
/*   Updated: 2025/09/25 15:17:56 by anoviedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	main(int ac, char **av)
{
	long	*args;

	if (checker(ac, av + 1, args))
		return (1);
	printf("termina con exito\n");
	return (0);
}
