/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/10 10:22:34 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/04/30 17:11:28 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>

int	ft_putstr(const char *str)
{
	int	len;

	len = -1;
	if (str)
		len = write(1, str, ft_strlen(str));
	return (len);
}
