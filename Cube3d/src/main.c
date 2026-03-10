/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:58:17 by jose-vda          #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	initialize(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img.img = NULL;
	game->player.rot_speed = 0.05;
	game->player.move_speed = 0.08;
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->show_minimap = 1;
	game->mouse_last_x = -1;
	game->num_open_doors = 0;
	game->theme_sunny = 0;
	game->map_name = NULL;
	game->has_key = 0;
	game->paused = 0;
	game->num_pushed = 0;
	game->exit_reached = 0;
	game->damage_flash = 0;
	game->pickup_flash = 0;
}

int	game_loop(t_game *game)
{
	update_player(game);
	render(game);
	return (0);
}

static int	main_parse_and_init(t_game *game, char *filename)
{
	if (!parse_map(game, filename))
		return (0);
	game->map_name = ft_strdup(filename);
	if (!game->map_name)
		return (0);
	return (1);
}

static void	main_hooks_and_loop(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 6, 0, mouse_move, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error\nUsage: ./cube3d map.cub\n");
		return (1);
	}
	initialize(&game);
	if (!main_parse_and_init(&game, argv[1]))
		return (1);
	init_mlx(&game);
	load_textures(&game);
	init_image(&game);
	main_hooks_and_loop(&game);
	return (0);
}
