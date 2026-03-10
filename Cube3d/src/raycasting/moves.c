/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:53:02 by josevictord       #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	apply_mouse_rotation(t_game *game, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(rot)
		- game->player.dir_y * sin(rot);
	game->player.dir_y = old_dir_x * sin(rot)
		+ game->player.dir_y * cos(rot);
	game->player.plane_x = game->player.plane_x * cos(rot)
		- game->player.plane_y * sin(rot);
	game->player.plane_y = old_plane_x * sin(rot)
		+ game->player.plane_y * cos(rot);
}

int	mouse_move(int x, int y, void *param)
{
	t_game	*game;
	int		delta;
	double	rot;

	(void)y;
	game = (t_game *)param;
	if (game->mouse_last_x < 0)
	{
		game->mouse_last_x = x;
		return (0);
	}
	delta = x - game->mouse_last_x;
	game->mouse_last_x = x;
	rot = delta * MOUSE_SENS;
	if (rot != 0)
		apply_mouse_rotation(game, rot);
	return (0);
}
