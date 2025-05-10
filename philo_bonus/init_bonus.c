/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:27:23 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/05/04 17:18:12 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	create_semaphore(t_info *info)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_death");
	sem_unlink("/sem_eat");
	sem_unlink("/sem_write");
	info->forks = sem_open("/sem_forks", O_CREAT, 0644, info->nb_philo);
	info->sem_eat = sem_open("/sem_eat", O_CREAT, 0644, 1);
	info->sem_write = sem_open("/sem_write", O_CREAT, 0644, 1);
	info->sem_death = sem_open("/sem_death", O_CREAT, 0644, 1);
	if (info->forks == SEM_FAILED || info->sem_eat == SEM_FAILED 
		|| info->sem_write == SEM_FAILED || info->sem_death == SEM_FAILED)
		return (printf(ERR_SEM), 0);
	return (1);
}

static void	philo_init(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		info->philo[i].rsleep = 500;
		if (info->nb_philo == 1)
			info->philo[i].rsleep = 0;
		info->philo[i].pos = i + 1;
		info->philo[i].e_counter = 0;
		info->philo[i].info = info;
	}
}

int	global_init(t_info *info)
{
	info->philo = malloc(sizeof(t_philo) * info->nb_philo);
	if (!info->philo)
		return (printf(ERR_MEM), 0);
	info->pids = malloc(sizeof(pid_t) * info->nb_philo);
	if (!info->pids)
	{
		free(info->philo);
		return (printf(ERR_MEM), 0);
	}
	info->death_flag = 0;
	philo_init(info);
	if (!create_semaphore(info))
	{
		free(info->philo);
		free(info->pids);
		return (0);
	}
	return (1);
}
