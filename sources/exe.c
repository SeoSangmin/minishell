#include "minishell.h"
#include "tree.h"

void	exe_pipe(t_tree *tree, t_node *cur)
{
	tree->filefds[0] = 0;
	tree->filefds[1] = 0;
	if (cur->left == 0)
		return ;
	if (cur->right->left != 0)
	{
		pipe(tree->fds);
		tree->first += 1;
	}
	else
	{
		tree->last = 1;
	}
}

void	exe_redir(t_tree *tree, t_node *cur, char ***envp)
{
	if (tree->err != 0)
			return ;
	if (cur->cont.redir_type == IN)
	{
		tree->filefds[0] = open(cur->cont.file_name, O_RDONLY);
		//printf("%d\n\n", tree->filefds[0]);
		if (tree->filefds[0] == -1)
		{
			tree->err = 1;
			perror(cur->cont.file_name);
		}
		dup2(tree->filefds[0], 0);
		close(tree->filefds[0]);
	}
	else if (cur->cont.redir_type == HERE_DOC)
	{
		;
	}
	else if (cur->cont.redir_type == OUT_T)
	{
		tree->filefds[1] = open(cur->cont.file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tree->filefds[1] == -1)
		{
			tree->err = 1;
			perror(cur->cont.file_name);
			return ;
		}
		dup2(tree->filefds[1], 1);
		close(tree->filefds[1]);
	}
	else if (cur->cont.redir_type == OUT_A)
	{
		tree->filefds[1] = open(cur->cont.file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (tree->filefds[1] == -1)
		{
			tree->err = 1;
			perror(cur->cont.file_name);
		}
		dup2(tree->filefds[1], 1);
		close(tree->filefds[1]);
	}
}

//void	last_simple_com(t_tree *tree, t_node *cur, char ***envp)
//{
//	int pid;

//	pid = fork();
//	if (pid == 0)
//	{
//		if (tree->filefds[1] > 0)
//			;
//		else
//		{
//			dup2(tree->stdfds[1], 1);
//			close(tree->stdfds[1]);
//		}
//		execve(cur->cont.path, cur->cont.args, 0);
//		perror("");
//		exit(errno);
//	}
//	else
//	{
//		tree->pid = pid;
//		return ;
//	}
//}

//void	exe_simple_com(t_tree *tree, t_node *cur, char ***envp)
//{
//	int pid;
	
//	if (tree->err == 0)
//	{
//		if (tree->last == 1)
//		{
//			last_simple_com(tree, cur, envp);
//			return ;
//		}
//		pid = fork();
//		if (pid == 0)
//		{
			//close(tree->fds[0]);
			//if (tree->filefds[1] > 0)
			//	close(tree->fds[1]);
			//else
			//{
			//	dup2(tree->fds[1], 1);
			//	close(tree->fds[1]);
			//}
//			execve(cur->cont.path, cur->cont.args, *envp);
//			perror("");
//			//errno 확인해서 exit하셈
//			exit(1);
//		}
//		else
//		{
//			close(tree->fds[1]);
//			dup2(tree->fds[0], 0);
//			close(tree->fds[0]);
//			return ;
//		}
//	}
//	else
//	{
//		close(tree->fds[1]);
//		close(tree->fds[0]);
//		tree->err = 0;
//		return ;
//	}
//}

void	exe_cur(t_tree *tree, t_node *cur, char ***envp)
{
	if (cur->type == PIPE)
		exe_pipe(tree, cur);
	else if (cur->type == CMD)
		;
	else if (cur->type == REDIR)
		exe_redir(tree, cur, envp);
	else if (cur->type == SIMPLE_CMD && tree->last == 0)
	{
		exe_simple_com(tree, cur, envp);
	}
	else if (cur->type == SIMPLE_CMD && tree->last == 1)
	{
		last_simple_com(tree, cur, envp);
	}	
	else if (cur->type == NO_CMD)
		return ;
}