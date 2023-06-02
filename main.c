/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:40:52 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/02 12:34:55 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map(char *file, t_fdf *fdf)
{
	ft_printf ("%sReading Map... ", BLUE);
	fdf->raw_map = read_map(file, fdf);
	ft_printf ("%sOK!\nAnalyzing Map... ", BLUE);
	check_map(fdf);
	ft_printf ("%sOK!\n", BLUE);
	fdf->elements = fdf->x_elements * fdf->y_elements;
	ft_printf("%s", fdf->raw_map);
	ft_printf(" x:%d ", fdf->x_elements);
	ft_printf(" y:%d ", fdf->y_elements);
	ft_printf(" total:%d ", fdf->elements);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		ft_error_handler(ERROR_ARGS);
	init_map(argv[1], &fdf);
	free(fdf.raw_map);
	return (0);
}
	//fdf.mlx = mlx_init();
	//fdf.mlx_win = mlx_new_window(fdf.mlx, WIDTH, HEIGHT, "FdF");
	//mlx_loop(fdf.mlx);	
