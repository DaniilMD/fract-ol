/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:45:54 by openelop          #+#    #+#             */
/*   Updated: 2019/11/16 15:45:56 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	close_window(void *param_void)
{
	t_param *param;

	param = (t_param*)param_void;
	mlx_destroy_image(param->mlx_ptr, param->img_ptr);
	mlx_clear_window(param->mlx_ptr, param->win_ptr);
	(void)param;
	exit(0);
}

void	shift_location(int keycode, void *param_void)
{
	t_param *param;

	param = (t_param*)param_void;
	if (keycode == 123)
		param->frac_bldr.move_x += 100 / param->frac_bldr.zoom_x;
	if (keycode == 124)
		param->frac_bldr.move_x -= 100 / param->frac_bldr.zoom_x;
	if (keycode == 125)
		param->frac_bldr.move_y -= 100 / param->frac_bldr.zoom_y;
	if (keycode == 126)
		param->frac_bldr.move_y += 100 / param->frac_bldr.zoom_y;
}

void	zoom(int keycode, void *param_void)
{
	t_param *param;

	param = (t_param*)param_void;
	if (keycode == 27 || keycode == 5)
	{
		param->frac_bldr.zoom_x /= 1.5;
		param->frac_bldr.zoom_y /= 1.5;
	}
	if (keycode == 24 || keycode == 4)
	{
		param->frac_bldr.zoom_x *= 1.5;
		param->frac_bldr.zoom_y *= 1.5;
	}
}

void	colour_changer(int keycode, void *param_void)
{
	t_param *param;

	param = (t_param*)param_void;
	if (keycode == 18)
	{
		param->frac_bldr.red = 50;
		param->frac_bldr.green = 50;
	}
	else if (keycode == 19)
	{
		param->frac_bldr.red = 250;
		param->frac_bldr.green = 10;
		param->frac_bldr.blue = 135;
	}
	else if (keycode == 20)
	{
		param->frac_bldr.red = 40;
		param->frac_bldr.blue = 250;
	}
	else if (keycode == 15)
		param->frac_bldr.red += 8;
	else if (keycode == 5)
		param->frac_bldr.green += 8;
	else if (keycode == 11)
		param->frac_bldr.blue += 8;
}

int		key_press_down(int keycode, void *param_void)
{
	t_param			*param;

	param = (t_param *)param_void;
	if (keycode == 53)
		close_window(param_void);
	if (keycode == 124 || keycode == 123 || keycode == 126 || keycode == 125)
		shift_location(keycode, param_void);
	if (keycode == 27 || keycode == 24)
		zoom(keycode, param_void);
	if ((keycode >= 18 && keycode <= 23) || (keycode == 15)
		|| (keycode == 5) || (keycode == 11))
		colour_changer(keycode, param_void);
	if (keycode == 49)
	{
		if (param->type == 1)
			param->frac_bldr.move_x = 0;
		else
			param->frac_bldr.move_x = -0.5;
		param->frac_bldr.move_y = 0;
		param->frac_bldr.zoom_x = (0.5 * WINDOW_WIDTH) * 0.5;
		param->frac_bldr.zoom_y = (0.5 * WINDOW_HEIGHT) * 0.5;
	}
	mlx_clear_window(param->mlx_ptr, param->win_ptr);
	render(param_void);
	return (0);
}
