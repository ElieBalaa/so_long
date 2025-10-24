/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eal-bala <eal-bala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:48:38 by eal-bala          #+#    #+#             */
/*   Updated: 2025/05/21 18:51:46 by eal-bala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	is_operator(char c)
{
	return (c == '-' || c == '+');
}

int	ft_atoi(const char *str)
{
	int	result;
	int	minus;
	int	i;

	result = 0;
	minus = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (is_operator(str[i]))
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * minus);
}
