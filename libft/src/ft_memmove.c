/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eal-bala <eal-bala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:49:24 by eal-bala          #+#    #+#             */
/*   Updated: 2025/05/20 16:16:47 by eal-bala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	*ft_forward_copy(unsigned char *d, unsigned char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

static void	*ft_backward_copy(unsigned char *d, unsigned char *s, size_t n)
{
	size_t	i;

	i = n;
	while (i > 0)
	{
		i--;
		d[i] = s[i];
	}
	return (d);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (NULL);
	if (n == 0)
		return (dest);
	if ((unsigned char *)dest < (unsigned char *)src)
		ft_forward_copy((unsigned char *)dest, (unsigned char *)src, n);
	else
		ft_backward_copy((unsigned char *)dest, (unsigned char *)src, n);
	return (dest);
}
