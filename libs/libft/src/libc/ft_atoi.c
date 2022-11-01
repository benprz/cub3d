/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 18:27:49 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/04/13 13:55:50 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	val;
	int	neg;

	val = 0;
	neg = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		neg = 1;
	if (neg || *str == '+')
		str++;
	while (ft_isdigit(*str))
		val = val * 10 + (*str++ - '0');
	if (neg)
		return (-val);
	return (val);
}
