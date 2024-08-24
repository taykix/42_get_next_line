/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayki <tayki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:48:15 by tayki             #+#    #+#             */
/*   Updated: 2024/08/24 22:17:25 by tayki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(list_t *list)
{
	int		line_len;
	char	*line;
	char	*str;
	int i;

	if (list == NULL)
		return NULL;
	line_len = count_line(list);
	line = malloc(line_len + 1);
	if (line == NULL)
		return NULL;
	i = 0;
	while (list != NULL)
	{
		str = list->str;
		while (*str && i < line_len + 1)
		{
			if (*str != '\n')
				line[i] = *str++;
			else
			{
				line[i] = *str++;
				break ;
			}
			i++;
		}
		line[i] = '\0';
		list = list->next;
	}
	return (line);
}

int	count_line(list_t *list)
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

char	*get_next_line(int fd)
{
	static list_t	*list;
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

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY | O_CREAT);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%s", line);
	}
	return (0);
}
