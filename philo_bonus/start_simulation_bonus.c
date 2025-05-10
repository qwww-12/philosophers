/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:53:00 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/05/04 18:26:23 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	wait_philos(t_info *info)
{
	t_wait	wait1;

	wait1.done = 0;
	wait1.status = 0;
	while (1)
	{
		wait1.pid = waitpid(-1, &wait1.status, 0);
		if (WIFEXITED(wait1.status))
		{
			wait1.code = WEXITSTATUS(wait1.status);
			if (wait1.code == 1)
			{
				delete_process(info, wait1.pid);
				return ;
			}
			else if (wait1.code == 42)
			{
				wait1.done++;
				if (wait1.done == info->nb_philo)
					return ;
			}
		}
	}
}

static void	actions(t_philo *philo)
{
	if (philo->pos % 2 == 0)
		ft_usleep(philo->info->tt_eat / 2);
	while (1)
	{
		think(philo);
		eat(philo);
		slumber(philo);
		usleep(500);
	}
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

void	start_simulation(t_info *info)
{
	int	i;

	i = -1;
	set_time(info);
	while (++i < info->nb_philo)
	{
		info->pids[i] = fork();
		if (info->pids[i] == 0)
		{
			pthread_create(&info->philo[i].observe, NULL, \
			reaper_eye, &info->philo[i]);
			pthread_detach(info->philo[i].observe);
			actions(&info->philo[i]);
			exit(2);
		}
		else if (info->pids[i] == -1)
		{
			printf(ERR_FRK);
			exit(1);
		}
	}
	wait_philos(info);
}
