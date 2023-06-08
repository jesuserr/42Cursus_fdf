/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:22:46 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/08 17:09:05 by jesuserr         ###   ########.fr       */
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
/* Scales figure according screen size and INIT_SCALE value */
/* Uses the worst case scale (smaller one) between x and y */
/* Writes projection directly in screen buffer */
/* Values outside screen boundaries are not printed */

void	projection(t_fdf *fdf, t_img *img)
{
	int		i;
	float	x;
	float	y;

	fdf->scale_x = (WIDTH * INIT_SCALE) / (fdf->x_elem - 1);
	fdf->scale_y = (HEIGHT * INIT_SCALE) / (fdf->y_elem - 1);
	if (fdf->scale_x < fdf->scale_y)
		fdf->scale = fdf->scale_x;
	else
		fdf->scale = fdf->scale_y;
	i = 0;
	while (i < (fdf->x_elem * fdf->y_elem))
	{
		x = (fdf->map[i].x * fdf->scale) + (WIDTH / 2);
		y = (fdf->map[i].y * fdf->scale) + (HEIGHT / 2);
		if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
			mlx_put_pixel(img, x, y, fdf->map[i].color);
		i++;
	}
}