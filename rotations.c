/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:22:46 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/09 19:44:00 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* All rotations are clockwise */

void	rotate_x(t_fdf *fdf, float angle)
{
	int		i;
	float	copy_y;
	float	copy_z;

	i = 0;
	angle = angle * PI / 180;
	while (i < (fdf->x_elem * fdf->y_elem))
	{
		copy_y = fdf->map[i].y;
		copy_z = fdf->map[i].z;
		fdf->map[i].y = (copy_y * cos(angle)) - (copy_z * sin(angle));
		fdf->map[i].z = (copy_y * sin(angle)) + (copy_z * cos(angle));
		i++;
	}
}

void	rotate_y(t_fdf *fdf, float angle)
{
	int		i;
	float	copy_x;
	float	copy_z;

	i = 0;
	angle = angle * PI / 180;
	while (i < (fdf->x_elem * fdf->y_elem))
	{
		copy_x = fdf->map[i].x;
		copy_z = fdf->map[i].z;
		fdf->map[i].x = (copy_x * cos(angle)) - (copy_z * sin(angle));
		fdf->map[i].z = (copy_z * cos(angle)) + (copy_x * sin(angle));
		i++;
	}
}

void	rotate_z(t_fdf *fdf, float angle)
{
	int		i;
	float	copy_x;
	float	copy_y;

	i = 0;
	angle = angle * PI / 180;
	while (i < (fdf->x_elem * fdf->y_elem))
	{
		copy_x = fdf->map[i].x;
		copy_y = fdf->map[i].y;
		fdf->map[i].x = (copy_x * cos(angle)) - (copy_y * sin(angle));
		fdf->map[i].y = (copy_x * sin(angle)) + (copy_y * cos(angle));
		i++;
	}
}
