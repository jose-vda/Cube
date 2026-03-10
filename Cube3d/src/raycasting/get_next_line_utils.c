/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:45:26 by jose-vda          #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static size_t	gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static void	copy_from_output(char *newline, char *output_line, size_t *i)
{
	size_t	j;

	j = 0;
	while (output_line && output_line[j])
	{
		newline[*i] = output_line[j];
		(*i)++;
		j++;
	}
}

static void	copy_from_buf_until_newline(char *newline, char *buffer, size_t *i)
{
	size_t	j;

	j = 0;
	while (buffer[j] && buffer[j] != '\n')
		newline[(*i)++] = buffer[j++];
	if (buffer[j] == '\n')
		newline[(*i)++] = '\n';
	newline[*i] = '\0';
}

char	*copy_to_line(char *output_line, char *buffer)
{
	char	*newline;
	size_t	i;

	newline = malloc(gnl_strlen(output_line) + gnl_strlen(buffer) + 1);
	if (!newline)
	{
		free(output_line);
		return (NULL);
	}
	i = 0;
	copy_from_output(newline, output_line, &i);
	copy_from_buf_until_newline(newline, buffer, &i);
	free(output_line);
	return (newline);
}
