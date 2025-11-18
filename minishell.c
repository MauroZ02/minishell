/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzangaro <mzangaro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:24:52 by mzangaro          #+#    #+#             */
/*   Updated: 2025/11/18 20:32:54 by mzangaro         ###   ########.fr       */
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
	new->next = NULL;
	return (new);
}

t_token	*lexer(char *line)
{
	int		i;
	int		start;
	t_token	*head;
	t_token	*cur;
	t_token	*tmp;

	i = 0;
	start = i;
	head = NULL;
	cur = NULL;
	tmp = NULL;
	while (line[i])
	{
		if ((line[i] >= 7 && line[i] <= 13)|| line[i] == 32)
			i++;
		else 
		{
			if (line[i] == '"')
			{
				i++;
				start = i;
				while ((line[i] != '"') && line[i] != '\0')
					i++;
				cur = new_token(ft_substr(line, start, i - start), TOKEN_QUOTES);
				cur = cur->next;
			}
			else if (line[i] == "'")
			{
				i++;
				start = i;
				while ((line[i] != "'") && line[i] != '\0')
					i++;
				cur = new_token(ft_substr(line, start, i - start), TOKEN_SING_Q);
				cur = cur->next;
			}
			else if (line[i] == '>')
			{
				start = i;
				if (line[i + 1] == '>')
				{
					i++;
					cur = new_token(ft_substr(line, start, i - start), TOKEN_APPEND);
					cur = cur->next;
				}
				else 
				{
					i++;
					cur = new_token(ft_substr(line, start, i - start), TOKEN_OUT_REDIR);
					cur = cur->next;
				}
			}
			else if (line[i] == '<')
			{
				start = i;
				if (line[i + 1] == '<')
				{
					i++;
					cur = new_token(ft_substr(line, start, i - start), TOKEN_HEREDOC);
					cur = cur->next;
				}
				else 
				{
					i++;
					cur = new_token(ft_substr(line, start, i - start), TOKEN_IN_REDIR);
					cur = cur->next;
				}
			}
			else if (line[i] == '|')
			{
				start = i;
				i++;
				cur = new_token(ft_substr(line, start, i - start), TOKEN_PIPE);
				cur = cur->next;
			}
			else
			{
				start = i;
				while (line[i] != 32 && line[i] != 9 && line[i] != '|' && line[i] != '<' && line[i] != '>' && line[i] != "'" && line[i] != '"' && line[i] != '\0')
					i++;
				cur = new_token(ft_substr(line, start, i - start), TOKEN_WORD);
				cur = cur->next;
			}
		}
		if (!cur)
			return (NULL);
		if (head == NULL)
		{
			head = cur;
		}
		else
		{
			tmp = cur;
			cur = cur->next;
			cur->next = tmp;
		}
	}
	if (head == NULL)
		return NULL;
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
	char		*line;
	char		*prompt;
	t_token		*token;

	token = malloc(sizeof(t_token));

	prompt = "minishell> ";
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline(prompt);
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		else if (line)
		{
			if (line[0] != '\0')
				add_history(line);
		}
		free(line);
	}
	return (0);
}
