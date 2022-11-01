/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strschr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 17:02:33 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/04/30 17:23:54 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strschr(const char *s, const char *s2)
{
	int	i;

	while (*s)
	{
		i = 0;
		while (s2[i])
		{
			if (s2[i] == *s)
				return ((char *)s);
			i++;
		}
		s++;
	}
	return (NULL);
}
