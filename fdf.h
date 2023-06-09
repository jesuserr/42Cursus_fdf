/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:34:08 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/09 20:24:49 by jesuserr         ###   ########.fr       */
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

# define ERROR_ARGS			0
# define ERROR_FILE     	1
# define ERROR_MEM			2
# define ERROR_EMPTY		3
# define ERROR_MAP			4

# define WIDTH			1024
# define HEIGHT			768
# define ALLOWED_CHR	"-0123456789 ,xABCDEFabcdef"
# define DEF_COLOR		16777215
# define PI				3.141592654
# define INIT_SCALE		0.66

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

typedef struct s_line
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		color0;
	int		color1;	
}	t_line;

typedef struct s_fdf
{
	void	*mlx;
	void	*mlx_win;
	char	*raw_map;	
	int		x_elem;
	int		y_elem;
	int		z_max;
	int		z_min;
	float	scale_x;
	float	scale_y;
	float	scale_z;
	float	scale;
	t_point	*map;
}	t_fdf;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
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

void	mlx_put_pixel(t_img *img, int x, int y, int color);
void	draw_line(t_line line, t_img *img);

int		key_hook(int keycode, t_fdf *fdf);
int		mouse_hook(int button, int x, int y, t_fdf *fdf);

void	init_map(char *file, t_fdf *fdf);
void	init_win(t_fdf *fdf, t_img *img, char *s);
void	iso_view(t_fdf *fdf, t_img *img);

char	*read_map(char *file, t_fdf *fdf);
void	check_map(t_fdf *fdf);
int		count_x_elem(char *line, int jump);
void	parse_map(t_fdf *fdf, char *line);
int		get_hex_color(char *color);

void	projection(t_fdf *fdf, t_img *img);
void	project_x_lines(t_fdf *fdf, t_img *img);
void	project_y_lines(t_fdf *fdf, t_img *img);
void	project_points(t_fdf *fdf, t_img *img);

void	rotate_x(t_fdf *fdf, float angle);
void	rotate_y(t_fdf *fdf, float angle);
void	rotate_z(t_fdf *fdf, float angle);

void	z_centering(t_fdf *fdf);
void	print_map(t_fdf *fdf);	//temporal for checking

#endif