/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_memset.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: erocha-- <erocha--@student.42.fr>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/10/14 17:48:56 by erocha--		   #+#	  #+#			  */
/*	 Updated: 2025/10/16 15:42:04 by erocha--		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset( void *pointer, int value, size_t count )
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)pointer;
	i = 0;
	while (i < count)
	{
		ptr[i] = value;
		i++;
	}
	return (ptr);
}
