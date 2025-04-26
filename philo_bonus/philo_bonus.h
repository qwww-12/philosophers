/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 08:29:37 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/04/26 13:00:05 by mbarhoun         ###   ########.fr       */
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

# define ERR_MAX "You Have Exceeded the limit of philosophers\n"
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
void	log_action(t_philo *philo, char *msg);
void	destroy_sem(t_info *info);
void	ready_to_finish(t_info *info);
/*~~~~~~~~~~~~~~~~~ start_simulation_bonus.c ~~~~~~~~~~~~~~~*/
void	start_simulation(t_info *info);
/*~~~~~~~~~~~~~~~~~~~~ reaper_eye_bonus.c ~~~~~~~~~~~~~~~~~~*/
void	*reaper_eye(void *arg);
/*~~~~~~~~~~~~~~~~~~~~~~ actions_bonus.c ~~~~~~~~~~~~~~~~~~~*/
void	eat(t_philo *philo);
void	think(t_philo *philo);
void	slumber(t_philo *philo);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct s_info
{
	int			nb_philo;
	int			n_meals;
	int			process_counter;
	bool		death_flag;
	t_long		tt_die;
	t_long		tt_eat;
	t_long		tt_sleep;
	pid_t		main_pid;
	pid_t		*pids;
	sem_t		*forks;
	sem_t		*sem_death;
	sem_t		*sem_eat;
	sem_t		*sem_write;
	t_philo		*philo;
}	t_info;

typedef struct s_philo
{
	int		e_counter;
	int		pos;
	bool	not_write;
	bool	death_flag;
	t_long	t0;
	t_long	t1;
	t_info	*info;
}	t_philo;

typedef struct s_wait
{
	int	status;
	int	pid;
	int	done;
	int	code;
}	t_wait;

#endif