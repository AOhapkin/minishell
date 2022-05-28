#include "minishell.h"

t_token	*pull_last_token(t_token **stack)
{
	t_token	*tmp;
	t_token	*last;

	last = NULL;
	if (stack && *stack)
	{
		tmp = *stack;
		while (tmp && tmp->next && tmp->next->next)
			tmp = tmp->next;
		last = tmp->next;
		tmp->next = NULL;
	}
	return (last);
}

t_token	*pull_first_token(t_token **stack)
{
	t_token	*first;

	first = NULL;
	if (stack && *stack)
	{
		first = *stack;
		*stack = first->next;
		first->next = NULL;
	}
	return (first);
}

void	push_token_back(t_token **stack, t_token *token)
{
	t_token	*last_token;

	if (*stack)
	{
		last_token = get_last_token(*stack);
		last_token->next = token;
	}
	else
		*stack = token;
}

void	push_token_front(t_token **stack, t_token *token)
{
	if (stack && token)
	{
		token->next = *stack;
		*stack = token;
	}
}

int	get_position_in_the_stack(t_token *stack, t_token *token)
{
	int	position;

	position = 0;
	while (stack && token && stack != token)
	{
		position++;
		stack = stack->next;
	}
	return (position);
}
