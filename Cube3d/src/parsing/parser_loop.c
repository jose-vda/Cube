/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	init_parse_state(t_game *game, int *got)
{
	game->tex_path[0] = NULL;
	game->tex_path[1] = NULL;
	game->tex_path[2] = NULL;
	game->tex_path[3] = NULL;
	game->tex_path[4] = NULL;
	game->tex_path[5] = NULL;
	game->ceiling_tex_path = NULL;
	game->floor_color = -1;
	game->ceiling_color = -1;
	got[0] = 0;
	got[1] = 0;
	got[2] = 0;
	got[3] = 0;
	got[4] = 0;
	got[5] = 0;
}

int	read_file_loop(int fd, t_game *game, int *got,
		char **map_lines, int *map_count)
{
	char	*line;
	int		phase;
	int		status;

	phase = 0;
	*map_count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		status = process_read_line(&phase, game, line, got,
				map_lines, map_count);
		if (status == 0)
			return (0);
		if (status == 2)
			break ;
	}
	return (1);
}
