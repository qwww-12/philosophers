/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:25 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/04/27 14:01:42 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf(ERR_TIM), 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ready_to_finish(t_info *info)
{
	int	i;

	i = 0;
	unlock_mutex(info);
	while (i < info->nb_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->lock_eat);
	pthread_mutex_destroy(&info->lock_death);
	pthread_mutex_destroy(&info->lock_write);
	free(info->forks);
	free(info->philo);
}

void	log_action(t_philo *philo, char *msg)
{
	t_long	time;

	pthread_mutex_lock(&philo->info->lock_write);
	time = get_time() - philo->t0;
	if (!philo->info->death_flag)
		printf("%lld %d %s\n", time, philo->pos, msg);
	pthread_mutex_unlock(&philo->info->lock_write);
}

void	ft_usleep(t_long time, t_info *info)
{
	t_long	t0;
	t_long	t1;

	t0 = get_time();
	while (info->death_flag == 0)
	{
		t1 = get_time();
		if (t1 - t0 >= time)
			return ;
		usleep(100);
	}
}

int	crash(char *msg, t_info *info)
{
	if (msg)
		printf("%s\n", msg);
	if (info)
		destroy_mutex(info->forks, info->nb_philo);
	return (0);
}
