/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:58:17 by jose-vda          #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	load_texture(t_game *game, int i, char *path)
{
	game->tex[i].img = mlx_xpm_file_to_image(game->mlx, path, &game->tex[i].width,
			&game->tex[i].height);
	if (!game->tex[i].img)
	{
		write(2, "Error\nFailed to load texture\n", 30);
		free_game(game);
		exit(1);
	}
	game->tex[i].addr = (int *)mlx_get_data_addr(game->tex[i].img,
			&game->tex[i].bpp, &game->tex[i].line_len, &game->tex[i].endian);
}

static void	load_wall_textures(t_game *game)
{
	load_texture(game, TEX_NORTH, game->tex_path[TEX_NORTH]);
	load_texture(game, TEX_SOUTH, game->tex_path[TEX_SOUTH]);
	load_texture(game, TEX_EAST, game->tex_path[TEX_EAST]);
	load_texture(game, TEX_WEST, game->tex_path[TEX_WEST]);
	if (game->tex_path[TEX_WALL2])
		load_texture(game, TEX_WALL2, game->tex_path[TEX_WALL2]);
	else
		load_texture(game, TEX_WALL2, game->tex_path[TEX_NORTH]);
	if (game->tex_path[TEX_WALL3])
		load_texture(game, TEX_WALL3, game->tex_path[TEX_WALL3]);
	else
		load_texture(game, TEX_WALL3, game->tex_path[TEX_NORTH]);
}

static void	load_floor_textures(t_game *game)
{
	game->floor_tex.img = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm",
			&game->floor_tex.width, &game->floor_tex.height);
	if (!game->floor_tex.img)
	{
		write(2, "Error\nFailed to load floor texture (textures/floor.xpm)\n", 54);
		free_game(game);
		exit(1);
	}
	game->floor_tex.addr = (int *)mlx_get_data_addr(game->floor_tex.img,
			&game->floor_tex.bpp, &game->floor_tex.line_len, &game->floor_tex.endian);
	game->floor_tex_sunny.img = mlx_xpm_file_to_image(game->mlx, "textures/floor_sunny.xpm",
			&game->floor_tex_sunny.width, &game->floor_tex_sunny.height);
	if (!game->floor_tex_sunny.img)
	{
		write(2, "Error\nFailed to load floor_sunny texture (textures/floor_sunny.xpm)\n", 65);
		free_game(game);
		exit(1);
	}
	game->floor_tex_sunny.addr = (int *)mlx_get_data_addr(game->floor_tex_sunny.img,
			&game->floor_tex_sunny.bpp, &game->floor_tex_sunny.line_len, &game->floor_tex_sunny.endian);
}

static void	load_ceiling_texture(t_game *game)
{
	if (game->ceiling_tex_path)
	{
		game->ceiling_tex.img = mlx_xpm_file_to_image(game->mlx, game->ceiling_tex_path,
				&game->ceiling_tex.width, &game->ceiling_tex.height);
		if (!game->ceiling_tex.img)
		{
			write(2, "Error\nFailed to load ceiling texture\n", 37);
			free_game(game);
			exit(1);
		}
		game->ceiling_tex.addr = (int *)mlx_get_data_addr(game->ceiling_tex.img,
				&game->ceiling_tex.bpp, &game->ceiling_tex.line_len, &game->ceiling_tex.endian);
		game->has_ceiling_tex = 1;
	}
	else
	{
		game->has_ceiling_tex = 0;
		game->ceiling_tex.img = NULL;
	}
}

void	load_textures(t_game *game)
{
	load_wall_textures(game);
	load_floor_textures(game);
	load_ceiling_texture(game);
}
