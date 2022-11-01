/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 16:47:21 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/23 18:54:28 by bperez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *p1, const void *p2, const size_t len)
{
	size_t	i;

	i = 0;
	while (i != len)
	{
		if (((unsigned char *)p1)[i] != ((unsigned char *)p2)[i])
			return (((unsigned char *)p1)[i] - ((unsigned char *)p2)[i]);
		i++;
	}
	return (0);
}
