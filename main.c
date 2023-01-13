/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariahi <ariahi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:51:59 by ariahi            #+#    #+#             */
/*   Updated: 2023/01/13 18:53:16 by ariahi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void	leaks()
// {
// 	system ("leaks cub3D");
// }

void	cast_ray(t_data *data)
{
	horizontal_intersection(data);
	vertical_intersection(data);
	distance(data);
}

void	cast_all_rays(t_data *data)
{
	int	i;

	i = 0;
	data->ray->ray_angle = data->player->rotation_agnles - (data->fov / 2);
	while (i < NUM_RAYS)
	{
		ray_init(data->ray, solve_angle(data->ray->ray_angle));
		cast_ray(data);
		generate_3d_projection(data, i);
		data->ray->ray_angle += data->fov / NUM_RAYS;
		i++;
	}
}

int	start_game(t_data *data)
{
	render_back_ground(data);
	cast_all_rays(data);
	move_player(data);
	render_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_input	input;
	t_data	data;
	int		fd;
	// atexit(leaks);
	if (ac != 2)
		return (ft_putendl_fd("Error invalid argument", 2), 1);
	fd = open(av[1], O_RDWR);
	if (fd == -1)
		return (ft_putendl_fd("Error can't open map", 2), 1);
	if (check_map_name(av[1]))
		return (ft_putendl_fd("Error invalid map name", 2), 1);
	init_input(&input);
	if (stock_input(fd, &input))
		return (close(fd), free_input(&input), 1);
	close(fd);
	if (data_init(&data, &input))
		return (free_data(&data), 1);
	mlx_hook(data.win, 02, 1L << 0, &handle_key_press, &data);
	mlx_hook(data.win, 03, 2L << 0, &handle_keyrelease, &data);
	mlx_loop_hook(data.mlx, start_game, &data);
	mlx_loop(data.mlx);
	return (free_data(&data), 0);
}
