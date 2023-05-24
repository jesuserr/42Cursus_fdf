/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:20:00 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/24 13:40:52 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_l;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_l + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(int x0, int y0, int x1, int y1, t_data data)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
	int	e2;

	dx = abs(x1 - x0);
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	dy = -abs(y1 - y0);
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	error = dx + dy;
	while (1)
	{
		my_mlx_pixel_put(&data, x0, y0, 0x000000FF);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * error;
		if (e2 >= dy)
		{
			if (x0 == x1)
				break ;
			error = error + dy;
			x0 = x0 + sx;
		}
		if (e2 <= dx)
		{
			if (y0 == y1)
				break ;
			error = error + dx;
			y0 = y0 + sy;
		}
	}
}

void plot_circle (int xm, int ym, int r, t_data data)
{
   int x = -r, y = 0, err = 2-2*r; /* II. Quadrant */ 
   do {	
      my_mlx_pixel_put(&data, xm-x, ym+y, 0x000000FF); /*   I. Quadrant */
      my_mlx_pixel_put(&data, xm-y, ym-x, 0x000000FF); /*  II. Quadrant */
      my_mlx_pixel_put(&data, xm+x, ym-y, 0x000000FF); /* III. Quadrant */
      my_mlx_pixel_put(&data, xm+y, ym+x, 0x000000FF); /*  IV. Quadrant */
      r = err;
      if (r >  x) err += ++x*2+1; /* e_xy+e_x > 0 */
      if (r <= y) err += ++y*2+1; /* e_xy+e_y < 0 */
   } while (x < 0);
}


int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		y;

	y = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_l, &img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	plot_circle (1600, 300, 100, img);
 	while (y < 1080)
	{
		draw_line(0, y, 1919, 1079, img);
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

// Proteger mlx_init & mlx_new_window & mlx_new_image