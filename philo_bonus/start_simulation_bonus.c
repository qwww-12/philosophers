/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:53:00 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/04/30 16:26:03 by mbarhoun         ###   ########.fr       */
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
				semaphore_post(info);
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

static int	restart_action(t_philo *philo)
{
	if (philo->info->n_meals == -1)
		return (0);
	if (philo->e_counter < philo->info->n_meals)
		return (0);
	return (1);
}

static void	actions(t_philo *philo)
{
	pthread_t	observ;

	if (pthread_create(&observ, NULL, reaper_eye, philo))
	{
		printf(ERR_PTH);
		exit(1);
	}
	pthread_detach(observ);
	if (philo->pos % 2 == 0)
		ft_usleep(1);
	while (!restart_action(philo))
	{
		think(philo);
		eat(philo);
		slumber(philo);
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
			actions(&info->philo[i]);
			exit(2);
		}
		else if (info->pids[i] == -1)
		{
			printf(ERR_FRK);
			exit(1);
		}
		usleep(100);
	}
	wait_philos(info);
}
