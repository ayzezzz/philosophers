/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:12:40 by zayaz             #+#    #+#             */
/*   Updated: 2024/08/30 16:55:02 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	numeric_check(char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= 48 && argv[i][j] <= 57) && argv[i][j] != 43)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_argv(char **argv)
{
	if (ft_zatoi(argv[1]) > 200)
		return (0);
	if (numeric_check(argv))
		return (1);
	return (0);
}
