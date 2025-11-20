/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzangaro <mzangaro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:24:39 by mzangaro          #+#    #+#             */
/*   Updated: 2025/11/20 17:39:43 by mzangaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
