/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset_uint32.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 13:12:43 by bperez            #+#    #+#             */
/*   Updated: 2021/04/30 17:07:46 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

void	ft_memset_uint32(void *ptr, const uint32_t value, size_t len_32)
{
	__uint128_t	*ptr_128;
	size_t		len_128;

	ptr_128 = (__uint128_t *)ptr;
	len_128 = len_32 * 0.25;
	if (len_32-- % 4)
	{
		*((uint32_t *)(ptr_128 + len_128)) = value;
		if (len_32-- % 4)
		{
			*((uint32_t *)(ptr_128 + len_128) + 1) = value;
			if (len_32 % 4)
				*((uint32_t *)(ptr_128 + len_128) + 2) = value;
		}
	}
	while (len_128--)
	{
		ptr_128[len_128] = value;
		ptr_128[len_128] |= ptr_128[len_128] << 32;
		ptr_128[len_128] |= ptr_128[len_128] << 64;
	}
}
