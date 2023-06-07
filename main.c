/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:40:52 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/07 00:03:45 by jesuserr         ###   ########.fr       */
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
	ft_printf ("%sOK!\nAnalyzing Map... ", BLUE);
	check_map(fdf);
	ft_printf ("%sOK!\n", BLUE);
	//print_map(fdf);
	//printf("\n%d %d", fdf->z_max, fdf->z_min);
}

	//fdf->t_elem = fdf->x_elem * fdf->y_elem;
	//ft_printf("%s", fdf->raw_map);
	//ft_printf(" x:%d ", fdf->x_elem);
	//ft_printf(" y:%d ", fdf->y_elem);
	//ft_printf(" total:%d ", fdf->elements);

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

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	t_img	img;
	int		i;

	if (argc != 2)
		ft_error_handler(ERROR_ARGS);
	init_map(argv[1], &fdf);
	fdf.mlx = mlx_init();
	fdf.mlx_win = mlx_new_window(fdf.mlx, WIDTH, HEIGHT, "FdF");
	img.img = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	i = 0;
	while (i < (fdf.x_elem * fdf.y_elem))
	{
		mlx_put_pixel(&img, (fdf.map[i].x * 5) + (WIDTH / 2), (fdf.map[i].y * 5) + (HEIGHT / 2), fdf.map[i].color);
		i++;
	}
	mlx_put_image_to_window(fdf.mlx, fdf.mlx_win, img.img, 0, 0);
	mlx_key_hook(fdf.mlx_win, key_hook, &fdf);
	mlx_loop(fdf.mlx);
	//free(fdf.raw_map);
	//free(fdf.map);
	return (0);
}

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
