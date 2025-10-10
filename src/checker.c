/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoviedo <antuel@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:22:13 by anoviedo          #+#    #+#             */
/*   Updated: 2025/10/10 16:14:25 by anoviedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#define INT_MAX 2147483647

static int	jump(const char *nptr)
{
	int	i;

	i = 0;
	if (nptr[i] == '\0')
		return (0);
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\v'
		|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == ' ')
		i++;
	return (i);
}

long	ft_atol(const char *nptr)
{
	long	num;
	int		neg;
	int		i;

	num = 0;
	neg = 0;
	i = jump(nptr);
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = 1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		num = (num * 10) + nptr[i] - '0';
		i++;
	}
	if (neg == 1)
		num = -num;
	return (num);
}

static int	control_number(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j] == '\0')
		{
			if (args[i][j] && (args[i][j] < '0' || args[i][j] > '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	checker(int n, char **args, long **dest)
{
	int	i;

	i = 0;
	if (n < 5 || n > 6)
		return (printf("Error! Use:\nnumber_of_philosophers\ntime_to_die\n"
				"time_to_eat\ntime_to_sleep\n"
				"[number_of_times_each_philosopher_must_eat]\n"), 1);
	*dest = (long *)malloc(sizeof(long) * (n - 1));
	if (!*dest)
		return (perror("malloc"), 1);
	if (control_number(args))
		return (1);
	while (--n > 0)
	{
		(*dest)[i] = ft_atol(args[i]);
		if ((*dest)[i] < 0)
			return (printf("only possitive number please\n"), 1);
		else if ((*dest)[i] > INT_MAX)
			return (printf("Overflow, int_max 2147483647\n"), 1);
		i++;
	}
	return (0);
}
