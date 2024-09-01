/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:05:07 by zayaz             #+#    #+#             */
/*   Updated: 2024/08/30 17:02:07 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void include_input(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_zatoi(argv[2]);
	philo->time_to_eat = ft_zatoi(argv[3]);
	philo->time_to_sleep = ft_zatoi(argv[4]);
	if (argv[5])
		philo->need_eat_num = ft_zatoi(argv[5]);
	else
		philo->need_eat_num = -1;
}

void init_philo(t_philo *philo, t_program *program, pthread_mutex_t *forks,
				char **argv)
{
	int i;

	i = 0;
	while (i < ft_zatoi(argv[1]))
	{
		philo[i].id = i + 1;
		include_input(&philo[i], argv);
		philo[i].eaten_count = 0;
		philo[i].eating = 0;
		philo[i].start_time = time_now();
		philo[i].last_time = time_now();
		philo[i].dead_flag = 0;
		philo->dead_flag = program->dead;
		philo[i].l_fork = &forks[i];
		philo[i].eat_done = 0;
		philo[i].data = program;
		if (i == 0)
			philo[i].r_fork = &forks[philo[i].data->philo_num - 1];
		else
			philo[i].r_fork = &forks[i - 1];
		i++;
	}
}

void init_forks(pthread_mutex_t *forks, int p_count)
{
	int i;

	i = 0;
	while (i < p_count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void init_program(t_program *program, t_philo *philo, char **argv)
{
	program->philo = philo;
	program->dead = 0;
	program->philo_num = ft_zatoi(argv[1]);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->eat_lock, NULL);
	pthread_mutex_init(&program->check_lock, NULL);
	pthread_mutex_init(&program->need_lock, NULL);
}
