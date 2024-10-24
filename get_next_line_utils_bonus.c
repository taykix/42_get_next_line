/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:19:44 by tayki             #+#    #+#             */
/*   Updated: 2024/10/24 19:37:37 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		new_node->prev = temp;
	}
}

void	clean_line(t_list **head, int fd)
{
	t_list	*temp;
	t_list	*current;
	char	*str;

	current = *head;
	while (current)
	{
		str = current->str;
		if (current->fd == fd)
		{
			while (*str && *str != '\n')
				str++;
			if (*str == '\n' && *++str != '\0')
			{
				temp = create_node(str, fd);
				temp->next = current->next;
				if (current->prev)
				{
					temp->prev = current->prev;
					current->prev->next = temp;
				}
				else
					*head = temp;
				free(current->str);
				free(current);
				break ;
			}
			temp = current->next;
			if (current->prev)
				current->prev->next = temp;
			else
				*head = temp;
			if (temp)
				temp->prev = current->prev;
			free(current->str);
			free(current);
			current = temp;
		}
		else
			current = current->next;
	}
}

t_list	*create_node(char *content, int fd)
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
	node->prev = NULL;
	node->fd = fd;
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
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	len_s = i;
	arr = malloc((len_s + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
