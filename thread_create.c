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

static void	zzz_sleeping(t_philo *philo)
{
	print_message(philo, philo->id, "is sleeping");
	z_sleep(philo, philo->time_to_sleep);
	return ;
}

static void	thinking(t_philo *philo)
{
	print_message(philo, philo->id, "is thinking");
	return ;
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, philo->id, "has taken a fork");
	philo->eating = 1;
	print_message(philo, philo->id, "is eating");
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_time = time_now();
	philo->eaten_count++;
	pthread_mutex_unlock(&philo->eat_lock);
	z_sleep(philo, philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo[0].philo_num == 1)
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

int	thread_create(t_philo *philo)
{
	int			i;
	pthread_t	zthread;

	i = 0;
	if (pthread_create(&zthread, NULL, &check_thread, philo) != 0)
		return (-1);
	while (i < philo[0].philo_num)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return (-1);
		i++;
	}
	i = 0;
	if (pthread_join(zthread, NULL) != 0)
		return (-1);
	while (i < philo[0].philo_num)
	{
		if (pthread_detach(philo[i].thread) != 0)
			return (-1);
	}
	return (1);
}
