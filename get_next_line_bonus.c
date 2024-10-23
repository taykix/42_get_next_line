/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayki <tayki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:48:15 by tayki             #+#    #+#             */
/*   Updated: 2024/10/23 20:52:50 by tayki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <string.h>

char	*get_line(t_list *list)
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
		while (*str && i < line_len && *str != '\n')
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
				line_len++;
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

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	write_to_buffer(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = get_line(list);
	clean_line(&list);
	if (next_line == NULL || *next_line == '\0')
	{
		free(next_line);
		return (NULL);
	}
	return (next_line);
}

void	write_to_buffer(t_list **list, int fd)
{
	t_list	*current;
	ssize_t	bytes_read;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return ;
	while (!has_endline(list))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		current = create_node(buffer);
		if (current == NULL)
		{
			free(buffer);
			return ;
		}
		append(list, current);
	}
	free(buffer);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("42_with_nl", O_RDWR);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	close(fd);
// 	printf("\nsize of node%lu\n", sizeof(t_list));
// 	return (0);
// }
