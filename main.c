/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:40:52 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/30 19:26:56 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <fcntl.h>	// for open

char	*read_map(char *file, t_fdf *fdf)
{
	int		fd;
	char	*line;
	char	*map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_handler(ERROR_FILE);
	line = get_next_line(fd);
	if (!line)
		ft_error_handler(ERROR_EMPTY);
	map = ft_strdup("");
	while (line != NULL)
	{
		map = gnl_strjoin(map, line, 1);
		fdf->y_elements++;
		free (line);
		if (!map)
		{
			free(map);
			ft_error_handler(ERROR_MEM);
		}
		line = get_next_line(fd);
	}
	close (fd);
	return (map);
}

int	check_map(char *map)
{
	char	**split;

	split = ft_split(map, ' ');
	free_memory(split);
	return (1);
}

void	init_map(char *file, t_fdf *fdf)
{
	fdf->raw_map = read_map(file, fdf);
	printf("%s", *ft_split(fdf->raw_map, '\n'));
	//printf("%s", fdf->raw_map);
	//if (!check_map(map))
	//	ft_error_handler(ERROR_MAP);	
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	fdf.y_elements = 0;
	fdf.x_elements = 0;
	if (argc != 2)
		ft_error_handler(ERROR_ARGS);
	init_map(argv[1], &fdf);
	//ft_printf("%d", fdf.y_elements);
	free(fdf.raw_map);
	//fdf.mlx = mlx_init();
	//fdf.mlx_win = mlx_new_window(fdf.mlx, WIDTH, HEIGHT, "FdF");
	//mlx_loop(fdf.mlx);	
	return (0);
}
