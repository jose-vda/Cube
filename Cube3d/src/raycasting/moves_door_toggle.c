/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_door_toggle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static int	remove_door_at(t_game *game, int my, int mx)
{
	int	i;

	i = 0;
	while (i < game->num_open_doors)
	{
		if (game->open_doors[i].y == my && game->open_doors[i].x == mx)
		{
			game->open_doors[i] = game->open_doors[game->num_open_doors - 1];
			game->num_open_doors--;
			return (1);
		}
		i++;
	}
	return (0);
}

static void	add_door_at(t_game *game, int my, int mx)
{
	if (game->num_open_doors < MAX_DOORS)
	{
		game->open_doors[game->num_open_doors].y = my;
		game->open_doors[game->num_open_doors].x = mx;
		game->num_open_doors++;
	}
}

void	toggle_door_at(t_game *game, int my, int mx)
{
	if (my < 0 || my >= game->map_height || mx < 0 || mx >= game->map_width)
		return ;
	if (mx >= ft_strlen(game->map[my]))
		return ;
	if (game->map[my][mx] != 'D')
		return ;
	if (remove_door_at(game, my, mx))
		return ;
	add_door_at(game, my, mx);
}
