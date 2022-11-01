/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 20:05:00 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/30 13:14:37 by bperez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	s2 = NULL;
	if (s1)
	{
		len = ft_strlen(s1);
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
