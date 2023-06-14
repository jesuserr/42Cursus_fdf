/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:47:50 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/14 12:03:56 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_action_1(int keycode, t_fdf *fdf)
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
		fdf->zoom = INIT_ZOOM;
		fdf->offset_x = 0;
		fdf->offset_y = 0;
		fdf->angle_x = 45;
		fdf->angle_y = 35;
		fdf->angle_z = 30;
	}
	key_action_aux(fdf);
	return ;
}

void	key_action_2(int keycode, t_fdf *fdf)
{
	unrotate(fdf);
	if (keycode == 14)
		fdf->zoom *= INC_ZOOM;
	else if (keycode == 15)
		fdf->zoom /= INC_ZOOM;
	else if (keycode == 35)
	{
		fdf->zoom = INIT_ZOOM;
		fdf->offset_x = 0;
		fdf->offset_y = 0;
		fdf->angle_x = 90;
		fdf->angle_y = 0;
		fdf->angle_z = 0;
	}
	else if (keycode == 123)
		fdf->offset_x -= INC_OFFSET;
	else if (keycode == 124)
		fdf->offset_x += INC_OFFSET;
	else if (keycode == 125)
		fdf->offset_y += INC_OFFSET;
	else if (keycode == 126)
		fdf->offset_y -= INC_OFFSET;
	key_action_aux(fdf);
	return ;
}

void	key_action_aux(t_fdf *fdf)
{
	ft_bzero(fdf->img.addr, WIDTH * HEIGHT * fdf->img.bpp / 8);
	rotate(fdf);
	projection(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img.img, 0, 0);
	return ;
}
