/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 17:35:31 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/04/30 17:17:07 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*s3;
	size_t	len1;
	size_t	len2;

	s3 = NULL;
	if (s1 || s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		s3 = (char *)ft_calloc(len1 + len2 + 1, sizeof(char));
		if (s3)
		{
			s3 += len1 + len2;
			while (len2--)
				*--s3 = s2[len2];
			while (len1--)
				*--s3 = s1[len1];
		}
	}
	return (s3);
}
