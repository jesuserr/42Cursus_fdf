/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:40:52 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/12 17:01:30 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map(char *file, t_fdf *fdf)
{
	fdf->raw_map = read_map(file, fdf);
	fdf->z_max = INT_MIN;
	fdf->z_min = INT_MAX;
	ft_printf ("%sOK!\nAnalyzing Map... ", BLUE);
	check_map(fdf);
	ft_printf ("%sOK!\n", BLUE);
}

void	init_win(t_fdf *fdf, t_img *img, char *s)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		free_map_and_exit(fdf, ERROR_MLX, 0);
	fdf->mlx_win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, s);
	if (!fdf->mlx_win)
		free_map_and_exit(fdf, ERROR_MLX, 1);
	img->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!img->img)
		free_map_and_exit(fdf, ERROR_MLX, 2);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->endian);
}

void	iso_view(t_fdf *fdf, t_img *img)
{
	rotate_x(fdf, 45);
	rotate_y(fdf, 35);
	rotate_z(fdf, 30);
	projection(fdf, img);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, img->img, 0, 0);
}

void	init_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->mlx_win, 17, 0, close_window, fdf);
	mlx_key_hook(fdf->mlx_win, key_hook, fdf);
	mlx_mouse_hook(fdf->mlx_win, mouse_hook, fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	t_img	img;

	if (argc != 2)
		ft_error_handler(ERROR_ARGS);
	init_map(argv[1], &fdf);
	init_win(&fdf, &img, argv[1]);
	iso_view(&fdf, &img);
	init_hooks(&fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
