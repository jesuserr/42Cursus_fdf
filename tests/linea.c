/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:20:00 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/22 14:55:53 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 640, 480, "Hello world!");
	//mlx_string_put(mlx, mlx_win, 100, 100, 0xccccff, get_next_line(1));
	//mlx_pixel_put(mlx, mlx_win, 200, 200, 0xccccff);
	//mlx_pixel_put(mlx, mlx_win, 300, 300, 0xccccf0);
	
	int s, dx, dy, m, x1, y1, x2, y2;
    float xi, yi, x, y;
    x2 = 100;
	x1 = 1;
	y1 = 1;
	y2 = 100;
	dx = x2 - x1;
    dy = y2 - y1;
    if (abs(dx) > abs(dy))
        s = abs(dx); else
        s = abs(dy);
    xi = dx / (float) s;
    yi = dy / (float) s;
    x = x1;
    y = y1;
	mlx_pixel_put(mlx, mlx_win, x1, y1, 0xccccff);
        
        for (m = 0; m < s; m++) {
                x += xi;
                y += yi;
                mlx_pixel_put(mlx, mlx_win, x, y, 0xccccff);
        }
	mlx_loop(mlx);
}
