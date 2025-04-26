/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:05:40 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/04/26 13:02:40 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	slumber(t_philo *philo)
{
	log_action(philo, "is sleeping");
	ft_usleep(philo->info->tt_sleep);
}

void	think(t_philo *philo)
{
	log_action(philo, "is thinking");
}

void	eat(t_philo *philo)
{
	sem_wait(philo->info->forks);
	log_action(philo, "has taken a fork");
	if (philo->info->nb_philo == 1)
	{
		sem_post(philo->info->forks);
		ft_usleep(philo->info->tt_die);
		return ;
	}
	sem_wait(philo->info->forks);
	log_action(philo, "has taken a fork");
	log_action(philo, "is eating");
	ft_usleep(philo->info->tt_eat);
	sem_wait(philo->info->sem_eat);
	philo->t1 = get_time();
	philo->e_counter++;
	sem_post(philo->info->sem_eat);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}
