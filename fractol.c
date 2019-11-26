/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:28:08 by openelop          #+#    #+#             */
/*   Updated: 2019/11/08 17:28:10 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	render(t_param *param)
{
	int				i;
	t_for_threads	wtf[THREADS_NUM];
	pthread_t		threads[THREADS_NUM];

	i = 0;
	while (i < THREADS_NUM)
	{
		wtf[i].param = *param;
		wtf[i].thread_num = i;
		i++;
	}
	i = 0;
	while (i < THREADS_NUM)
	{
		pthread_create(&(threads[i]), NULL, fractal_drawer, &wtf[i]);
		i++;
	}
	i = 0;
	while (i < THREADS_NUM)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr,
		param->img_ptr, 0, 0);
}

int		main(int argc, char **argv)
{
	t_param			param;

	if (argc != 2 || (ft_strcmp(argv[1], "1") && ft_strcmp(argv[1], "2") != 0
		&& ft_strcmp(argv[1], "3") != 0))
	{
		ft_putstr("usage: ./fractol <fractol number>:\n\
	1) Julia\n\t2) Mandelbrot\n\t3) Burningship\n");
		return (0);
	}
	param.type = argv[1][0] - 48;
	param.mlx_ptr = mlx_init();
	param.win_ptr = mlx_new_window(param.mlx_ptr,
		WINDOW_WIDTH, WINDOW_HEIGHT, "Eto moe okno");
	param.img_ptr = mlx_new_image(param.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	param.mlx_data_addr = mlx_get_data_addr(param.img_ptr,
		&param.bpp, &param.size_line, &param.endian);
	set_start_nums(&param);
	render(&param);
	mlx_hook(param.win_ptr, 2, 2, &key_press_down, (void*)&param);
	mlx_hook(param.win_ptr, 4, 2, &mouse_usage, (void*)&param);
	mlx_hook(param.win_ptr, 5, 2, &mouse_released, (void*)&param);
	mlx_hook(param.win_ptr, 6, 2, &julia_changer, (void*)&param);
	mlx_loop(param.mlx_ptr);
	return (0);
}
