/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:12:31 by zayaz             #+#    #+#             */
/*   Updated: 2024/08/30 17:08:45 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *s)
{
	return (printf("Error: %s\n", s));
}

int	ft_zatoi(char *s)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + s[i] - '0';
		i++;
	}
	return (result);
}

void	z_sleep(t_philo *philo, size_t time)
{
	size_t	start_time;

	start_time = time_now();
	(void)*philo;
	while (time_now() - start_time < time)
	{
		if (!dieorlife(philo))
			return ;
		usleep(500);
	}
}

size_t	time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_error("gettime");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_message(t_philo *philo, int id, char *state)
{
	size_t		time;
	static int	i = 0;

	pthread_mutex_lock(&philo->data->need_lock);
	if (philo->data->philo[0].eat_done == 1)
	{
		pthread_mutex_unlock(&philo->data->need_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->need_lock);
	pthread_mutex_lock(&philo->data->write_lock);
	time = (time_now() - philo->start_time);
	if (dieorlife(philo))
	{
		printf("%zu %d %s\n", time, id, state);
		pthread_mutex_unlock(&philo->data->write_lock);
		return ;
	}
	else if (!i)
	{
		printf("%zu %d %s\n", time, id, state);
		i = 1;
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}
