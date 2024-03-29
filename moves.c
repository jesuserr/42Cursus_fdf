/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:47:50 by jesuserr          #+#    #+#             */
/*   Updated: 2023/12/08 21:56:38 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Rotations and arrow keys movements */
void	key_action_1(t_fdf *fdf)
{
	if (fdf->key.w_press || (fdf->key.mou_x_dir == 1 && fdf->key.mlb_press))
		fdf->angle_x += ROT_ANGLE;
	if (fdf->key.q_press || (fdf->key.mou_x_dir == 2 && fdf->key.mlb_press))
		fdf->angle_x -= ROT_ANGLE;
	if (fdf->key.s_press || (fdf->key.mou_y_dir == 1 && fdf->key.mlb_press))
		fdf->angle_y += ROT_ANGLE;
	if (fdf->key.a_press || (fdf->key.mou_y_dir == 2 && fdf->key.mlb_press))
		fdf->angle_y -= ROT_ANGLE;
	if (fdf->key.z_press)
		fdf->angle_z -= ROT_ANGLE;
	if (fdf->key.x_press)
		fdf->angle_z += ROT_ANGLE;
	if (fdf->key.left_press || (fdf->key.mou_y_dir == 1 && fdf->key.mrb_press))
		fdf->offset_x += INC_OFFSET;
	if (fdf->key.right_press || (fdf->key.mou_y_dir == 2 && fdf->key.mrb_press))
		fdf->offset_x -= INC_OFFSET;
	if (fdf->key.down_press || (fdf->key.mou_x_dir == 2 && fdf->key.mrb_press))
		fdf->offset_y -= INC_OFFSET;
	if (fdf->key.up_press || (fdf->key.mou_x_dir == 1 && fdf->key.mrb_press))
		fdf->offset_y += INC_OFFSET;
	fdf->key.mou_x_dir = 0;
	fdf->key.mou_y_dir = 0;
}

/* Deals with the three available views */
void	key_action_2(t_fdf *fdf)
{
	if (fdf->key.i_press == 1 || fdf->key.o_press == 1 || fdf->key.p_press == 1)
	{
		fdf->zoom = INIT_ZOOM;
		fdf->offset_x = 0;
		fdf->offset_y = 0;
		fdf->angle_z = 0;
		recover_height(fdf);
	}
	if (fdf->key.i_press == 1)
	{
		fdf->angle_x = 0;
		fdf->angle_y = 0;
	}
	else if (fdf->key.o_press == 1)
	{
		fdf->angle_x = 90;
		fdf->angle_y = 0;
	}
	else if (fdf->key.p_press == 1)
	{
		fdf->angle_x = 90;
		fdf->angle_y = 90;
	}
}

/* Three-axxis rotation at the same time */
void	key_action_3(t_fdf *fdf)
{
	if (fdf->key.bar_press == 1)
	{
		fdf->angle_x -= THREE_ROT_ANG;
		fdf->angle_y += THREE_ROT_ANG;
		fdf->angle_z -= THREE_ROT_ANG;
	}
	if (fdf->key.one_press || fdf->key.two_press)
		modify_height(fdf);
}

/* Height scale and ISO view */
void	mouse_action_1(t_fdf *fdf)
{
	if (fdf->key.mwb_press)
	{
		fdf->zoom = INIT_ZOOM;
		fdf->offset_x = 0;
		fdf->offset_y = 0;
		fdf->angle_x = 45;
		fdf->angle_y = 35;
		fdf->angle_z = 30;
		recover_height(fdf);
	}
}

/* Erases the image in memory; calculates and writes the new one */
/* Keeps angles always between 0-359 degrees and prints info bar */
/* if screen is big enough */
int	main_loop(t_fdf *fdf)
{
	ft_bzero(fdf->img.addr, WIDTH * HEIGHT * fdf->img.bpp / 8);
	normalize_angles(fdf);
	projection(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img.img, 0, 0);
	if (WIDTH > MIN_WIDTH && HEIGHT > MIN_HEIGHT)
		print_info(fdf);
	unrotate(fdf);
	key_action_1(fdf);
	key_action_2(fdf);
	key_action_3(fdf);
	mouse_action_1(fdf);
	rotate(fdf);
	return (0);
}
