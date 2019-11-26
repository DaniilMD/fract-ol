/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:16:06 by openelop          #+#    #+#             */
/*   Updated: 2019/11/19 18:16:08 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_usage(int button, int x, int y, void *param_void)
{
	t_param		*param;
	t_frac_func	*frc_bldr;

	param = (t_param*)param_void;
	frc_bldr = &param->frac_bldr;
	if (button == 5 || button == 4)
	{
		zoom(button, param_void);
		frc_bldr->move_x += (x - WINDOW_WIDTH / 2) / frc_bldr->zoom_x;
		frc_bldr->move_y += (y - WINDOW_HEIGHT / 2) / frc_bldr->zoom_y;
	}
	if (button == 1)
	{
		param->prev_x = x;
		param->prev_y = y;
		param->mouse_pressed = 1;
	}
	mlx_clear_window(param->mlx_ptr, param->win_ptr);
	render(param_void);
	return (0);
}

int		mouse_released(int button, int x, int y, void *param_void)
{
	t_param *param;

	x++;
	y++;
	param = (t_param*)param_void;
	if (button == 1)
		param->mouse_pressed = 0;
	return (0);
}

int		julia_changer(int x, int y, void *param_void)
{
	t_param *param;

	param = (t_param*)param_void;
	if (param->mouse_pressed == 1)
	{
		param->frac_bldr.move_x -= (x - param->prev_x)
			/ param->frac_bldr.zoom_x;
		param->prev_x = x;
		param->frac_bldr.move_y -= (y - param->prev_y)
			/ param->frac_bldr.zoom_y;
		param->prev_y = y;
		mlx_clear_window(param->mlx_ptr, param->win_ptr);
		render(param_void);
	}
	if (param->type == 1)
	{
		param->frac_bldr.pixel_param.re = param->frac_bldr.win_diff
			* (x - WINDOW_WIDTH / 2) / param->frac_bldr.zoom_x;
		param->frac_bldr.pixel_param.im = (y - WINDOW_HEIGHT / 2)
			/ param->frac_bldr.zoom_y;
		mlx_clear_window(param->mlx_ptr, param->win_ptr);
		render(param_void);
	}
	return (0);
}
