/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:45:26 by jose-vda          #+#    #+#             */
/*   Updated: 2026/02/12 19:07:49 by jose-vda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

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

void	remaining_buffer(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
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

int	new_line(char *output_line)
{
	int	i;

	if (!output_line)
		return (0);
	i = 0;
	while (output_line[i])
	{
		if (output_line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*output_line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	output_line = NULL;
	while (!new_line(output_line))
	{
		if (buffer[0] == '\0')
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
				break ;
			buffer[bytes_read] = '\0';
		}
		output_line = copy_to_line(output_line, buffer);
		remaining_buffer(buffer);
		if (!output_line)
			return (NULL);
	}
	return (output_line);
}