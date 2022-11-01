/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_calloc.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 19:20:54 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/01/27 14:46:14 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

void	*ft_calloc(const size_t count, const size_t size)
{
	void	*ptr;
	size_t	len;

	ptr = NULL;
	len = size * count;
	if (len > 0)
	{
		ptr = malloc(len);
		if (ptr)
			ft_bzero(ptr, len);
	}
	return (ptr);
}
