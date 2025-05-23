/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 08:29:37 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/05/04 18:22:28 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>

# define ERR_ARG "Number of the arg is not Correct\n"
# define ERR_NBR "Number is not Correct\n"
# define ERR_MEM "Allocation Faield\n"
# define ERR_PTH "Probleme Creating Thread\n"
# define ERR_TIM "Clock Probleme\n"
# define ERR_SEM "Probleme Creating Semaphore\n"
# define ERR_FRK "Probleme Craeting Child Process\n"

typedef long long		t_long;
typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

/*~~~~~~~~~~~~~~~~~~~~~~~ parsing_bonus.c ~~~~~~~~~~~~~~~~~~*/
int		parsing(t_info *info, int ac, char **av);
/*~~~~~~~~~~~~~~~~~~~~~~~ init_bonus.c ~~~~~~~~~~~~~~~~~~~~~*/
int		global_init(t_info *info);
/*~~~~~~~~~~~~~~~~~~~~~~~ utils_bonus.c ~~~~~~~~~~~~~~~~~~~~*/
t_long	get_time(void);
void	ft_usleep(t_long time);
void	ready_to_finish(t_info *info);
void	semaphore_post(t_info *info);
void	delete_process(t_info *info, pid_t pid);
/*~~~~~~~~~~~~~~~~~ start_simulation_bonus.c ~~~~~~~~~~~~~~~*/
void	start_simulation(t_info *info);
/*~~~~~~~~~~~~~~~~~~~~ reaper_eye_bonus.c ~~~~~~~~~~~~~~~~~~*/
void	*reaper_eye(void *arg);
/*~~~~~~~~~~~~~~~~~~~~~~ actions_bonus.c ~~~~~~~~~~~~~~~~~~~*/
void	eat(t_philo *philo);
void	think(t_philo *philo);
void	slumber(t_philo *philo);
/*~~~~~~~~~~~~~~~~~~~ write_status_bonus.c ~~~~~~~~~~~~~~~~~*/
void	write_status(t_philo *philo, char *p_str);

typedef struct s_info
{
	int			nb_philo;
	int			n_meals;
	bool		death_flag;
	t_long		tt_die;
	t_long		tt_eat;
	t_long		tt_sleep;
	pid_t		*pids;
	sem_t		*forks;
	sem_t		*sem_death;
	sem_t		*sem_eat;
	sem_t		*sem_write;
	t_philo		*philo;
}	t_info;

typedef struct s_philo
{
	int			pos;
	int			e_counter;
	useconds_t	rsleep;
	t_long		t0;
	t_long		t1;
	t_info		*info;
	pthread_t	observe;
}	t_philo;

typedef struct s_wait
{
	int	status;
	int	pid;
	int	done;
	int	code;
}	t_wait;

#endif