/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:19:44 by tayki             #+#    #+#             */
/*   Updated: 2024/08/26 15:36:15 by tkarakay         ###   ########.fr       */
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
	}
}

void	clean_line(t_list **head)
{
	t_list	*new_head;
	t_list	*temp;
	char	*str;

	while ((*head))
	{
		str = (*head)->str;
		while (*str && *str != '\n')
			str++;
		if (*str == '\n')
		{
			new_head = create_node(++str);
			if (!new_head || !(new_head->str))
				return ;
			new_head->next = (*head)->next;
			free((*head)->str);
			free(*head);
			*head = new_head;
			break ;
		}
		temp = *head;
		*head = (*head)->next;
		free(temp->str);
		free(temp);
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
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	len_s = i;
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
