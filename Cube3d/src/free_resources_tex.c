/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources_tex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	free_tex_array(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 6)
	{
		if (game->tex_path[i])
		{
			free(game->tex_path[i]);
			game->tex_path[i] = NULL;
		}
		j = 0;
		while (j < i && game->tex[j].img != game->tex[i].img)
			j++;
		if (j >= i && game->tex[i].img && game->mlx)
		{
			mlx_destroy_image(game->mlx, game->tex[i].img);
			game->tex[i].img = NULL;
		}
		else
			game->tex[i].img = NULL;
		i++;
	}
}

static void	free_ceiling_and_img(t_game *game)
{
	if (game->has_ceiling_tex && game->ceiling_tex.img && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->ceiling_tex.img);
		game->ceiling_tex.img = NULL;
	}
	else
		game->ceiling_tex.img = NULL;
	if (game->img.img && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->img.img);
		game->img.img = NULL;
	}
}

static void	free_floor_textures(t_game *game)
{
	if (game->floor_tex.img && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->floor_tex.img);
		game->floor_tex.img = NULL;
	}
	if (game->floor_tex_sunny.img && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->floor_tex_sunny.img);
		game->floor_tex_sunny.img = NULL;
	}
	if (game->ceiling_tex_path)
	{
		free(game->ceiling_tex_path);
		game->ceiling_tex_path = NULL;
	}
}

static void	free_extra_textures(t_game *game)
{
	free_ceiling_and_img(game);
	free_floor_textures(game);
}

void	free_textures(t_game *game)
{
	free_tex_array(game);
	free_extra_textures(game);
}
