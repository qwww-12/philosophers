/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper_eye.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:22 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/04/26 10:18:14 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	timer_of_death(t_philo *philo)
{
	t_long		t2;
	bool		status;

	pthread_mutex_lock(&philo->info->lock_eat);
	t2 = get_time();
	status = 0;
	if (t2 - philo->t1 >= philo->info->tt_die)
		status = 1;
	pthread_mutex_unlock(&philo->info->lock_eat);
	return (status);
}

static int	observe_death(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo[0].info->nb_philo)
	{
		if (timer_of_death(&philo[i]))
		{
			log_action(&philo[i], "died");
			pthread_mutex_lock(&philo->info->lock_death);
			philo->info->death_flag = 1;
			pthread_mutex_unlock(&philo->info->lock_death);
			return (1);
		}
	}
	return (0);
}

static int	check_e_counter(t_philo *philo)
{
	int	full;
	int	i;

	full = 0;
	i = 0;
	if (philo->info->n_meals == -1)
		return (0);
	while (i < philo[0].info->nb_philo)
	{
		pthread_mutex_lock(&philo->info->lock_eat);
		if (philo[i].e_counter >= philo[0].info->n_meals)
			full++;
		pthread_mutex_unlock(&philo[0].info->lock_eat);
		i++;
	}
	if (full == philo[0].info->nb_philo)
	{
		pthread_mutex_lock(&philo->info->lock_death);
		philo->info->death_flag = 1;
		pthread_mutex_unlock(&philo->info->lock_death);
		return (1);
	}
	return (0);
}

void	*reaper_eye(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	while (1)
		if (observe_death(info->philo) == 1 
			|| check_e_counter(info->philo) == 1)
			break ;
	return (arg);
}
