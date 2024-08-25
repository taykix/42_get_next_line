/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayki <tayki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:48:15 by tayki             #+#    #+#             */
/*   Updated: 2024/08/25 22:39:03 by tayki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		while (*str && i < line_len + 1 && *str != '\n')
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
				line_len += 2;
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
	return (next_line);
}

void	write_to_buffer(t_list **list, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	t_list	*current;
	ssize_t	bytes_read;

	while (!has_endline(list))
	{
		if (buffer == NULL)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read)
		{
			return ;
		}
		buffer[bytes_read] = '\0';
		current = create_node(buffer);
		append(list, current);
	}
}
/*
int	main(void)
{
	int		fd;
	int		fda;
	char	*line;

	fd = open("test.txt", O_RDONLY | O_CREAT);
	fda = open("test1.txt", O_RDONLY | O_CREAT);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%s\n", line);
		free(line);
		line = get_next_line(fda);
		if (line == NULL)
			break ;
		printf("%s\n", line);
		free(line);
	}
	printf("Buffer size %d\n", BUFFER_SIZE);
	close(fd);
	return (0);
}
*/
