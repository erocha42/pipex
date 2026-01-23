/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_memmove.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: erocha-- <erocha--@student.42.fr>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/10/14 17:29:51 by erocha--		   #+#	  #+#			  */
/*	 Updated: 2025/10/16 15:42:12 by erocha--		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*destptr;
	unsigned char	*srcptr;

	if (!dest && !src)
		return (NULL);
	destptr = (unsigned char *)dest;
	srcptr = (unsigned char *)src;
	if (destptr < srcptr)
		ft_memcpy(destptr, srcptr, n);
	else
	{
		while (n-- > 0)
			destptr[n] = srcptr[n];
	}
	return (dest);
}
