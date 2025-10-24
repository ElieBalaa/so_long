/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eal-bala <eal-bala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:50:15 by eal-bala          #+#    #+#             */
/*   Updated: 2025/05/20 17:28:00 by eal-bala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*last_occurrence;

	last_occurrence = NULL;
	c = (unsigned char)c;
	len = 0;
	while (s[len])
	{
		if (s[len] == c)
			last_occurrence = (char *)&s[len];
		len++;
	}
	if (c == '\0')
		return ((char *)&s[len]);
	return (last_occurrence);
}
