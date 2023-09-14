#include "shell.h"

/**
 * safeFree - Frees a pointer and sets it to NULL.
 * @ptr: Address of the pointer to free.
 *
 * Returns:
 *   - 1 if memory was freed.
 *   - 0 if the pointer was already NULL or invalid.
 */
int safeFree(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
        return (1);
    }
    return (0);
}
