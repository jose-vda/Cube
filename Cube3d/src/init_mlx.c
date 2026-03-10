/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:19:24 by jose-vda          #+#    #+#             */
/*   Updated: 2026/02/12 19:57:38 by jose-vda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	init_image(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img.img)
	{
		write(2, "Error: mlx_new_image failed\n", 28);
		exit(EXIT_FAILURE);
	}
	game->img.addr = mlx_get_data_addr(
			game->img.img,
			&game->img.bpp,
			&game->img.line_len,
			&game->img.endian);
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		write(2, "Error: mlx_init failed\n", 23);
		exit(EXIT_FAILURE);
	}
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cube3D");
	if (!game->win)
	{
		write(2, "Error: mlx_new_window failed\n", 29);
		exit(EXIT_FAILURE);
	}
}

void	free_game(t_game *game)
{
	free_map(game);
	free_textures(game);
	free_mlx(game);
}

int	close_window(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

void	fill_board(t_game game, int y, int x)
{
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(&game.img, x, y, 0x003366);
			x++;
		}
		y++;
	}
}