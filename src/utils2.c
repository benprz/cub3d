/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:23:43 by bperez            #+#    #+#             */
/*   Updated: 2021/04/30 15:09:52 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <math.h>

float	fix_degrees(float degrees)
{
	if (degrees < 0)
		degrees += 360;
	else if (degrees >= 360)
		degrees -= 360;
	return (degrees);
}

float	rad(float degrees)
{
	return (degrees * (M_PI / 180));
}

float	deg(float rad)
{
	return (rad * 180 / M_PI);
}

float	calc_distance(t_vector *p1, t_vector *p2)
{
	float	distance;

	distance = sqrtf(
			(p1->x - p2->x) * (p1->x - p2->x) + \
			(p1->y - p2->y) * (p1->y - p2->y));
	return (distance);
}
