/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_drawer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:23:50 by openelop          #+#    #+#             */
/*   Updated: 2019/11/16 14:23:54 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_start_nums(t_param *param)
{
	param->frac_bldr.win_diff = ((double)WINDOW_WIDTH
		/ (double)WINDOW_HEIGHT) * 1.05;
	param->frac_bldr.zoom_x = (0.5 * WINDOW_WIDTH) * 0.5;
	param->frac_bldr.zoom_y = (0.5 * WINDOW_HEIGHT) * 0.5;
	param->frac_bldr.move_x = 0;
	param->frac_bldr.move_y = 0;
	param->frac_bldr.red = 100;
	param->frac_bldr.green = 30;
	param->frac_bldr.blue = 175;
	if (param->type == 1)
	{
		param->frac_bldr.pixel_param.re = -0.7;
		param->frac_bldr.pixel_param.im = 0.27015;
	}
	else if (param->type == 2)
		param->frac_bldr.move_x = -0.5;
	else if (param->type == 3)
	{
		param->frac_bldr.move_y = -0.5;
		param->frac_bldr.move_x = -0.5;
	}
}

void	pixel_cords_counter(t_param *param, int x, int y)
{
	t_frac_func	fr_bldr;

	fr_bldr = param->frac_bldr;
	if (param->type == 1)
	{
		param->frac_bldr.new_pixel.re = fr_bldr.win_diff * (x
			- WINDOW_WIDTH / 2) / fr_bldr.zoom_x + fr_bldr.move_x;
		param->frac_bldr.new_pixel.im = (y - WINDOW_HEIGHT / 2)
			/ fr_bldr.zoom_y + fr_bldr.move_y;
	}
	else if (param->type == 2 || param->type == 3)
	{
		param->frac_bldr.pixel_param.re = fr_bldr.win_diff * (x -
			WINDOW_WIDTH / 2) / fr_bldr.zoom_x + fr_bldr.move_x;
		param->frac_bldr.pixel_param.im = (y - WINDOW_HEIGHT / 2)
		/ fr_bldr.zoom_y + fr_bldr.move_y;
		param->frac_bldr.new_pixel.re = 0;
		param->frac_bldr.new_pixel.im = 0;
	}
}

int		iteration_point_counter(t_param *param)
{
	int			i;
	t_complex	temp;
	t_complex	frac_z;

	frac_z = param->frac_bldr.new_pixel;
	i = 0;
	while (i < MAX_ITERS
		&& (frac_z.re * frac_z.re + frac_z.im * frac_z.im <= 4))
	{
		if (param->type == 3)
		{
			frac_z.re = fabs(frac_z.re);
			frac_z.im = fabs(frac_z.im);
		}
		temp.re = frac_z.re * frac_z.re - frac_z.im
			* frac_z.im + param->frac_bldr.pixel_param.re;
		temp.im = 2 * frac_z.re * frac_z.im + param->frac_bldr.pixel_param.im;
		if (fabs(frac_z.re - temp.re) < 0.00000001
			&& fabs(frac_z.im - temp.im) < 0.00000001)
			i = MAX_ITERS - 1;
		frac_z.re = temp.re;
		frac_z.im = temp.im;
		i++;
	}
	return (i);
}

void	pixel_putter_with_colour(t_param *param, int x, int y, int i)
{
	int			im_count;
	t_complex	frac_z;
	t_complex	frac_c;

	frac_z = param->frac_bldr.new_pixel;
	frac_c = param->frac_bldr.pixel_param;
	if (i == MAX_ITERS)
	{
		im_count = x * (param->bpp) / 8 + y * (param->size_line);
		param->mlx_data_addr[im_count] = 0;
		param->mlx_data_addr[im_count + 1] = 0;
		param->mlx_data_addr[im_count + 2] = 0;
	}
	else
	{
		im_count = x * (param->bpp) / 8 + y * (param->size_line);
		param->mlx_data_addr[im_count] = (param->frac_bldr.blue + i) % 256;
		param->mlx_data_addr[im_count + 1] = (param->frac_bldr.green + i) % 256;
		param->mlx_data_addr[im_count + 2] =
			(param->frac_bldr.red + (int)log(i)) % 256;
	}
}

void	*fractal_drawer(void *thr_param_void)
{
	int				x;
	int				y;
	int				i;
	t_for_threads	*thr_param;

	thr_param = (t_for_threads *)thr_param_void;
	y = thr_param->thread_num * (WINDOW_HEIGHT / THREADS_NUM);
	while (y < (thr_param->thread_num + 1) * (WINDOW_HEIGHT / THREADS_NUM))
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_cords_counter(&(thr_param->param), x, y);
			i = iteration_point_counter(&(thr_param->param));
			pixel_putter_with_colour(&(thr_param->param), x, y, i);
			x++;
		}
		y++;
	}
	return (NULL);
}
