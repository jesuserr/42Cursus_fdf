/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:40:52 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/08 14:00:33 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map(char *file, t_fdf *fdf)
{
	ft_printf ("%sReading Map... ", BLUE);
	fdf->raw_map = read_map(file, fdf);
	fdf->y_elem = 0;
	fdf->z_max = INT_MIN;
	fdf->z_min = INT_MAX;
	fdf->scale_z = SCALE_Z;
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

void	print_map(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < (fdf->x_elem * fdf->y_elem))
	{
		if (i % fdf->x_elem == 0)
			printf("\n");
		printf("\n%f %f ", fdf->map[i].x, fdf->map[i].y);
		printf("%f %d", fdf->map[i].z, fdf->map[i].color);
		i++;
	}
}
