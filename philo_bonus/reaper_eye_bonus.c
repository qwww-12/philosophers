/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper_eye_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 08:14:14 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/04/26 15:22:17 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_e_counter(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->info->n_meals == -1)
		return (1);
	sem_wait(philo->info->sem_eat);
	if (philo->e_counter >= philo->info->n_meals)
	{
		sem_post(philo->info->sem_eat);
		sem_wait(philo->info->sem_write);
		sem_post(philo->info->sem_write);
		exit(42);
	}
	sem_post(philo->info->sem_eat);
	return (1);
}

static int	timer_of_death(t_philo *philo)
{
	t_long	time;

	sem_wait(philo->info->sem_eat);
	time = get_time();
	if (time - philo->t1 >= philo->info->tt_die)
	{
		sem_wait(philo->info->sem_death);
		log_action(philo, "died");
		sem_post(philo->info->sem_eat);
		exit (1);
	}
	sem_post(philo->info->sem_eat);
	return (1);
}

void	*reaper_eye(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
		if (!timer_of_death(philo) || !check_e_counter(philo))
			break ;
	return (arg);
}
