/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_feast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:28 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/04/27 14:56:03 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_action(t_philo *philo, bool condition)
{
	int	status;

	status = 0;
	if (condition == 0)
	{
		pthread_mutex_lock(&philo->info->lock_death);
		if (philo->info->death_flag == 1)
			status = 1;
		pthread_mutex_unlock(&philo->info->lock_death);
		return (status);
	}
	else
	{
		if (philo->info->n_meals < 0)
			return (0);
		if (philo->e_counter < philo->info->n_meals)
			return (0);
	}
	return (1);
}

void	*philosophers(void *arg)
{
	t_philo	*philo;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	if (philo->pos % 2 == 0)
		ft_usleep(1, philo->info);
	while (!valid_action(philo, 0) && !valid_action(philo, 1))
	{
		think(philo);
		if (!eat(philo))
			return (NULL);
		slumber(philo);
	}
	return (NULL);
}

static void	set_time(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		info->philo[i].t0 = get_time();
		info->philo[i].t1 = get_time();
	}
}

static int	philo_create(t_info *info)
{
	int	i;

	i = -1;
	set_time(info);
	if (pthread_create(&info->reaper_eye, NULL, reaper_eye, info))
		return (crash(ERR_PTH, info));
	while (++i < info->nb_philo)
		if (pthread_create(&info->philo[i].thread, NULL, 
				&philosophers, &info->philo[i]))
			return (crash(ERR_PTH, info));
	i = -1;
	if (pthread_join(info->reaper_eye, NULL))
		return (crash(ERR_WTH, info));
	while (++i < info->nb_philo)
		if (pthread_join(info->philo[i].thread, NULL))
			return (crash(ERR_WTH, info));
	return (1);
}

int	philo_start_dining(t_info *info)
{
	if (!info->n_meals)
		return (1);
	if (!philo_create(info))
		return (0);
	return (1);
}
