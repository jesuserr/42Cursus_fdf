/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:20:00 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/22 16:39:17 by jesuserr         ###   ########.fr       */
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
	mlx_string_put(mlx, mlx_win, 100, 100, 0xccccff, "hola");
	mlx_pixel_put(mlx, mlx_win, 200, 200, 0xccccff);
	mlx_loop(mlx);
}
