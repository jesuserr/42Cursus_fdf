/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:47:50 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/16 12:44:39 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Rotations and arrow keys movements */

void	key_action_1(int keycode, t_fdf *fdf)
{
	unrotate(fdf);
	if (keycode == W_KEY)
		fdf->angle_x += ROT_ANGLE;
	else if (keycode == Q_KEY)
		fdf->angle_x -= ROT_ANGLE;
	else if (keycode == A_KEY)
		fdf->angle_y -= ROT_ANGLE;
	else if (keycode == S_KEY)
		fdf->angle_y += ROT_ANGLE;
	else if (keycode == Z_KEY)
		fdf->angle_z -= ROT_ANGLE;
	else if (keycode == X_KEY)
		fdf->angle_z += ROT_ANGLE;
	else if (keycode == LEFT_KEY)
		fdf->offset_x -= INC_OFFSET;
	else if (keycode == RIGHT_KEY)
		fdf->offset_x += INC_OFFSET;
	else if (keycode == DOWN_KEY)
		fdf->offset_y += INC_OFFSET;
	else if (keycode == UP_KEY)
		fdf->offset_y -= INC_OFFSET;
	action_aux(fdf);
}

/* Deals with the three available views */

void	key_action_2(int keycode, t_fdf *fdf)
{
	unrotate(fdf);
	fdf->zoom = INIT_ZOOM;
	fdf->offset_x = 0;
	fdf->offset_y = 0;
	fdf->angle_z = 0;
	if (keycode == I_KEY)
	{
		fdf->angle_x = 0;
		fdf->angle_y = 0;
	}
	else if (keycode == O_KEY)
	{	
		fdf->angle_x = 90;
		fdf->angle_y = 0;
	}
	else if (keycode == P_KEY)
	{	
		fdf->angle_x = 90;
		fdf->angle_y = 90;
	}
	recover_height(fdf);
	action_aux(fdf);
}

/* Three-axxis rotation at the same time */

void	key_action_3(int keycode, t_fdf *fdf)
{
	(void)keycode;
	unrotate(fdf);
	fdf->angle_x += ROT_ANGLE;
	fdf->angle_y += ROT_ANGLE;
	fdf->angle_z += ROT_ANGLE;
	action_aux(fdf);
}

/* Zoom, height scale and ISO view */

void	mouse_action_1(int button, t_fdf *fdf)
{
	unrotate(fdf);
	if (button == WHEEL_UP)
		fdf->zoom *= INC_ZOOM;
	else if (button == WHEEL_DOWN)
		fdf->zoom /= INC_ZOOM;
	else if (button == LB_BUTTON || button == RB_BUTTON)
		modify_height(button, fdf);
	else if (button == WHEEL_BUTTON)
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
