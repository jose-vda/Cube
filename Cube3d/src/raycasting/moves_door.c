/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

int	door_is_open(t_game *game, int my, int mx)
{
	int	i;

	i = 0;
	while (i < game->num_open_doors)
	{
		if (game->open_doors[i].y == my && game->open_doors[i].x == mx)
			return (1);
		i++;
	}
	return (0);
}

int	cell_is_pushed(t_game *game, int my, int mx)
{
	int	i;

	i = 0;
	while (i < game->num_pushed)
	{
		if (game->pushed[i].y == my && game->pushed[i].x == mx)
			return (1);
		i++;
	}
	return (0);
}

void	push_wall_at(t_game *game, int my, int mx)
{
	int	i;

	if (my < 0 || my >= game->map_height || mx < 0 || mx >= game->map_width)
		return ;
	if (mx >= ft_strlen(game->map[my]))
		return ;
	if (game->map[my][mx] != 'P')
		return ;
	i = 0;
	while (i < game->num_pushed)
	{
		if (game->pushed[i].y == my && game->pushed[i].x == mx)
			return ;
		i++;
	}
	if (game->num_pushed < MAX_PUSH_WALLS)
	{
		game->pushed[game->num_pushed].y = my;
		game->pushed[game->num_pushed].x = mx;
		game->num_pushed++;
		game->map[my][mx] = '0';
	}
}

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
