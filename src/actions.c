/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:02:52 by sal-zuba          #+#    #+#             */
/*   Updated: 2023/12/22 16:46:29 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print(char *str, t_philo *philo)
{
	int	var;

	pthread_mutex_lock(philo->t);
	var = *philo->dead;
	pthread_mutex_unlock(philo->t);
	if (!var)
	{
		pthread_mutex_lock(philo->print);
		printf("%li %d %s\n", get_init_time() - philo->start, philo->id, str);
		pthread_mutex_unlock(philo->print);
	}
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print("has taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	print("has taken a fork", philo);
	pthread_mutex_lock(&philo->makla);
	philo->eating = 1;
	philo->ate++;
	pthread_mutex_unlock(&philo->makla);
	print("is eating", philo);
	smart_sleep(philo->time_to_eat);
	pthread_mutex_lock(&philo->tmp);
	philo->last_meal = get_init_time();
	philo->ttd = philo->last_meal + philo->time_to_die - philo->time_to_eat;
	pthread_mutex_unlock(&philo->tmp);
	pthread_mutex_lock(&philo->makla);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->makla);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	print("is sleeping", philo);
	return (0);
}

void	*routine(void *p)
{
	t_philo	*philo;
	int		f;

	philo = (t_philo *)p;
	if (philo->id % 2)
		usleep(1100);
	while (1)
	{
		pthread_mutex_lock(philo->t);
		f = *philo->dead;
		pthread_mutex_unlock(philo->t);
		if (f)
			break ;
		eat(philo);
		pthread_mutex_lock(&philo->makla);
		f = (philo->ate == philo->number_of_meals);
		pthread_mutex_unlock(&philo->makla);
		if (f)
			break ;
		smart_sleep(philo->time_to_sleep);
		print("is thinking", philo);
	}
	return (NULL);
}
