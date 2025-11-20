/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzangaro <mzangaro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:24:52 by mzangaro          #+#    #+#             */
/*   Updated: 2025/11/20 17:39:25 by mzangaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
