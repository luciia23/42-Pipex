/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:45:54 by lcollado          #+#    #+#             */
/*   Updated: 2024/02/10 12:33:22 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	**arr_mem(char const *s, char c)
{
	char	**str;
	int		num_words;

	if (s == NULL)
		return (NULL);
	num_words = count_words(s, c);
	str = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	str[num_words] = NULL;
	return (str);
}

char	**make_split(char	**str, int num, char const *s, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		str[j++] = ft_substr(s, start, i - start);
		while (s[i] && s[i] == c)
			i++;
		if (j == num)
			break ;
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		num;

	if (s == NULL)
		return (NULL);
	num = count_words(s, c);
	str = arr_mem(s, c);
	if (!str)
		return (NULL);
	if (num == 0)
	{
		str[0] = NULL;
		return (str);
	}
	str = make_split(str, num, s, c);
	if (!str)
		return (NULL);
	return (str);
}
