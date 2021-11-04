/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:08:51 by cmariot           #+#    #+#             */
/*   Updated: 2021/11/04 15:51:53 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	atou_errors(int ref, t_rules *rules)
{
	if (ref == 1)
		printf("Error : philo only supports unsigned int arguments.\n");
	else if (ref == 2)
		printf("Error : an argument is too big\n");
	free(rules);
	exit(EXIT_FAILURE);
}

unsigned int	ft_atou(char *str, t_rules *rules)
{
	unsigned int	number;
	int				number_len;
	int				i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			atou_errors(1, rules);
	number = 0;
	number_len = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			number = (number * 10) + (str[i++] - '0');
			number_len++;
		}
		else
			atou_errors(1, rules);
	}
	if (number_len > 10)
		atou_errors(2, rules);
	return (number);
}

void	init_philo(t_rules *rules)
{
	int	i;

	rules->philo = malloc(sizeof(t_philo) * rules->number_of_philosophers);
	if (!rules->philo)
	{
		printf("Error, during the malloc of rules->philo\n");
		free(rules);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < rules->number_of_philosophers)
	{
		rules->philo[i].id = i + 1;
		rules->philo[i].number_of_philosophers = rules->number_of_philosophers;
		rules->philo[i].number_of_forks = rules->number_of_forks;
		rules->philo[i].time_to_die = rules->time_to_die;
		rules->philo[i].time_to_eat = rules->time_to_eat;
		rules->philo[i].time_to_sleep = rules->time_to_sleep;
		rules->philo[i].min_number_of_eat = rules->min_number_of_eat;
		i++;
	}
}

void	init_rules(t_rules *rules, char **argv, int argc)
{
	rules->number_of_philosophers = ft_atou(argv[1], rules);
	rules->number_of_forks = rules->number_of_philosophers;
	rules->time_to_die = ft_atou(argv[2], rules);
	rules->time_to_eat = ft_atou(argv[3], rules);
	rules->time_to_sleep = ft_atou(argv[4], rules);
	if (argc == 6)
		rules->min_number_of_eat = ft_atou(argv[5], rules);
	else
		rules->min_number_of_eat = 0;
	if (rules->number_of_philosophers < 1)
	{
		printf("Error, not enought philosophers\n");
		free(rules);
		exit(EXIT_FAILURE);
	}
	init_philo(rules);
}
