/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayki <tayki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:19:44 by tayki             #+#    #+#             */
/*   Updated: 2024/08/25 15:28:08 by tayki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	append(t_list **list, t_list *new_node)
{
	t_list	*temp;

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

void	clean_line(t_list **head)
{
	t_list	*new_head;
	t_list	*temp;
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
			new_head = create_node(str);
			if (new_head == NULL || new_head->str == NULL)
				return ;
			temp = *head;
			new_head->next = (*head)->next;
			*head = new_head;
			free(temp->str);
			free(temp);
			break ;
		}
	}
}

t_list	*create_node(char *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
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

void	clean_list(t_list **list)
{
	t_list	*temp;
	t_list	*next;

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
