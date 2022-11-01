/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 14:54:47 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 14:27:56 by bperez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *dst, const void *src, const int c, const size_t len)
{
	size_t	i;

	i = 0;
	if (dst && src)
	{
		while (i != len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			if (((unsigned char *)src)[i] == (unsigned char)c)
				return ((void *)((char *)dst + i + 1));
			i++;
		}
	}
	return (NULL);
}
