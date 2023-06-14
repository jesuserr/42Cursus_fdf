/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:54:26 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/14 08:52:53 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_pressed(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
		close_window(fdf);
	else if (keycode == 13 || keycode == 12 || keycode == 0 || keycode == 1
		|| keycode == 6 || keycode == 7 || keycode == 34)
		redraw(keycode, fdf);
	return (0);
}

void	redraw(int keycode, t_fdf *fdf)
{
	unrotate(fdf);
	if (keycode == 13)
		fdf->angle_x += ROT_ANGLE;
	else if (keycode == 12)
		fdf->angle_x -= ROT_ANGLE;
	else if (keycode == 0)
		fdf->angle_y += ROT_ANGLE;
	else if (keycode == 1)
		fdf->angle_y -= ROT_ANGLE;
	else if (keycode == 6)
		fdf->angle_z += ROT_ANGLE;
	else if (keycode == 7)
		fdf->angle_z -= ROT_ANGLE;
	else if (keycode == 34)
	{
		fdf->angle_x = 45;
		fdf->angle_y = 35;
		fdf->angle_z = 30;
	}
	ft_bzero(fdf->img.addr, WIDTH * HEIGHT * fdf->img.bpp / 8);
	rotate(fdf);
	projection(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img.img, 0, 0);
	return ;
}
/* Without mlx_destroy_window and free(fdf->mlx) there is no leaks either !?? */

int	close_window(t_fdf *fdf)
{
	free(fdf->raw_map);
	free(fdf->map);
	mlx_destroy_window(fdf->mlx, fdf->mlx_win);
	free(fdf->mlx);
	exit (EXIT_SUCCESS);
}

int	mouse_hook(int button, int x, int y, t_fdf *fdf)
{
	(void)fdf;
	ft_printf("\n%d %d %d", button, x, y);
	return (0);
}
