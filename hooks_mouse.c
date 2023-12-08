/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:50:27 by jesuserr          #+#    #+#             */
/*   Updated: 2023/12/08 10:02:54 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Checking y > 0 prevents a click in the window title to become an event */
int	mouse_pressed(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	if (button == LB_BUTTON && y > 0)
		fdf->key.mlb_press = 1;
	else if (button == RB_BUTTON && y > 0)
		fdf->key.mrb_press = 1;
	else if (button == WHEEL_BUTTON && y > 0)
		fdf->key.mwb_press = 1;
	else if (button == WHEEL_UP && y > 0 && fdf->zoom < ZOOM_MAX)
		fdf->zoom *= INC_ZOOM;
	else if (button == WHEEL_DOWN && y > 0 && fdf->zoom > ZOOM_MIN)
		fdf->zoom /= INC_ZOOM;
	return (0);
}

int	mouse_released(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == LB_BUTTON)
		fdf->key.mlb_press = 0;
	else if (button == RB_BUTTON)
		fdf->key.mrb_press = 0;
	else if (button == WHEEL_BUTTON)
		fdf->key.mwb_press = 0;
	return (0);
}
