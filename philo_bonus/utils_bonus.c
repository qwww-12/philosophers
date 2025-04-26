/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:37:12 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/04/26 14:53:19 by mbarhoun         ###   ########.fr       */
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

void	log_action(t_philo *philo, char *msg)
{
	t_long	time;

	sem_wait(philo->info->sem_write);
	time = get_time() - philo->t0;
	printf("%lld %d %s\n", time, philo->pos, msg);
	sem_post(philo->info->sem_write);
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
		usleep(100);
	}
}

void	destroy_sem(t_info *info)
{
	sem_close(info->forks);
	sem_close(info->sem_eat);
	sem_close(info->sem_write);
	sem_close(info->sem_death);
	sem_unlink("/sem_forks");
	sem_unlink("/sem_eat");
	sem_unlink("/sem_write");
	sem_unlink("/sem_death");
}

void	ready_to_finish(t_info *info)
{
	destroy_sem(info);
	free(info->philo);
	free(info->pids);
}
