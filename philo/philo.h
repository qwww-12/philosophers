/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:31 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/05/04 17:13:25 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>

# define ERR_MAX "You Have Exceeded the limit of philosophers\n"
# define ERR_ARG "Number of the arg is not Correct\n"
# define ERR_NBR "Number is not Correct\n"
# define ERR_MEM "Allocation Faield\n"
# define ERR_PTH "Probleme Creating Thread\n"
# define ERR_MTX "Mutex Problem\n"
# define ERR_DST "Probleme Destroying The Mutex\n"
# define ERR_TIM "Clock Probleme\n"
# define ERR_WTH "Threading Probleme\n"

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;
typedef long long		t_long;

/*~~~~~~~~~~~~~~~~~~~~~~~ parsing.c ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int		philo_parsing(int narg, char **args, t_info *info);
/*~~~~~~~~~~~~~~~~~~~~~~~ leaks.c ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void	fint_db(int ***leaks);
void	destroy_mutex(pthread_mutex_t *mtx, int max);
void	unlock_mutex(t_info *info);
/*~~~~~~~~~~~~~~~~~~~~~~~ init.c ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int		global_init(t_info *info);
/*~~~~~~~~~~~~~~~~~~~~ strat_feats.c ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int		philo_start_dining(t_info *info);
int		valid_action(t_philo *philo, bool condition);
/*~~~~~~~~~~~~~~~~~~~~~~~ utils.c ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
t_long	get_time(void);
int		crash(char *msg, t_info *info);
void	log_action(t_philo *philo, char *msg);
void	ft_usleep(t_long time, t_info *info);
void	ready_to_finish(t_info *info);
/*~~~~~~~~~~~~~~~~~~~~~~~ watcher.c ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void	*reaper_eye(void *arg);
/*~~~~~~~~~~~~~~~~~~~~~~~ action.c ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void	slumber(t_philo *philo);
void	think(t_philo *philo);
int		eat(t_philo *philo);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct s_info
{
	int				nb_philo;
	int				n_meals;
	bool			death_flag;
	t_long			tt_eat;
	t_long			tt_die;
	t_long			tt_sleep;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_eat;
	pthread_mutex_t	lock_death;
	pthread_mutex_t	lock_write;
	pthread_t		reaper_eye;
	t_philo			*philo;
}	t_info;

typedef struct s_philo
{
	int			pos;
	int			fork[2];
	int			e_counter;
	t_long		t0;
	t_long		t1;
	t_info		*info;
	pthread_t	thread;
}	t_philo;

#endif
