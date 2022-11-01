/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strctrim.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 19:04:39 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/04/30 17:16:09 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

#include <stddef.h>
#include <stdlib.h>

static int	get_occurrences(const char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

char	*ft_strctrim(const char *s1, int c)
{
	char	*s2;
	int		occurrences;
	int		i;

	occurrences = get_occurrences(s1, c);
	s2 = malloc(sizeof(char) * (ft_strlen(s1) - occurrences + 1));
	if (s2)
	{
		i = 0;
		while (*s1)
		{
			if (*s1 != c)
				s2[i++] = *s1;
			s1++;
		}
		s2[i] = '\0';
	}
	return (s2);
}
