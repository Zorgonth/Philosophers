/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:26:58 by sal-zuba          #+#    #+#             */
/*   Updated: 2023/12/22 15:27:38 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	check(t_general *g)
{
	int	i;
	int	number;

	number = 0;
	i = -1;
	while (++i < g->number_of_p)
	{
		pthread_mutex_lock(&g->philo[i].makla);
		if (g->philo[i].ate == g->number_of_meals)
			number++;
		pthread_mutex_unlock(&g->philo[i].makla);
	}
	if (number == g->number_of_p)
		g->all_ate = 1;
}

void	death_print(t_philo philo)
{
	pthread_mutex_lock(philo.print);
	printf("%li ", get_init_time() - philo.start);
	printf("%d ", philo.id);
	printf("%s\n", "has died");
}

void	check_death(t_general *g)
{
	int	i;

	i = -1;
	while (++i < g->number_of_p)
	{
		pthread_mutex_lock(&g->philo[i].tmp);
		pthread_mutex_lock(&g->philo[i].makla);
		if ((!g->philo[i].eating && get_init_time() >= g->philo[i].ttd))
		{
			pthread_mutex_unlock(&g->philo[i].makla);
			pthread_mutex_unlock(&g->philo[i].tmp);
			pthread_mutex_lock(&g->t);
			g->died = 1;
			pthread_mutex_unlock(&g->t);
			death_print(g->philo[i]);
			break ;
		}
		pthread_mutex_unlock(&g->philo[i].tmp);
		pthread_mutex_unlock(&g->philo[i].makla);
	}
}

int	death(t_general *g)
{
	int	i;

	i = 0;
	usleep(g->time_to_die);
	while (1)
	{
		check(g);
		check_death(g);
		pthread_mutex_lock(&g->t);
		if (g->died)
		{
			pthread_mutex_unlock(&g->t);
			i = 1;
			break ;
		}
		pthread_mutex_unlock(&g->t);
		if (g->all_ate)
			break ;
		usleep(g->time_to_die / 2);
	}
	return (i);
}
