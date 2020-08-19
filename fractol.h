#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <mlx.h>
# include <math.h>
# include <pthread.h>

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 700
# define MAX_ITERS 200
# define THREADS_NUM 10

typedef struct	s_complex
{
	double		re;
	double		im;
}				t_complex;

typedef struct	s_frac_func
{
	double		zoom_x;
	double		zoom_y;
	double		move_x;
	double		move_y;
	int			red;
	int			green;
	int			blue;
	double		win_diff;
	t_complex	new_pixel;
	t_complex	pixel_param;
}				t_frac_func;

typedef struct	s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*mlx_data_addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			type;
	int			prev_x;
	int			prev_y;
	int			mouse_pressed;
	t_frac_func frac_bldr;
}				t_param;

typedef struct	s_for_threads
{
	t_param		param;
	int			thread_num;
	int			*iters;
}				t_for_threads;

/*
** transformations.c
*/

void			close_window(void *param_void);
int				key_press_down(int keycode, void *param_void);
void			shift_location(int keycode, void *param_void);
void			zoom(int keycode, void *param_void);
void			colour_changer(int keycode, void *param_void);

/*
** fractal_drawer.c
*/

void			set_start_nums(t_param *param);
void			pixel_cords_counter(t_param *param, int x, int y);
int				iteration_point_counter(t_param *param);
void			pixel_putter_with_colour(t_param *param, int x, int y, int i);
void			*fractal_drawer(void *thr_param_void);

/*
** fractol.c
*/

void			render(t_param *param);

/*
** mouse_work.c
*/

int				mouse_usage(int button, int x, int y, void *param_void);
int				julia_changer(int x, int y, void *param_void);
int				mouse_released(int button, int x, int y, void *param_void);

#endif
