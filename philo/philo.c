/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:35 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/04/26 09:53:29 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	l(void)
{
	system("leaks -q philo");
}

int	main(int ac, char **av)
{
	t_info	info;

	atexit(l);
	if (!philo_parsing(ac - 1, av, &info))
		return (1);
	if (!global_init(&info))
		return (1);
	if (!philo_start_dining(&info))
		return (1);
	ready_to_finish(&info);
	return (0);
}
