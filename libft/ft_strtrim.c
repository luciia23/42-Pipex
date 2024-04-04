/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:41:53 by lcollado          #+#    #+#             */
/*   Updated: 2024/02/10 12:33:53 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_start(char const *s1, char const *set)
{
	int	start;

	start = 0;
	while (s1[start])
	{
		if (ft_strchr(set, s1[start]) == NULL)
			break ;
		start++;
	}
	return (start);
}

static int	get_end(char const *s1, char const *set, int start)
{
	int	end;

	end = ft_strlen(s1);
	while (s1[end - 1] && end > start)
	{
		if (ft_strchr(set, s1[end - 1]) == NULL)
			break ;
		end--;
	}
	return (end);
}

static char	*set_mem(int start, int end)
{
	char	*str;

	str = (char *)malloc(((end - start) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strim;
	int		start;
	int		end;
	int		i;

	if ((s1 == NULL) || (set == NULL))
		return (NULL);
	start = get_start(s1, set);
	end = get_end(s1, set, start);
	strim = set_mem(start, end);
	if (strim == NULL)
		return (NULL);
	i = 0;
	while (start < end)
		strim[i++] = s1[start++];
	strim[i] = 0;
	return (strim);
}
