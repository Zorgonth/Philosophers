/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:57:04 by sal-zuba          #+#    #+#             */
/*   Updated: 2023/12/22 16:53:32 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

struct	s_general;
struct	s_philo;

typedef struct s_philo
{
	int					ate;
	int					eating;
	int					id;
	int					*dead;
	int					number_of_meals;
	long				time_to_eat;
	long				time_to_sleep;
	long				last_meal;
	long				start;
	long				ttd;
	long				time_to_die;
	pthread_mutex_t		tmp;
	pthread_mutex_t		*t;
	pthread_mutex_t		*print;
	pthread_mutex_t		makla;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
}				t_philo;

typedef struct s_general
{
	int				number_of_meals;
	int				number_of_p;
	int				n_forks;
	int				died;
	int				all_ate;
	long			time_to_sleep;
	long			time_to_eat;
	long			time_to_die;
	long			start_time;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	print;
	pthread_mutex_t	t;
	t_philo			philo[200];
	pthread_t		tmp[200];
}				t_general;

int		init(t_general *g, char **argv);
int		check_args(int argc, char **argv);
int		ft_atoi(const char *str);
int		set_rules(t_general *g, char **argv);
int		init_philos(t_general *g);
int		init_threads(t_general *g);
int		eat(t_philo *philo);
int		death(t_general *g);
long	get_init_time(void);
long	get_actual_time(long start);
void	destory(t_general *g);
void	*routine(void *p);
void	print(char *str, t_philo *philo);
void	smart_sleep(long time);
void	*monitor(void *p);
void	check(t_general *g);
void	death_print(t_philo philo);
void	check_death(t_general *g);

#endif