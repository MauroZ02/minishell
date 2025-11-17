/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzangaro <mzangaro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:24:52 by mzangaro          #+#    #+#             */
/*   Updated: 2025/11/17 20:10:42 by mzangaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*prompt;

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
