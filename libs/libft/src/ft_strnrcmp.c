/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnrcmp.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/22 13:18:46 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/05/08 16:05:11 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

#include <stddef.h>

int	ft_strnrcmp(const char *s1, const char *s2, size_t n)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	while (n-- && len1 && len2)
	{
		len1--;
		len2--;
		if (((unsigned char *)s1)[len1] != ((unsigned char *)s2)[len2])
			return (((unsigned char *)s1)[len1] - ((unsigned char *)s2)[len2]);
	}
	if (!len1 || !len2)
		return (((unsigned char *)s1)[len1] - ((unsigned char *)s2)[len2]);
	return (0);
}
