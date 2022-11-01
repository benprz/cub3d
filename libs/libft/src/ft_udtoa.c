/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_udtoa.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 11:04:48 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/04/30 17:27:39 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

static short	count_chars(unsigned long long n)
{
	short	len;

	len = 1;
	while (n / 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_udtoa(unsigned long long n)
{
	char	*str;
	short	len;

	len = count_chars(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str)
	{
		str[len] = '\0';
		while (len--)
		{
			str[len] = n % 10 + '0';
			n /= 10;
		}
	}
	return (str);
}
