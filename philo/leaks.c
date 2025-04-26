/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:46 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/04/26 11:14:25 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_mutex(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
		pthread_mutex_unlock(&info->forks[i]);
	pthread_mutex_unlock(&info->lock_death);
	pthread_mutex_unlock(&info->lock_eat);
	pthread_mutex_unlock(&info->lock_write);
}

void	destroy_mutex(pthread_mutex_t *mtx, int max)
{
	int	i;

	i = -1;
	while (++i < max)
	{
		if (pthread_mutex_destroy(&mtx[i]))
		{
			printf(ERR_DST);
			return ;
		}
	}
}

void	fint_db(int ***leaks)
{
	int	i;

	if (!leaks || !(*leaks))
		return ;
	i = -1;
	while ((*leaks)[++i])
		free((*leaks)[i]);
	free(*leaks);
	*leaks = NULL;
}
