/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 22:16:08 by anoviedo          #+#    #+#             */
/*   Updated: 2025/10/09 00:02:07 by anoviedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	long	*nums;
	t_args	args;
	t_philo	*philos;

	nums = NULL;
	if (checker(ac, av + 1, &nums))
		return (free(nums), 1);
	if (preparing_table(&args, nums, ac))
		return (free(nums), 1);
	philos = init_philos(&args);
	if (!philos)
		return (free(nums), 1);
	timetoeat(philos, &args);
	free(nums);
	return (0);
}
