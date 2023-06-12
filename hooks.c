/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:54:26 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/12 10:21:39 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Without mlx_destroy_window and free(fdf->mlx) there is no leaks either !?? */

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
	{
		free(fdf->raw_map);
		free(fdf->map);
		mlx_destroy_window(fdf->mlx, fdf->mlx_win);
		free(fdf->mlx);
		exit (0);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fdf *fdf)
{
	(void)fdf;
	ft_printf("\n%d %d %d", button, x, y);
	return (0);
}
