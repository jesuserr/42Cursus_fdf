/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:34:08 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/07 16:30:19 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              DEFINES
*/
# define BLUE       "\033[0;94m"
# define RED        "\033[0;31m"
# define WHITE      "\033[0;37m"

# define ERROR_ARGS			0
# define ERROR_FILE     	1
# define ERROR_MEM			2
# define ERROR_EMPTY		3
# define ERROR_MAP			4

# define WIDTH		1024
# define HEIGHT		768
# define STR_1		"-0123456789 ,xABCDEFabcdef"
# define DEF_COLOR	16777215
# define PI			3.141592654

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              HEADERS
*/
# include "libft/includes/get_next_line.h"
# include "libft/includes/ft_printf.h"
# include "libft/includes/libft.h"
# include "mlx.h"
# include <fcntl.h>	// for open
# include <math.h>

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              STRUCTS
*/
typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;	
}	t_point;

typedef struct s_fdf
{
	void	*mlx;
	void	*mlx_win;
	char	*raw_map;	
	int		x_elem;
	int		y_elem;
	int		z_max;
	int		z_min;
	t_point	*map;
}	t_fdf;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                        FUNCTION PROTOTYPES
*/
void	ft_error_handler(int error);
void	free_split(char **str);
void	free_and_exit(int error, char *ptr);
void	free_split_and_exit(char **str, int error, char *ptr);

void	mlx_put_pixel(t_img *data, int x, int y, int color);

int		key_hook(int keycode, t_fdf *fdf);
int		mouse_hook(int button, int x, int y, t_fdf *fdf);

void	print_map(t_fdf *fdf);	//temporal for checking

char	*read_map(char *file, t_fdf *fdf);
void	check_map(t_fdf *fdf);
int		count_x_elem(char *line, int jump);
void	parse_map(t_fdf *fdf, char *line);
int		get_hex_color(char *color);

void	rotate_x(t_fdf *fdf, float angle);
void	rotate_y(t_fdf *fdf, float angle);
void	rotate_z(t_fdf *fdf, float angle);

void	z_centering(t_fdf *fdf);

#endif