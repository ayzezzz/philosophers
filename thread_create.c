/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:23:47 by zayaz             #+#    #+#             */
/*   Updated: 2024/08/30 17:08:32 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void zzz_sleeping(t_philo *philo)
{
	print_message(philo, philo->id, "is sleeping");
	z_sleep(philo, philo->time_to_sleep);
	return;
}

static void thinking(t_philo *philo)
{
	print_message(philo, philo->id, "is thinking");
	return;
}

static void eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, philo->id, "has taken a fork");
	philo->eating = 1;
	print_message(philo, philo->id, "is eating");
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->last_time = time_now();
	philo->eaten_count++;
	pthread_mutex_unlock(&philo->data->eat_lock);
	z_sleep(philo, philo->time_to_eat);
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->data->eat_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo[0].data->philo_num == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		print_message(philo, philo->id, "has taken a fork");
		pthread_mutex_unlock(philo->r_fork);
		philo->data->dead = 1;
		dieorlife(philo);
		return (arg);
	}
	if (philo->id % 2 == 0)
		z_sleep(philo, 1);
	while (dieorlife(philo))
	{
		eating(philo);
		zzz_sleeping(philo);
		thinking(philo);
	}
	return (arg);
}

int thread_create(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo[0].data->philo_num)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return (-1);
		i++;
	}
	check_thread(philo);
	i = 0;
	while (i < philo->data->philo_num)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (1);
}
