/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eal-bala <eal-bala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:48:50 by eal-bala          #+#    #+#             */
/*   Updated: 2025/05/20 21:04:17 by eal-bala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	bytes;
	void	*pointer;

	bytes = count * size;
	if (size != 0 && ((bytes / size) != count))
		return (NULL);
	pointer = malloc(bytes);
	if (!pointer)
		return (NULL);
	ft_bzero(pointer, bytes);
	return (pointer);
}
