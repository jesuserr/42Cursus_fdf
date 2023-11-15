/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:34:08 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/15 10:45:07 by jesuserr         ###   ########.fr       */
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
# define ERROR_MLX			5

# define WIDTH			1024
# define HEIGHT			768
# define ALLOWED_CHR	"-0123456789 ,xABCDEFabcdef"
# define DEF_COLOR		0xf26e04
# define WHITE			0xFFFFFF
# define PI				3.141592654
# define INIT_SCALE		0.75
# define ROT_ANGLE		1
# define INIT_ZOOM		1
# define INC_ZOOM		1.03
# define ZOOM_MAX		40
# define ZOOM_MIN		0.1
# define INIT_OFFSET_X	0
# define INIT_OFFSET_Y	0
# define INC_OFFSET		10
# define INC_ZOOM_Z		1.1
# define MAX_Z_SCALES	50
# define BAR_INFO_H		65
# define MIN_WIDTH		1000
# define MIN_HEIGHT		300

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              HEADERS
*/
# include "libft/includes/get_next_line.h"
# include "libft/includes/ft_printf.h"
# include "libft/includes/libft.h"
# include "mlx.h"
# include "mlx_error.h"
# include <fcntl.h>	// for open
# include <math.h>
# include "controls.h"

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

typedef struct s_line_aux
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		error;	
}	t_line_aux;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}	t_img;

typedef struct s_keys
{
	int		q_press;
	int		w_press;
	int		a_press;
	int		s_press;
	int		z_press;
	int		x_press;
	int		left_press;
	int		right_press;
	int		down_press;
	int		up_press;
	int		i_press;
	int		o_press;
	int		p_press;
	int		bar_press;
	int		mlb_press;
	int		mrb_press;
	int		mwb_press;		
}	t_keys;

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
	float	angle_x;
	float	angle_y;
	float	angle_z;
	float	zoom;
	int		offset_x;
	int		offset_y;
	float	user_scale_z;
	int		num_scales_z;
	int		bar_size;
	t_keys	key;
	t_point	*map;
	t_img	img;	
}	t_fdf;

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                        FUNCTION PROTOTYPES
*/
void	ft_error_handler(int error);
void	free_split(char **str);
void	free_and_exit(int error, char *ptr);
void	free_split_and_exit(char **str, int error, char *ptr);
void	free_map_and_exit(t_fdf *fdf, int error, int flag);

void	mlx_put_pixel(t_fdf *fdf, int x, int y, int color);
void	draw_line(t_line line, t_fdf *fdf);
void	line_direction(t_line *line, t_line_aux *line_aux);
void	print_info(t_fdf *fdf);
void	print_next_line(t_fdf *fdf);

int		mouse_pressed(int button, int x, int y, t_fdf *fdf);
int		mouse_released(int button, int x, int y, t_fdf *fdf);

int		key_pressed(int keycode, t_fdf *fdf);
int		key_pressed_aux(int keycode, t_fdf *fdf);
int		key_released(int keycode, t_fdf *fdf);
int		key_released_aux(int keycode, t_fdf *fdf);
int		close_window(t_fdf *fdf);

void	init_map(char *file, t_fdf *fdf);
void	init_win(t_fdf *fdf, char *s);
void	iso_view(t_fdf *fdf);
void	init_hooks(t_fdf *fdf);

char	*read_map(char *file, t_fdf *fdf);
void	check_map(t_fdf *fdf);
int		count_x_elem(char *line, int jump);
void	parse_map(t_fdf *fdf, char *line);
int		get_hex_color(char *color);

void	key_action_1(t_fdf *fdf);
void	key_action_2(t_fdf *fdf);
void	key_action_3(t_fdf *fdf);
void	mouse_action_1(t_fdf *fdf);
int		main_loop(t_fdf *fdf);

void	projection(t_fdf *fdf);
void	project_x_lines(t_fdf *fdf);
void	project_y_lines(t_fdf *fdf);
void	project_points(t_fdf *fdf);

void	rotate(t_fdf *fdf);
void	unrotate(t_fdf *fdf);
void	rotate_x(t_fdf *fdf, float angle);
void	rotate_y(t_fdf *fdf, float angle);
void	rotate_z(t_fdf *fdf, float angle);

void	z_centering(t_fdf *fdf);
void	modify_height(t_fdf *fdf);
void	recover_height(t_fdf *fdf);

#endif