/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:54:26 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/15 01:15:11 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_pressed(int keycode, t_fdf *fdf)
{
	if (keycode == ESC_KEY)
		close_window(fdf);
	else if (keycode == Q_KEY)
		fdf->key.q_press = 1;
	else if (keycode == W_KEY)
		fdf->key.w_press = 1;
	else if (keycode == A_KEY)
		fdf->key.a_press = 1;
	else if (keycode == S_KEY)
		fdf->key.s_press = 1;
	else if (keycode == Z_KEY)
		fdf->key.z_press = 1;
	else if (keycode == X_KEY)
		fdf->key.x_press = 1;
	else if (keycode == LEFT_KEY)
		fdf->key.left_press = 1;
	else if (keycode == RIGHT_KEY)
		fdf->key.right_press = 1;
	else if (keycode == DOWN_KEY)
		fdf->key.down_press = 1;
	else if (keycode == UP_KEY)
		fdf->key.up_press = 1;
	else if (keycode == I_KEY)
		fdf->key.i_press = 1;
	return (key_pressed_aux(keycode, fdf));
}

int	key_pressed_aux(int keycode, t_fdf *fdf)
{
	if (keycode == O_KEY)
		fdf->key.o_press = 1;
	else if (keycode == P_KEY)
		fdf->key.p_press = 1;
	else if (keycode == BAR_KEY)
		fdf->key.bar_press = 1;
	return (0);
}

int	key_released(int keycode, t_fdf *fdf)
{
	if (keycode == Q_KEY)
		fdf->key.q_press = 0;
	else if (keycode == W_KEY)
		fdf->key.w_press = 0;
	else if (keycode == A_KEY)
		fdf->key.a_press = 0;
	else if (keycode == S_KEY)
		fdf->key.s_press = 0;
	else if (keycode == Z_KEY)
		fdf->key.z_press = 0;
	else if (keycode == X_KEY)
		fdf->key.x_press = 0;
	else if (keycode == LEFT_KEY)
		fdf->key.left_press = 0;
	else if (keycode == RIGHT_KEY)
		fdf->key.right_press = 0;
	else if (keycode == DOWN_KEY)
		fdf->key.down_press = 0;
	else if (keycode == UP_KEY)
		fdf->key.up_press = 0;
	else if (keycode == I_KEY)
		fdf->key.i_press = 0;
	else if (keycode == O_KEY)
		fdf->key.o_press = 0;
	return (key_released_aux(keycode, fdf));
}

int	key_released_aux(int keycode, t_fdf *fdf)
{
	if (keycode == P_KEY)
		fdf->key.p_press = 0;
	else if (keycode == BAR_KEY)
		fdf->key.bar_press = 0;
	return (0);
}

int	close_window(t_fdf *fdf)
{
	free(fdf->raw_map);
	free(fdf->map);
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	mlx_destroy_window(fdf->mlx, fdf->mlx_win);
	free(fdf->mlx);
	exit (EXIT_SUCCESS);
}
