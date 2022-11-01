/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_2d.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/23 17:08:53 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/05/05 17:41:11 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_2d(void **array, size_t size)
{
	if (array)
	{
		while (size--)
		{
			if (array[size])
				free(array[size]);
		}
		free(array);
	}
}
