/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/19 10:38:19 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/04/30 17:11:01 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putnstr(const char *str, const int len)
{
	int	ret;

	ret = -1;
	if (str)
		ret = write(1, str, len);
	return (ret);
}
