/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 15:34:13 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/23 19:02:52 by bperez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst && src)
	{
		if (src < dst)
		{
			while (len--)
				((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
		}
		else
		{
			i = 0;
			while (i != len)
			{
				((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
				i++;
			}
		}
	}
	return (dst);
}
