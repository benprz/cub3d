/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/15 15:08:44 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/04/30 17:14:02 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

static size_t	count_words(const char *s, char c)
{
	size_t	nwords;

	nwords = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
		nwords++;
	}
	return (nwords);
}

static char	*parse_word(const char *s, const char c, size_t current_word)
{
	size_t	i;

	while (*s && *s == c)
		s++;
	while (*s && current_word)
	{
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
		current_word--;
	}
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (ft_strndup(s, i));
}

char	**ft_split(const char *s, const char c)
{
	char	**array;
	size_t	nwords;
	size_t	i;

	nwords = count_words(s, c);
	array = (char **)ft_calloc(nwords + 1, sizeof(char *));
	if (array)
	{
		i = 0;
		while (i != nwords)
		{
			array[i] = parse_word(s, c, i);
			if (!array[i])
			{
				ft_free_2d((void **)array, nwords);
				return (NULL);
			}
			i++;
		}
	}
	return (array);
}
