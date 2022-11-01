/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_regex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:27:07 by bperez            #+#    #+#             */
/*   Updated: 2021/04/30 17:11:55 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	check_regex(char c, char *regex)
{
	while (*regex)
	{
		if (c == *regex)
			return (1);
		regex++;
	}
	return (0);
}

int	ft_regex(char *str, char *regex)
{
	if (str && regex)
	{
		while (*str)
		{
			if (!check_regex(*str, regex))
				return (0);
			str++;
		}
	}
	return (1);
}
