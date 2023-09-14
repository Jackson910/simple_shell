#include "shell.h"

/**
 * listLength - Calculates the length of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t listLength(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        h = h->next;
        i++;
    }

    return (i);
}

/**
 * listToStrings - Converts a linked list of strings into an array of strings.
 * @head: Pointer to the first node of the linked list.
 *
 * Return: An array of strings, or NULL on failure.
 */
char **listToStrings(list_t *head)
{
    list_t *node = head;
size_t i = listLength(head), j;
char **strs;
char *str;

if (!head || !i)
    return NULL;

strs = (char **)malloc(sizeof(char *) * (i + 1));
if (!strs)
    return NULL;

for (i = 0; node; node = node->next, i++)
{
    
    str = (char *)malloc(strlen(node->str) + 1);
    if (!str)
    {
         for (j = 0; j < i; j++)
            free(strs[j]);
        free(strs);
        return NULL;
    }
    strcpy(str, node->str);    
 
    strs[i] = str;
}
strs[i] = NULL;
return (strs);

}

/**
 * printList - Prints all elements of a linked list along with their numerical index.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t printList(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _print_string(convert_number(h->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _print_string(h->str ? h->str : "(nil)");
        _print_string("\n");
        h = h->next;
        i++;
    }

    return (i);
}

/**
 * findNodeWithPrefix - Finds a node whose string starts with a specified prefix and, optionally, a matching character after the prefix.
 * @node: Pointer to the head of the list.
 * @prefix: String to match as a prefix.
 * @c: The character to match after the prefix (-1 to match any character).
 *
 * Return: A matching node or NULL.
 */
list_t *findNodeWithPrefix(list_t *node, char *prefix, char c)
{
    char *p = NULL;

    while (node)
    {
        p = string_starts_with(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return (node);
        node = node->next;
    }

    return (NULL);
}

/**
 * getNodeIndex - Gets the index of a node within a linked list.
 * @head: Pointer to the head of the list.
 * @node: Pointer to the node for which the index is sought.
 *
 * Return: The index of the node, or -1 if not found.
 */
ssize_t getNodeIndex(list_t *head, list_t *node)
{
    size_t i = 0;

    while (head)
    {
        if (head == node)
            return (i);
        head = head->next;
        i++;
    }

    return (-1);
}
