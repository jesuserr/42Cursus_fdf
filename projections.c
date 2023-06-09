/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:43:38 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/09 20:28:33 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Scales figure according to screen size and INIT_SCALE value */
/* Uses the worst case scale (smaller one) between x and y */
/* Writes projection directly in screen buffer */

void	projection(t_fdf *fdf, t_img *img)
{
	fdf->scale_x = (WIDTH * INIT_SCALE) / (fdf->x_elem - 1);
	fdf->scale_y = (HEIGHT * INIT_SCALE) / (fdf->y_elem - 1);
	if (fdf->scale_x < fdf->scale_y)
		fdf->scale = fdf->scale_x;
	else
		fdf->scale = fdf->scale_y;
	project_x_lines(fdf, img);
	project_y_lines(fdf, img);
	//project_points(fdf, img);
}

/* Draws a line between each pair of horizontal points */
/* A copy of struct "line" is passed to draw_line since */
/* values are modified inside and would affect this function */

void	project_x_lines(t_fdf *fdf, t_img *img)
{
	t_line	line;
	int		i;

	i = 0;
	while (i < (fdf->x_elem * fdf->y_elem))
	{
		line.x0 = (fdf->map[i].x * fdf->scale) + (WIDTH / 2);
		line.y0 = (fdf->map[i].y * fdf->scale) + (HEIGHT / 2);
		line.color0 = fdf->map[i].color;
		if ((i % fdf->x_elem) != 0)
			draw_line(line, img);
		line.x1 = line.x0;
		line.y1 = line.y0;
		line.color1 = line.color0;
		i++;
	}
}

/* Draws a line between each pair of vertical points */
/* A copy of struct "line" is passed to draw_line since */
/* values are modified inside and would affect this function */

void	project_y_lines(t_fdf *fdf, t_img *img)
{
	t_line	line;
	int		i;

	i = 0;
	while (i < (fdf->x_elem * fdf->y_elem))
	{
		line.x0 = (fdf->map[i].x * fdf->scale) + (WIDTH / 2);
		line.y0 = (fdf->map[i].y * fdf->scale) + (HEIGHT / 2);
		line.color0 = fdf->map[i].color;
		if ((i >= fdf->x_elem))
			draw_line(line, img);
		line.x1 = line.x0;
		line.y1 = line.y0;
		line.color1 = line.color0;
		i = i + fdf->x_elem;
		if (i == ((fdf->x_elem * fdf->y_elem) + fdf->x_elem - 1))
			break ;
		if (i >= (fdf->x_elem * fdf->y_elem))
			i = i - ((fdf->x_elem * fdf->y_elem) - 1);
	}
}

/* Draws only the points, no lines */
/* Values outside screen boundaries are not printed */

void	project_points(t_fdf *fdf, t_img *img)
{
	int		i;
	float	x;
	float	y;

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
