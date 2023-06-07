/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:54:26 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/07 11:57:35 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
	{
		free(fdf->raw_map);
		free(fdf->map);
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
