/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tolower_string.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 17:46:34 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/04/30 17:26:22 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tolower_string(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			str[i] = ft_tolower(str[i]);
			i++;
		}
	}
	return (str);
}
