/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:36:21 by lcollado          #+#    #+#             */
/*   Updated: 2023/02/23 17:32:28 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmeb, size_t size)
{
	void	*s;

	if (nmeb == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	s = malloc(nmeb * size);
	if (!s)
		return (NULL);
	ft_bzero(s, nmeb * size);
	return (s);
}
