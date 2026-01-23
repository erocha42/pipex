/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_memcpy.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: erocha-- <erocha--@student.42.fr>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/10/14 17:02:58 by erocha--		   #+#	  #+#			  */
/*	 Updated: 2025/10/16 15:42:18 by erocha--		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*destptr;
	unsigned char	*srcptr;
	size_t			i;

	if (!src && !dest)
		return (NULL);
	i = 0;
	destptr = (unsigned char *)dest;
	srcptr = (unsigned char *)src;
	while (i < n)
	{
		destptr[i] = srcptr[i];
		i++;
	}
	return (dest);
}
