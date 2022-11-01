/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcdup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 13:31:37 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/04/30 17:14:45 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

char	*ft_strcdup(const char *s1, const int c)
{
	char	*s2;
	size_t	len;

	s2 = NULL;
	if (s1)
	{
		len = ft_strclen(s1, c);
		s2 = (char *)malloc(sizeof(char) * (len + 1));
		if (s2)
		{
			s2[len] = '\0';
			while (len--)
				s2[len] = s1[len];
		}
	}
	return (s2);
}
