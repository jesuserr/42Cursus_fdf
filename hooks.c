/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:54:26 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/05 12:37:22 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_pressed(int keycode, t_fdf *fdf)
{
	if (keycode == ESC_KEY)
		close_window(fdf);
	else if (keycode == Q_KEY || keycode == W_KEY || keycode == A_KEY
		|| keycode == S_KEY || keycode == Z_KEY || keycode == X_KEY
		|| keycode == LEFT_KEY || keycode == RIGHT_KEY || keycode == DOWN_KEY
		|| keycode == UP_KEY)
		key_action_1(keycode, fdf);
	else if (keycode == I_KEY || keycode == O_KEY || keycode == P_KEY)
		key_action_2(keycode, fdf);
	else if (keycode == BAR_KEY)
		key_action_3(keycode, fdf);
	return (0);
}

/* Checking y > 0 prevents a click in the window title to become an event */

int	mouse_pressed(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	if (button >= 1 && button <= 5 && y > 0)
		mouse_action_1(button, fdf);
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
