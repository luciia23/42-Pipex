/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:22:10 by lcollado          #+#    #+#             */
/*   Updated: 2022/12/01 09:13:45 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*s;
	size_t	dstlen;
	size_t	srclen;
	size_t	i;
	size_t	j;

	if (dstsize == 0)
		return (ft_strlen((char *)src));
	s = (char *)src;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen((char *)src);
	i = 0;
	j = dstlen;
	if (dstlen >= dstsize)
		return (srclen + dstsize);
	while (s[i] != 0 && i < dstsize - dstlen - 1)
	{
		dst[j] = s[i];
		j++;
		i++;
	}
	dst[j] = 0;
	return (srclen + dstlen);
}
