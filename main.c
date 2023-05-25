/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:40:52 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/25 21:20:32 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <fcntl.h>	// for open

int	main(int argc, char **argv)
{
	int		fd;
	char	*linea;
	int		i;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			ft_error_handler(ERROR_FILE);
		i = 1;
		linea = get_next_line(fd);
		while (linea != NULL)
		{
			printf ("linea%2d: %s", i, linea);
			i++;
			free (linea);
			linea = get_next_line(fd);
		}
		close(fd);
	}
	else
		ft_error_handler(ERROR_ARGS);
	return (0);
}
