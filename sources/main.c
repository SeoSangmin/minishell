/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:35 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/19 13:37:38 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **en)
{
	char	**envp;
	t_tree	*tree;
	char	*line;
	t_set	sa;			

	if (argc != 1 || argv[1] != 0)
		exit(1);
	minishell_sig_setting(&sa.sig, &sa.old_term, &sa.term);
	minishell_start_setting(&envp, en, &tree);
	while (1)
	{
		line = readline(COL_1 MSG_1 COL_2 MSG_2 RESET_COL);
		if (!line)
			program_end(sa.old_term);
		else if (!*line)
			free(line);
		else if (*line)
		{
			tree_start(tree, line, &envp, sa);
			sigaction(SIGINT, &sa.sig, 0);
			sigaction(SIGQUIT, &sa.sig, 0);
		}
	}
	return (0);
}
