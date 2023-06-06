/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:23:42 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/06 15:45:29 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Uses GNL to read the fdf map and counts the elements of the first row */

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
	fdf->x_elem = count_x_elem(line, 0);
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

/* Returns the number of elements on a given line */
/* Same function as the one used in ft_printf with modification */
/* to deal with line feeds \n (var jump) */

int	count_x_elem(char *line, int jump)
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

/* Verifies that all lines have the same number of elements */
/* and that each line doesn't contain forbidden characters (STR_1) */
/* If there is only one line (no 3D element) -> finishes too */
/* After parsing the map, centers also the Z coordinates, figure centered */

void	check_map(t_fdf *fdf)
{
	char	**split;
	char	*line;
	int		i;

	split = ft_split(fdf->raw_map, '\n');
	while (split[fdf->y_elem])
	{
		line = split[fdf->y_elem++];
		if (ft_strlen(line) != ft_strspn(line, STR_1)
			|| count_x_elem(line, 1) != fdf->x_elem)
			free_split_and_exit(split, ERROR_MAP, fdf->raw_map);
	}
	if (fdf->y_elem < 2)
		free_split_and_exit(split, ERROR_MAP, fdf->raw_map);
	fdf->map = malloc (sizeof(t_point) * fdf->y_elem * fdf->x_elem);
	if (!fdf->map)
		free_split_and_exit(split, ERROR_MEM, fdf->raw_map);
	i = 0;
	ft_printf ("%sOK!\nParsing Map... ", BLUE);
	while (split[i])
		parse_map(fdf, split[i++]);
	if (fdf->z_max != -fdf->z_min)
		z_centering(fdf);
	free_split(split);
}

/* Parses the map in such way that X = 0 and Y = 0 are in the center */
/* Determines max and min values of Z to center all heights later */
/* Note: k can be replaced by (i + (j * fdf->x_elem)) */
/*       harder to read but can help to salve a couple of lines if needed */

void	parse_map(t_fdf *fdf, char *line)
{
	char		**split;
	int			i;
	static int	j = 0;
	static int	k = 0;

	split = ft_split(line, ' ');
	i = 0;
	while (i < fdf->x_elem)
	{
		fdf->map[k].x = i + ((fdf->x_elem / -2.0) + 0.5);
		fdf->map[k].y = j + ((fdf->y_elem / -2.0) + 0.5);
		fdf->map[k].z = ft_atoi(split[i]);
		if (fdf->map[k].z > fdf->z_max)
			fdf->z_max = fdf->map[k].z;
		if (fdf->map[k].z < fdf->z_min)
			fdf->z_min = fdf->map[k].z;
		if (ft_strstr(split[i], ",0x"))
			fdf->map[k].color = get_hex_color(split[i]);
		else
			fdf->map[k].color = DEF_COLOR;
		k++;
		i++;
	}
	j++;
	free_split(split);
}
//printf("\n%f %f %f", fdf->map[k].x, fdf->map[k].y, fdf->map[k].z);
//ft_printf("%d ", fdf->map[k].color);
//printf("%x ", fdf->map[k].color);
//ft_printf("%d ", k);

/* Converts the str containing the hex color to an int value */
/* similar philosophy as ft_atoi */

int	get_hex_color(char *hex_color)
{
	char	**split;
	int		color;
	int		i;
	char	*str;

	i = 0;
	color = 0;
	split = ft_split(hex_color, ',');
	str = split[1] + 2;
	while (i < 6 && str[i] != '\0')
	{
		color = color * 16;
		if (str [i] >= '0' && str [i] <= '9')
			color = color + str [i] - '0';
		else if (str [i] >= 'a' && str [i] <= 'f')
			color = color + str [i] - 87;
		else if (str [i] >= 'A' && str [i] <= 'F')
			color = color + str [i] - 55;
		i++;
	}	
	free_split(split);
	return (color);
}
//ft_printf("%d\n", color);
