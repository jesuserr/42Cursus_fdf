/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:47:50 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/15 15:24:14 by jesuserr         ###   ########.fr       */
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
		fdf->angle_y -= ROT_ANGLE;
	else if (keycode == 1)
		fdf->angle_y += ROT_ANGLE;
	else if (keycode == 6)
		fdf->angle_z -= ROT_ANGLE;
	else if (keycode == 7)
		fdf->angle_z += ROT_ANGLE;
	action_aux(fdf);
}

void	key_action_2(int keycode, t_fdf *fdf)
{
	unrotate(fdf);
	if (keycode == 35)
	{
		fdf->zoom = INIT_ZOOM;
		fdf->offset_x = 0;
		fdf->offset_y = 0;
		fdf->angle_x = 90;
		fdf->angle_y = 0;
		fdf->angle_z = 0;
		recover_height(fdf);
	}
	else if (keycode == 123)
		fdf->offset_x -= INC_OFFSET;
	else if (keycode == 124)
		fdf->offset_x += INC_OFFSET;
	else if (keycode == 125)
		fdf->offset_y += INC_OFFSET;
	else if (keycode == 126)
		fdf->offset_y -= INC_OFFSET;
	action_aux(fdf);
}

void	mouse_action_1(int button, t_fdf *fdf)
{
	unrotate(fdf);
	if (button == 4)
		fdf->zoom *= INC_ZOOM;
	else if (button == 5)
		fdf->zoom /= INC_ZOOM;
	else if (button == 1 || button == 2)
		modify_height(button, fdf);
	else if (button == 3)
	{
		fdf->zoom = INIT_ZOOM;
		fdf->offset_x = 0;
		fdf->offset_y = 0;
		fdf->angle_x = 45;
		fdf->angle_y = 35;
		fdf->angle_z = 30;
		recover_height(fdf);
	}	
	action_aux(fdf);
}
/* Erases the image in memory; calculates and writes the new one */
/* Keeps angles always between 0-359 degrees and prints info bar */
/* if screen is big enough */

void	action_aux(t_fdf *fdf)
{
	ft_bzero(fdf->img.addr, WIDTH * HEIGHT * fdf->img.bpp / 8);
	if (fdf->angle_x == 360)
		fdf->angle_x = 0;
	else if (fdf->angle_x == -1)
		fdf->angle_x = 359;
	if (fdf->angle_y == 360)
		fdf->angle_y = 0;
	else if (fdf->angle_y == -1)
		fdf->angle_y = 359;
	if (fdf->angle_z == 360)
		fdf->angle_z = 0;
	else if (fdf->angle_z == -1)
		fdf->angle_z = 359;
	rotate(fdf);
	projection(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img.img, 0, 0);
	if (WIDTH > MIN_WIDTH && HEIGHT > MIN_HEIGHT)
		print_info(fdf);
}
