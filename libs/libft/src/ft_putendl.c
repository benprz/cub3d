/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putendl.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/22 12:05:48 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/04/30 17:09:23 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl(const char *str)
{
	int	len;

	len = ft_putstr(str);
	if (len >= 0)
		ft_putchar('\n');
	return (len);
}
