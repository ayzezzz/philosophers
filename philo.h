/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:42:00 by zayaz             #+#    #+#             */
/*   Updated: 2024/08/30 17:07:04 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define PHILO_MAX 200

typedef struct s_philo
{
	int id;
	int eaten_count;
	int need_eat_num;
	size_t eating;
	size_t start_time;
	size_t last_time;
	size_t time_to_eat;
	size_t time_to_die;
	size_t time_to_sleep;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	pthread_t thread;
	pthread_mutex_t eat_lock;
	pthread_mutex_t dead_lock;
	pthread_mutex_t write_lock;
	int dead_flag;
	int eat_done;
	struct s_program *data;
} t_philo;

typedef struct s_program
{
	int philo_num;
	int dead;
	t_philo *philo;
	pthread_mutex_t eat_lock;
	pthread_mutex_t dead_lock;
	pthread_mutex_t write_lock;
	pthread_mutex_t check_lock;
	pthread_mutex_t need_lock;

} t_program;

int ft_error(char *s);
int ft_zatoi(char *s);
int check_argv(char **argv);
void z_sleep(t_philo *philo, size_t time);
size_t time_now(void);
void print_message(t_philo *philo, int id, char *state);
void init_philo(t_philo *philo, t_program *program,
				pthread_mutex_t *forks, char **argv);
void init_forks(pthread_mutex_t *forks, int p_count);
void init_program(t_program *program, t_philo *philo, char **argv);
int thread_create(t_philo *philo);
void *check_thread(void *arg);
int dieorlife(t_philo *philo);
void destroy_program(t_program *program, t_philo *philo,
					 pthread_mutex_t *forks);

#endif