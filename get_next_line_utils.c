/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:19:44 by tayki             #+#    #+#             */
/*   Updated: 2024/08/23 16:40:49 by tkarakay         ###   ########.fr       */
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
		append(&list, buffer);
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

void	append(list_t **head, char *str)
{
	list_t	*new_node;
	list_t	*current;

	new_node = (list_t *)malloc(sizeof(list_t));
	if (new_node == NULL)
		return ;
	new_node->str = str;
	if (new_node->str == NULL)
	{
		free(new_node);
		return ;
	}
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}

void	clean_list(list_t **head)
{
	list_t	*new_head;
	list_t	*temp;
	char	*str;
	int		if_eof;

	if_eof = 0;
	while ((*head) != NULL)
	{
		str = (*head)->str;
		while (*str)
		{
			if (*str == '\n')
				if_eof = 1;
			str++;
		}
		if (if_eof != 1)
		{
			temp = (*head)->next;
			free((*head)->str);
			free((*head));
			(*head) = temp;
		}
		else
		{
			if (*str)
			{
				new_head = malloc(sizeof(list_t));
				new_head->str = malloc(BUFFER_SIZE + 1);
				if (new_head == NULL || new_head->str == NULL)
					return ;
				new_head->str = str;
				new_head->next = (*head);
			}
		}
	}
}
