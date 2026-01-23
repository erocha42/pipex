/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:14:32 by erocha--          #+#    #+#             */
/*   Updated: 2025/10/24 11:31:13 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_sep(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	int	trim_len(char const *s1, char const *set)
{
	int	i;
	int	len;
	int	tmp;

	i = 0;
	len = 0;
	while (s1[i] && is_sep(set, s1[i]))
		i++;
	while (s1[i])
	{
		tmp = i;
		while (s1[tmp] && is_sep(set, s1[tmp]))
			tmp++;
		if (s1[tmp] == '\0')
			return (len);
		i++;
		len++;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	int		i;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (is_sep(set, s1[i]))
	{
		if (s1[i] == '\0')
		{
			dest = malloc(1);
			if (!dest)
				return (NULL);
			dest[0] = '\0';
			return (dest);
		}
		i++;
	}
	dest = ft_substr(s1, i, trim_len(s1, set));
	return (dest);
}
