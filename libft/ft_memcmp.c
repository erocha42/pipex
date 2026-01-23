/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_memcmp.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: erocha-- <erocha--@student.42.fr>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/10/14 11:01:38 by erocha--		   #+#	  #+#			  */
/*	 Updated: 2025/10/16 15:42:25 by erocha--		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t size)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	if (size == 0)
		return (0);
	while ((i < size - 1) && (ptr1[i] == ptr2[i]))
		i++;
	return (ptr1[i] - ptr2[i]);
}
