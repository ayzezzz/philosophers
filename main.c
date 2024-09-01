/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:19:38 by zayaz             #+#    #+#             */
/*   Updated: 2024/08/30 17:17:12 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_program *program;
	pthread_mutex_t forks[PHILO_MAX];
	t_philo philo[PHILO_MAX];

	if (!(argc == 5 || argc == 6))
		return (ft_error("Unvalid argc"));
	if (!check_argv(argv))
		return (ft_error("Unvalid arg"));
	program = malloc(sizeof(t_program));
	init_program(program, philo, argv);
	init_forks(forks, ft_zatoi(argv[1]));
	program->philo = malloc(sizeof(t_philo) * (ft_zatoi(argv[1])));
	init_philo(program->philo, program, forks, argv);
	thread_create(program->philo);
	destroy_program(program, program->philo, forks);
	return (0);
}

// void __attribute__((constructor))a()
// {
// 	system("leaks philo");
// }