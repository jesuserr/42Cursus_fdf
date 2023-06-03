/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:23:42 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/03 21:06:48 by jesuserr         ###   ########.fr       */
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

/* Returns the number of x elements of the first row only */

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
		{
			free_split(split);
			free_and_exit(ERROR_MAP, fdf->raw_map);
		}	
	}
	fdf->map = malloc (sizeof(t_point) * fdf->y_elem * fdf->x_elem);
	if (!fdf->map)
	{
		free_split(split);
		free_and_exit(ERROR_MEM, fdf->raw_map);		
	}
	i = 0;
	while (split[i])
		parse_map(fdf, split[i++]);
	free_split(split);
}

// k can be replaced by (i + (j * fdf->x_elem)) - it's harder to read 
// but can help to save a couple of lines
// give sense to hex color

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
		if (ft_strstr(split[i], ",0x"))
			fdf->map[k].color = 16777215;
		else
			fdf->map[k].color = -1;
		//printf("\n%f %f %f", fdf->map[k].x, fdf->map[k].y, fdf->map[k].z);
		//printf("%d ", fdf->map[k].color);
		//ft_printf("%d ", k);
		k++;
		i++;
	}
	j++;
	free_split(split);
}
