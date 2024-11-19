/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:48:15 by tayki             #+#    #+#             */
/*   Updated: 2024/11/19 17:52:30 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_the_line(t_list *list)
{
	int		line_len;
	char	*line;
	char	*str;
	int		i;

	if (list == NULL)
		return (NULL);
	line_len = count_line(list);
	line = malloc(line_len + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (list != NULL)
	{
		str = list->str;
		while (*str && i < line_len + 1 && *str != '\n')
			line[i++] = *str++;
		if (*str == '\n')
			line[i++] = *str++;
		line[i] = '\0';
		list = list->next;
	}
	return (line);
}

int	count_line(t_list *list)
{
	int		line_len;
	char	*str;

	line_len = 0;
	while (list != NULL)
	{
		str = list->str;
		while (*str)
		{
			if (*str != '\n')
				line_len++;
			else
			{
				line_len ++;
				break ;
			}
			str++;
		}
		list = list->next;
	}
	return (line_len);
}

int	has_endline(t_list **list)
{
	t_list	*current;
	char	*str;

	current = *list;
	while (current != NULL)
	{
		str = current->str;
		while (*str)
		{
			if (*str == '\n')
				return (1);
			str++;
		}
		current = current->next;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*next_line;
	int				status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	status = write_to_buffer(&list, fd);
	if (status == -1)
		return (NULL);
	if (status == 0 && list == NULL)
		return (NULL);
	next_line = get_the_line(list);
	clean_line(&list);
	if (next_line == NULL || *next_line == '\0')
	{
		free(next_line);
		return (NULL);
	}
	return (next_line);
}

int	write_to_buffer(t_list **list, int fd)
{
	char	*buffer;
	ssize_t	bytes_read;
	t_list	*current;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes_read = 1;
	while (!has_endline(list) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			current = create_node(buffer);
			if (!current)
				bytes_read = -1;
			else
				append(list, current);
		}
	}
	free(buffer);
	if (bytes_read < 0)
		clean_list(list);
	return (bytes_read);
}

int	main(void)
{
	int		fd;
	int		fda;
	char	*line;

	fd = open("multiple_nl.txt", O_RDONLY | O_CREAT);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
