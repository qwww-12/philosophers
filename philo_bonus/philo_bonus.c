/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 09:39:37 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/04/26 14:51:36 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_info	info;

	if (!parsing(&info, ac - 1, av))
		return (1);
	if (!global_init(&info))
		return (1);
	if (info.n_meals == 0)
	{
		ready_to_finish(&info);
		return (0);
	}
	start_simulation(&info);
	ready_to_finish(&info);
	return (0);
}
