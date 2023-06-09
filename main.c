/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:40:52 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/09 20:07:59 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map(char *file, t_fdf *fdf)
{
	ft_printf ("%sReading Map..... ", BLUE);
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
	fdf->mlx_win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, s);
	img->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->endian);
}

void	iso_view(t_fdf *fdf, t_img *img)
{
	rotate_x(fdf, 45);
	rotate_y(fdf, 35);
	rotate_z(fdf, 30);
	projection(fdf, img);
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
	mlx_put_image_to_window(fdf.mlx, fdf.mlx_win, img.img, 0, 0);
	mlx_key_hook(fdf.mlx_win, key_hook, &fdf);
	mlx_mouse_hook(fdf.mlx_win, mouse_hook, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
//add mlx_hook - protect mlx calls?
