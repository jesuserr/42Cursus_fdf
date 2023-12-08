/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:40:52 by jesuserr          #+#    #+#             */
/*   Updated: 2023/12/08 15:44:47 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map(char *file, t_fdf *fdf)
{
	fdf->raw_map = read_map(file, fdf);
	fdf->z_max = INT_MIN;
	fdf->z_min = INT_MAX;
	fdf->zoom = INIT_ZOOM;
	fdf->offset_x = INIT_OFFSET_X;
	fdf->offset_y = INIT_OFFSET_Y;
	fdf->user_scale_z = INC_ZOOM_Z;
	fdf->num_scales_z = 0;
	fdf->bar_size = 0;
	ft_memset(&fdf->key, 0, sizeof(t_keys));
	ft_printf ("%sOK!\nAnalyzing Map... ", BLUE);
	check_map(fdf);
	ft_printf ("%sOK!\n", BLUE);
}

void	init_win(t_fdf *fdf, char *s)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		free_map_and_exit(fdf, ERROR_MLX, 0);
	fdf->mlx_win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, s);
	if (!fdf->mlx_win)
		free_map_and_exit(fdf, ERROR_MLX, 1);
	fdf->img.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->img.img)
		free_map_and_exit(fdf, ERROR_MLX, 2);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp, \
		&fdf->img.len, &fdf->img.endian);
}

void	iso_view(t_fdf *fdf)
{
	fdf->angle_x = 45;
	fdf->angle_y = 35;
	fdf->angle_z = 30;
	rotate(fdf);
	if (WIDTH > MIN_WIDTH && HEIGHT > MIN_HEIGHT)
		fdf->bar_size = BAR_INFO_H;
	projection(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img.img, 0, 0);
	if (WIDTH > MIN_WIDTH && HEIGHT > MIN_HEIGHT)
		print_info(fdf);
}

void	init_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->mlx_win, 17, 0, close_window, fdf);
	mlx_hook(fdf->mlx_win, 2, 0, key_pressed, fdf);
	mlx_hook(fdf->mlx_win, 4, 0, mouse_pressed, fdf);
	mlx_loop_hook(fdf->mlx, main_loop, fdf);
	mlx_hook(fdf->mlx_win, 3, 0, key_released, fdf);
	mlx_hook(fdf->mlx_win, 5, 0, mouse_released, fdf);
	mlx_mouse_move(fdf->mlx_win, WIDTH / 2, HEIGHT / 2);
	mlx_hook(fdf->mlx_win, 6, 0, mouse_move, fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;	

	if (argc != 2)
		ft_error_handler(ERROR_ARGS);
	init_map(argv[1], &fdf);
	init_win(&fdf, argv[1]);
	iso_view(&fdf);
	init_hooks(&fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
