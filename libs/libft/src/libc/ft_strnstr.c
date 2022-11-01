/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 12:52:28 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/23 18:08:24 by bperez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;
	size_t	i;

	nlen = ft_strlen(needle);
	if (nlen)
		return ((char *)haystack);
	i = 0;
	while (len-- && *haystack)
	{
		if (*haystack == needle[i])
		{
			if (nlen == ++i)
				break ;
		}
		else
		{
			haystack -= i;
			len += i;
			i = 0;
		}
		haystack++;
	}
	if (nlen == i)
		return ((char *)haystack - i + 1);
	return (NULL);
}
