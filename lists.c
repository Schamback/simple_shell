#include "main.h"

/**
 * _addNode - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *_addNode(list_t **head, const char *str, int num)
{
	list_t *new_h;

	if (!head)
		return (NULL);
	new_h = malloc(sizeof(list_t));
	if (!new_h)
		return (NULL);
	memset((void *)new_h, 0, sizeof(list_t));
	new_h->num = num;
	if (str)
	{
		new_h->str = strdup(str);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *head;
	*head = new_h;
	return (new_h);
}

/**
 * add_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_end(list_t **head, const char *str, int num)
{
	list_t *new_nodes, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_nodes = malloc(sizeof(list_t));
	if (!new_nodes)
		return (NULL);
	memset((void *)new_nodes, 0, sizeof(list_t));
	new_nodes->num = num;
	if (str)
	{
		new_nodes->str = strdup(str);
		if (!new_nodes->str)
		{
			free(new_nodes);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_nodes;
	}
	else
		*head = new_nodes;
	return (new_nodes);
}

/**
 * print_str - prints only the str element of a list_t linked list
 * @a: pointer to first node
 *
 * Return: size of list
 */
size_t print_str(const list_t *a)
{
	size_t s = 0;

	while (a)
	{
		puts(a->str ? a->str : "(nil)");
		puts("\n");
		a = a->next;
		s++;
	}
	return (s);
}

/**
 * delete_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_nodes;
	unsigned int w = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (w == index)
		{
			prev_nodes->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		w++;
		prev_nodes = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_node - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_node(list_t **head_ptr)
{
	list_t *node, *next_nodes, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_nodes = node->next;
		free(node->str);
		free(node);
		node = next_nodes;
	}
	*head_ptr = NULL;
}
