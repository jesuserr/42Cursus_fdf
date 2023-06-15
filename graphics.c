/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:03:40 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/16 00:09:09 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->img.addr + (y * fdf->img.len + x * (fdf->img.bpp / 8));
	*(unsigned int *)dst = color;
}

/* Uses Bresenham's line algorithm (extended to work in any octant) */
/* Pixels outside screen boundaries (including info bar) are not printed */

void	draw_line(t_line line, t_fdf *fdf)
{
	t_line_aux	line_aux;

	line_direction (&line, &line_aux);
	line_aux.dx = abs(line.x1 - line.x0);
	line_aux.dy = -abs(line.y1 - line.y0);
	line_aux.error = line_aux.dx + line_aux.dy;
	while (!(line.x0 == line.x1 && line.y0 == line.y1))
	{
		if (line.x0 >= 0 && line.y0 >= (0 + fdf->bar_size)
			&& line.x0 < WIDTH && line.y0 < HEIGHT)
			mlx_put_pixel(fdf, line.x0, line.y0, line.color0);
		if ((2 * line_aux.error) >= line_aux.dy)
		{			
			line_aux.error = line_aux.error + line_aux.dy;
			line.x0 = line.x0 + line_aux.sx;
		}
		else
		{
			line_aux.error = line_aux.error + line_aux.dx;
			line.y0 = line.y0 + line_aux.sy;
		}
	}
}

void	line_direction(t_line *line, t_line_aux *line_aux)
{
	if (line->x0 < line->x1)
		line_aux->sx = 1;
	else
		line_aux->sx = -1;
	if (line->y0 < line->y1)
		line_aux->sy = 1;
	else
		line_aux->sy = -1;
}

void	print_info(t_fdf *fdf)
{
	char	*str;

	str = ft_itoa((int)fdf->angle_x);
	mlx_string_put(fdf->mlx, fdf->mlx_win, 10, 22, DEF_COLOR, "x:");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 40, 22, WHITE, str);
	free(str);
	str = ft_itoa((int)fdf->angle_y);
	mlx_string_put(fdf->mlx, fdf->mlx_win, 80, 22, DEF_COLOR, "y:");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 110, 22, WHITE, str);
	free(str);
	str = ft_itoa((int)fdf->angle_z);
	mlx_string_put(fdf->mlx, fdf->mlx_win, 150, 22, DEF_COLOR, "z:");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 180, 22, WHITE, str);
	free(str);
	mlx_string_put(fdf->mlx, fdf->mlx_win, 230, 10, DEF_COLOR, "Rot.x:");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 300, 10, WHITE, "Q/W");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 350, 10, DEF_COLOR, "Rot.y:");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 420, 10, WHITE, "A/S");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 470, 10, DEF_COLOR, "Rot.z:");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 540, 10, WHITE, "Z/X");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 590, 10, DEF_COLOR, "Alt.Views:");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 700, 10, WHITE, "I/O/P");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 770, 10, DEF_COLOR, "Zoom:");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 830, 10, WHITE, "Mouse Wheel");
	print_next_line(fdf);
}

void	print_next_line(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx, fdf->mlx_win, 230, 35, DEF_COLOR, "Iso View:");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 330, 35, WHITE, "Press Wheel");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 470, 35, DEF_COLOR, "Scale Height:");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 610, 35, WHITE, "Mouse RB/LB");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 770, 35, DEF_COLOR, "Move:");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 830, 35, WHITE, "Arrow Keys");
}
