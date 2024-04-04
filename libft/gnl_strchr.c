/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_strchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:36:42 by lcollado          #+#    #+#             */
/*   Updated: 2024/02/10 12:37:11 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strchr(const char *s, int c)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	while (i < len && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return (&((char *)s)[i]);
	if (c == 0)
		return ((char *)s);
	return (NULL);
}
