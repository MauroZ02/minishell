/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzangaro <mzangaro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:24:55 by mzangaro          #+#    #+#             */
/*   Updated: 2025/11/20 17:39:48 by mzangaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *line, t_labels type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = ft_strdup(line);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

/* Adds a token to the end of the list and handles the 'head' internally. */
int	token_add_back(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return (0);
	if (*head == NULL)
	{
		*head = new_token;
		return (1);
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_token;
	return (1);
}

/* Frees the entire list in case of error */
void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->value)
			free(head->value);
		free(head);
		head = tmp;
	}
}
