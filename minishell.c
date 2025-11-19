/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzangaro <mzangaro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:24:52 by mzangaro          #+#    #+#             */
/*   Updated: 2025/11/19 21:00:49 by mzangaro         ###   ########.fr       */
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

int	handle_quotes(char *line, int *i, t_token **head)
{
	int			start;
	char		quote_type;
	char		*sub;
	t_labels	type;
	t_token		*token;

	quote_type = line[*i];
	start = *i + 1;
	(*i)++;
	if (quote_type == '"')
		type = TOKEN_QUOTES;
	else
		type = TOKEN_SING_Q;
	while (line[*i] && line[*i] != quote_type)
		(*i)++;
	if (!line[*i])
	{
		printf("Minishell: syntax error: unclosed quotes\n");
		return (0);
	}
	sub = ft_substr(line, start, *i - start);
	if (!sub)
		return (0);
	if (line[*i])
		(*i)++;
	token = new_token(sub, type);
	free (sub);
	return (token_add_back(head, token));
}

int	handle_redirections(char *line, int *i, t_token **head)
{
	int			len;
	char		*sub;
	t_labels	type;
	t_token		*token;

	len = 1;
	if (line[*i] == '<')
	{
		if (line[*i + 1] == '<')
			type = TOKEN_HEREDOC;
		else
			type = TOKEN_IN_REDIR;
	}
	else
	{
		if (line[*i + 1] == '>')
			type = TOKEN_APPEND;
		else
			type = TOKEN_OUT_REDIR;
	}
	if (type == TOKEN_HEREDOC || type == TOKEN_APPEND)
		len = 2;
	sub = ft_substr(line, *i, len);
	if (!sub)
		return (0);
	*i = *i + len;
	token = new_token(sub, type);
	free(sub);
	return (token_add_back(head, token));
}

int	handle_word(char *line, int *i, t_token **head)
{
	int			start;
	char		*sub;
	t_token		*token;

	start = *i;
	while (line[*i] && !ft_strchr(" \t\n|<>'\"", line[*i]))
		(*i)++;
	sub = ft_substr(line, start, *i - start);
	if (!sub)
		return (0);
	token = new_token(sub, TOKEN_WORD);
	free(sub);
	return (token_add_back(head, token));
}

/* Decides which handler to call based on the character */
int	token_handler(char *line, int *i, t_token **head)
{
	if (line[*i] == '"' || line[*i] == '\'')
		return (handle_quotes(line, i, head));
	else if (line[*i] == '<' || line[*i] == '>')
		return (handle_redirections(line, i, head));
	else if (line[*i] == '|')
	{
		(*i)++;
		return (token_add_back(head, new_token("|", TOKEN_PIPE)));
	}
	else
		return (handle_word(line, i, head));
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

t_token	*lexer(char *line)
{
	int		i;
	int		status;
	t_token	*head;

	head = NULL;
	i = 0;
	status = 1;
	while (line[i] && status)
	{
		if ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
		else
			status = token_handler(line, &i, &head);
	}
	if (status == 0)
	{
		free_token_list(head);
		return (NULL);
	}
	return (head);
}

/* ^C handler */
void	sigint_handler(int sig_num)
{
	(void)sig_num;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* ONCE CHILD PROCESSES DONE COME BACK TO HANDLE CTRL + C & \ */
int	main(void)
{
	char	*line;
	t_token	*tokens;
	t_token	*tmp;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (line[0] != '\0')
		{
			add_history(line);
			tokens = lexer(line);
			if (tokens)
			{
				tmp = tokens;
				while (tmp)
				{
					printf("Token Type: %d, Value: %s\n", tmp->type, tmp->value);
					tmp = tmp->next;
				}
				free_token_list(tokens);
			}
		}
		free(line);
	}
	return (0);
}
