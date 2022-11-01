/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_dtoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/06 18:36:36 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/04/30 17:05:12 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

static short	count_chars(long long n)
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

char	*ft_dtoa(const long long n)
{
	char				*str;
	unsigned long long	n2;
	short				len;
	short				neg;

	len = count_chars(n);
	neg = n < 0;
	n2 = (unsigned long long)n;
	if (neg)
		n2 = -(unsigned long long)n;
	str = (char *)malloc((len + neg + 1) * sizeof(char));
	if (str)
	{
		str[len + neg] = '\0';
		while (len--)
		{
			str[len + neg] = n2 % 10 + '0';
			n2 /= 10;
		}
		if (neg)
			str[0] = '-';
	}
	return (str);
}
