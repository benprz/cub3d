/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_fd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/29 16:03:09 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/04/30 17:10:36 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(const int n, const int fd)
{
	unsigned int	n2;

	n2 = (unsigned int)n;
	if (n < 0)
		n2 = -(unsigned int)n;
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (n2)
	{
		if (n2 / 10)
			ft_putnbr_fd(n2 / 10, fd);
		ft_putchar_fd(n2 % 10 + '0', fd);
	}
	else
		ft_putchar_fd('0', fd);
}
