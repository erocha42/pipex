/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_strchr.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: erocha-- <erocha--@student.42.fr>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/10/15 12:04:54 by erocha--		   #+#	  #+#			  */
/*	 Updated: 2025/10/16 17:04:30 by erocha--		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int searchc)
{
	int				i;
	unsigned char	c;

	i = 0;
	c = (unsigned char) searchc;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	if (!s[i] && c == 0)
		return ((char *) s + i);
	return (0);
}
