/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:14 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/05/04 16:57:52 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	slumber(t_philo *philo)
{
	log_action(philo, "is sleeping");
	ft_usleep(philo->info->tt_sleep, philo->info);
}

void	think(t_philo *philo)
{
	log_action(philo, "is thinking");
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->fork[1]]);
	log_action(philo, "has taken a fork");
	if (philo->info->nb_philo == 1)
	{
		pthread_mutex_unlock(&philo->info->forks[0]);
		ft_usleep(philo->info->tt_die, philo->info);
		return (0);
	}
	pthread_mutex_lock(&philo->info->forks[philo->fork[0]]);
	log_action(philo, "has taken a fork");
	log_action(philo, "is eating");
	pthread_mutex_lock(&philo->info->lock_eat);
	philo->t1 = get_time();
	philo->e_counter++;
	pthread_mutex_unlock(&philo->info->lock_eat);
	ft_usleep(philo->info->tt_eat, philo->info);
	pthread_mutex_unlock(&philo->info->forks[philo->fork[0]]);
	pthread_mutex_unlock(&philo->info->forks[philo->fork[1]]);
	return (1);
}
