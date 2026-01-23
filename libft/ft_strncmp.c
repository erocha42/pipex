/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_strncmp.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: erocha-- <erocha--@student.42.fr>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/10/15 14:29:27 by erocha--		   #+#	  #+#			  */
/*	 Updated: 2025/10/16 15:41:32 by erocha--		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp( const char *first, const char *second, size_t length )
{
	size_t			i;
	unsigned char	*f;
	unsigned char	*s;

	i = 0;
	if (length == 0)
		return (0);
	f = (unsigned char *) first;
	s = (unsigned char *) second;
	while (i < length - 1 && f[i] && f[i] == s[i])
		i++;
	return (f[i] - s[i]);
}
