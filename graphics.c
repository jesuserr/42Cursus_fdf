/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:03:40 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/09 19:06:09 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	iso_view(t_fdf *fdf, t_img *img)
{
	rotate_x(fdf, 45);
	rotate_y(fdf, 35);
	rotate_z(fdf, 30);
	projection(fdf, img);
}

void	draw_line(t_line line, t_img *img)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
	int	e2;

	dx = abs(line.x1 - line.x0);
	if (line.x0 < line.x1)
		sx = 1;
	else
		sx = -1;
	dy = -abs(line.y1 - line.y0);
	if (line.y0 < line.y1)
		sy = 1;
	else
		sy = -1;
	error = dx + dy;
	while (1)
	{
		mlx_put_pixel(img, line.x0, line.y0, line.color0);
		if (line.x0 == line.x1 && line.y0 == line.y1)
			break ;
		e2 = 2 * error;
		if (e2 >= dy)
		{
			if (line.x0 == line.x1)
				break ;
			error = error + dy;
			line.x0 = line.x0 + sx;
		}
		if (e2 <= dx)
		{
			if (line.y0 == line.y1)
				break ;
			error = error + dx;
			line.y0 = line.y0 + sy;
		}
	}
}
