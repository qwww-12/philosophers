/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:05:40 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/05/04 18:22:47 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	slumber(t_philo *philo)
{
	write_status(philo, " is sleeping\n");
	ft_usleep(philo->info->tt_sleep);
}

void	think(t_philo *philo)
{
	write_status(philo, " is thinking\n");
}

void	eat(t_philo *philo)
{
	sem_wait(philo->info->forks);
	write_status(philo, " has taken a fork\n");
	if (philo->info->nb_philo == 1)
	{
		sem_post(philo->info->forks);
		ft_usleep(philo->info->tt_die);
		return ;
	}
	sem_wait(philo->info->forks);
	write_status(philo, " has taken a fork\n");
	write_status(philo, " is eating\n");
	sem_wait(philo->info->sem_eat);
	philo->t1 = get_time();
	sem_post(philo->info->sem_eat);
	ft_usleep(philo->info->tt_eat);
	philo->e_counter++;
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}
