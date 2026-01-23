/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_strrchr.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: erocha-- <erocha--@student.42.fr>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/10/15 12:45:40 by erocha--		   #+#	  #+#			  */
/*	 Updated: 2025/10/16 17:07:43 by erocha--		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int searchc)
{
	int				i;
	unsigned char	c;

	c = (unsigned char) searchc;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == c)
			return ((char *)s + i);
		i--;
	}
	if (c == '\0' && !s[i])
		return ((char *)s + i);
	return (NULL);
}
