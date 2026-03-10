/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:41:24 by jose-vda          #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	draw_hud(t_game *game)
{
	if (game->paused || game->exit_reached)
		return ;
	if (game->map_name)
		mlx_string_put(game->mlx, game->win, 10, 10, HUD_COLOR, game->map_name);
	mlx_string_put(game->mlx, game->win, 10, 28, HUD_COLOR,
		game->has_key ? "Key: Yes" : "Key: No");
	mlx_string_put(game->mlx, game->win, 10, 46, HUD_COLOR,
		"Objective: Find the exit");
}

void	draw_pause_overlay(t_game *game)
{
	(void)game;
}

static void	render_overlay(t_game *game)
{
	if (game->exit_reached)
		mlx_string_put(game->mlx, game->win, WIDTH / 2 - 40, HEIGHT / 2 - 10,
			HUD_COLOR, "You Win!");
	else if (game->paused)
	{
		mlx_string_put(game->mlx, game->win, WIDTH / 2 - 40, HEIGHT / 2 - 20,
			HUD_COLOR, "PAUSED");
		mlx_string_put(game->mlx, game->win, WIDTH / 2 - 80, HEIGHT / 2 + 0,
			HUD_COLOR, "P - Resume  ESC - Quit");
	}
	else
		draw_hud(game);
}

int	render(t_game *game)
{
	ft_bzero(game->img.addr, (size_t)HEIGHT * game->img.line_len);
	raycasting(game);
	draw_minimap(game);
	apply_screen_effects(game);
	draw_crosshair(game);
	if (game->paused)
		draw_rect(&game->img, 0, 0, WIDTH, HEIGHT,
			(100 << 16) | (100 << 8) | 100);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	render_overlay(game);
	return (0);
}
