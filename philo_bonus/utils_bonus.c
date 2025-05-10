/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:37:12 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/05/04 18:22:12 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf(ERR_TIM), 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(t_long time)
{
	t_long	t0;
	t_long	t1;

	t0 = get_time();
	while (1)
	{
		t1 = get_time();
		if (t1 - t0 >= time)
			return ;
		usleep(500);
	}
}

void	ready_to_finish(t_info *info)
{
	sem_close(info->forks);
	sem_close(info->sem_eat);
	sem_close(info->sem_write);
	sem_close(info->sem_death);
	free(info->philo);
	free(info->pids);
}

void	semaphore_post(t_info *info)
{
	sem_post(info->sem_death);
	sem_post(info->sem_write);
	sem_post(info->sem_eat);
}

void	delete_process(t_info *info, pid_t pid)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
		if (info->pids[i] != pid && info->pids[i] > 0)
			kill(info->pids[i], SIGKILL);
}
