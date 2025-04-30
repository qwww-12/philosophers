/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:49 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/04/30 18:57:13 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*init_fork(t_info *info)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = malloc(sizeof(pthread_mutex_t) * info->nb_philo);
	if (!fork)
		return (printf(ERR_MEM), NULL);
	i = -1;
	while (++i < info->nb_philo)
	{
		if (pthread_mutex_init(&fork[i], NULL))
			return (printf(ERR_MTX), destroy_mutex(fork, i), NULL);
	}
	return (fork);
}

static int	set_struct_philo(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		info->philo[i].pos = i + 1;
		info->philo[i].e_counter = 0;
		info->philo[i].info = info;
		info->philo[i].fork[0] = i;
		info->philo[i].fork[1] = i - 1;
		if (i == 0)
			info->philo[i].fork[1] = info->nb_philo - 1;
	}
	return (1);
}

int	global_init(t_info *info)
{
	info->philo = malloc(sizeof(t_philo) * info->nb_philo);
	if (!info->philo)
		return (printf(ERR_MEM), 0);
	if (!set_struct_philo(info))
		return (0);
	info->forks = init_fork(info);
	info->death_flag = 0;
	if (!info->forks)
		return (0);
	if (pthread_mutex_init(&info->lock_eat, NULL))
		return (crash(ERR_MTX, info));
	if (pthread_mutex_init(&info->lock_death, NULL))
	{
		pthread_mutex_destroy(&info->lock_eat);
		return (crash(ERR_MTX, info));
	}
	if (pthread_mutex_init(&info->lock_write, NULL))
	{
		pthread_mutex_destroy(&info->lock_eat);
		pthread_mutex_destroy(&info->lock_death);
		return (crash(ERR_MTX, info));
	}
	return (1);
}
