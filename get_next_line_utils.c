/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayki <tayki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:19:44 by tayki             #+#    #+#             */
/*   Updated: 2024/08/22 17:13:34 by tayki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	write_to_buffer(list_t *list, int fd)
{
	char	*buffer;
	ssize_t	bytesRead;

	while (!has_endline(list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return ;
		bytesRead = read(fd, buffer, BUFFER_SIZE);
		if (!bytesRead)
		{
			free(buffer);
			return ;
		}
		buffer[bytesRead] = '\0';
		append(list, buffer);
	}
}

int	has_endline(list_t *list)
{
	list_t	*current;
	char	*str;

	current = list;
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

void append(list_t * head, char * str) {
    list_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (list_t *) malloc(sizeof(list_t));
	if (current->next == NULL)
		return;
    current->next->str = str;
    current->next->next = NULL;
}
