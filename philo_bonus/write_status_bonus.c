/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:19:50 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/04/30 19:07:02 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_strlen(char *phl)
{
	int	len;

	len = 0;
	while (phl[len])
		len++;
	return (len);
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_putstr(char *phl)
{
	write(1, phl, ft_strlen(phl));
}

static void	ft_putnbr(int n)
{
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putchar((n % 10) + 48);
	}
	else
		ft_putchar(n + 48);
}

void	write_status(t_philo *philo, char *p_str)
{
	t_long	time;

	sem_wait(philo->info->sem_write);
	time = get_time() - philo->t0;
	ft_putnbr((int)time);
	ft_putchar(' ');
	ft_putnbr(philo->pos);
	ft_putstr(p_str);
	sem_post(philo->info->sem_write);
}
