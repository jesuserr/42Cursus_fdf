/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:54:26 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/14 22:29:44 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_pressed(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
		close_window(fdf);
	else if (keycode == 13 || keycode == 12 || keycode == 0 || keycode == 1
		|| keycode == 6 || keycode == 7 || keycode == 34)
		key_action_1(keycode, fdf);
	else if (keycode == 35 || keycode == 123 || keycode == 124 || keycode == 125
		|| keycode == 126)
		key_action_2(keycode, fdf);
	printf("\n%d %d %d", keycode, fdf->offset_x, fdf->offset_y);
	return (0);
}

int	mouse_pressed(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 4)
		mouse_action_1(button, fdf);
	else if (button == 5)
		mouse_action_1(button, fdf);
	return (0);
}

/* Without mlx_destroy_window & free(fdf->mlx) there are no leaks either !?? */

int	close_window(t_fdf *fdf)
{
	free(fdf->raw_map);
	free(fdf->map);
	mlx_destroy_window(fdf->mlx, fdf->mlx_win);
	free(fdf->mlx);
	exit (EXIT_SUCCESS);
}
