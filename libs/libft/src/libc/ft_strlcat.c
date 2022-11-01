/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 16:21:38 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/23 17:56:51 by bperez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (size <= dlen)
		return (slen + size);
	if (size <= dlen + slen)
	{
		ft_memcpy(dst + dlen, src, size - dlen - 1);
		dst[size - 1] = '\0';
	}
	else
		ft_memcpy(dst + dlen, src, slen + 1);
	return (dlen + slen);
}
