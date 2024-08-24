/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayki <tayki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:19:44 by tayki             #+#    #+#             */
/*   Updated: 2024/08/24 20:12:57 by tayki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	write_to_buffer(list_t **list, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	list_t	*current;
	ssize_t	bytesRead;

	while (!has_endline(list))
	{
		if (buffer == NULL)
			return ;
		bytesRead = read(fd, buffer, BUFFER_SIZE);
		if (!bytesRead)
		{
			return ;
		}
		buffer[bytesRead] = '\0';
		current = create_node(buffer);
		append(list, current);
	}
}

int	has_endline(list_t **list)
{
	list_t	*current;
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

void	append(list_t **list, list_t *new_node)
{
	list_t	*temp;

	if (!list || !new_node)
		return ;
	if (*list == NULL)
		*list = new_node;
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	clean_line(list_t **head)
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
			{
				if_eof = 1;
				str++;
				break ;
			}
			str++;
		}
		if (if_eof != 1)
		{
			temp = *head;
			*head = (*head)->next;
			free(temp->str);
			free(temp);
		}
		else
		{
			if (*str)
			{
				new_head = create_node(str);
				if (new_head == NULL || new_head->str == NULL)
					return ;
				temp = *head;
				new_head->next = (*head)->next;
				*head = new_head;
				free(temp->str);
				free(temp);
				break;
			}
		}
	}
}

list_t	*create_node(char *content)
{
	list_t	*node;

	node = (list_t *)malloc(sizeof(list_t));
	if (!node)
		return (NULL);
	node->str = ft_strdup(content);
	if (!(node->str))
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

void	clean_list(list_t **list)
{
	list_t	*temp;
	list_t	*next;

	if (!list || !*list)
		return ;
	temp = *list;
	while (temp)
	{
		next = temp->next;
		free(temp->str);
		free(temp);
		temp = next;
	}
	*list = NULL;
}

char	*ft_strdup(const char *s)
{
	size_t	len_s;
	char	*arr;
	char	*ptr;

	len_s = ft_strlen(s);
	arr = malloc((len_s + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	ptr = arr;
	while (*s)
	{
		*arr++ = *s++;
	}
	*arr = '\0';
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
