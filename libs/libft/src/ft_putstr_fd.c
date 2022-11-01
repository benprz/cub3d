/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putstr_fd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/16 18:45:01 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/23 16:59:38 by bperez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>

void	ft_putstr_fd(const char *s, const int fd)
{
	if (s && fd >= 0)
		write(fd, s, ft_strlen(s));
}
