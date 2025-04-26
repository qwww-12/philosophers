/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 09:43:08 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/04/22 10:23:40 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	set_philo_arguments(t_info *info, int *ent_arg, int ac)
{
	info->tt_die = (t_long)ent_arg[1];
	info->tt_eat = (t_long)ent_arg[2];
	info->tt_sleep = (t_long)ent_arg[3];
	info->nb_philo = ent_arg[0];
	info->n_meals = -1;
	if (ac == 5)
		info->n_meals = ent_arg[4];
	free(ent_arg);
	return (1);
}

static int	find_zero(int *ent_arg, int ac)
{
	int		i;
	bool	flag;

	i = -1;
	flag = 0;
	if (ac == 5)
		flag = 1;
	while (++i < ac - flag)
	{
		if (ent_arg[i] == 0)
		{
			free(ent_arg);
			return (printf(ERR_NBR), 0);
		}
	}
	return (1);
}

static int	philo_atoi(char *str)
{
	long long	nb;
	int			sg;

	nb = 0;
	sg = 1;
	while (*str && *str == ' ')
		str++;
	while (*str == '-' || *str == '+')
		if (*str++ == '-')
			sg = -1;
	while (*str)
	{
		if (*str < 48 || *str > 57)
			return (-1);
		nb = (nb * 10) + (*str++ - 48);
	}
	nb *= sg;
	if (nb > 2147483647 || nb < -2147483648)
		return (-1);
	return ((int)nb);
}

static int	philo_arguments(t_info *info, int ac, char **av)
{
	int	*ent_arg;
	int	i;

	i = -1;
	ent_arg = malloc(sizeof(int) * ac);
	if (!ent_arg)
		return (printf(ERR_MEM), 0);
	while (++i < ac)
	{
		ent_arg[i] = philo_atoi(av[i + 1]);
		if (ent_arg[i] < 0)
		{
			free(ent_arg);
			return (printf(ERR_NBR), 0);
		}
	}
	if (ent_arg[0] > 200)
		return (printf(ERR_MAX), free(ent_arg), 0);
	if (!find_zero(ent_arg, ac))
		return (0);
	return (set_philo_arguments(info, ent_arg, ac));
}

int	parsing(t_info *info, int ac, char **av)
{
	if (ac != 4 && ac != 5)
		return (printf(ERR_ARG), 0);
	return (philo_arguments(info, ac, av));
}
