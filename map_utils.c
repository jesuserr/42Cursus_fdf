/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:23:42 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/31 20:38:15 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Returns the map read with GNL and x elements (only first row for x */

char	*read_map(char *file, t_fdf *fdf)
{
	int		fd;
	char	*line;
	char	*map;
	char	*backup_map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_handler(ERROR_FILE);
	line = get_next_line(fd);
	if (!line)
		ft_error_handler(ERROR_EMPTY);
	fdf->x_elements = count_x_elements(line, 0);
	map = ft_strdup("");
	while (line != NULL)
	{
		backup_map = map;
		map = gnl_strjoin(map, line, 1);
		free (line);
		if (!map)
			free_and_exit(ERROR_MEM, backup_map);
		line = get_next_line(fd);
	}
	close (fd);
	return (map);
}

/* Returns the number of x elements of the first row only */

int	count_x_elements(char *line, int jump)
{
	int	flag;
	int	n;

	flag = 0;
	n = 0;
	while (*line)
	{
		if (*line == ' ')
			flag = 0;
		if (*line != ' ' && flag == 0)
		{
			flag = 1;
			n++;
		}
		line++;
	}
	if (*(line - 2) == ' ' && jump == 0)
		n--;
	return (n);
}

void	check_map(t_fdf *fdf)
{
	char	**split;

	fdf->y_elements = 0;
	split = ft_split(fdf->raw_map, '\n');
	while (split[fdf->y_elements])
	{
		if (count_x_elements(split[fdf->y_elements++], 1) != fdf->x_elements)
		{
			free_memory(split);
			free_and_exit(ERROR_MAP, fdf->raw_map);
		}
		ft_printf("\n%s\n", (split[fdf->y_elements - 1]));
	}
	free_memory(split);
}

	//ft_printf("%s\n", (split[0]));
	//ft_printf("%d\n", count_x_elements(split[0]));
	/*	fdf->map = malloc (1000);
	fdf->map->x = 1;
	fdf->map->y = 2;
	fdf->map->z = 3;
	printf("%f", fdf->map->x);
	fdf->map++;
	fdf->map->x = 4;
	fdf->map->y = 5;
	fdf->map->z = 6;
	printf("%f", fdf->map->y);
	fdf->map--;
	printf("%f", fdf->map->z);*/
