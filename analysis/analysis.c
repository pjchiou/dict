#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define BUFFER 256

typedef struct list {
    char *prefix;
    int iCount;
    double dSec;
    struct list_head entry;
} list;

list *initial_list()
{
    list *head = malloc(sizeof(list));
    if (!head)
        return (NULL);

    head->prefix = NULL;
    head->iCount = 0;
    head->dSec = 0.0;
    INIT_LIST_HEAD(&head->entry);

    return (head);
}

void add_node(char *prefix, double sec, list *head)
{
    struct list_head *node;
    list_for_each(node, &head->entry)
    {
        if (strcmp(container_of(node, list, entry)->prefix, prefix) > 0)
            break;

        if (strcmp(container_of(node, list, entry)->prefix, prefix) == 0) {
            container_of(node, list, entry)->iCount++;
            container_of(node, list, entry)->dSec += sec;
            return;
        }
    }

    list *new = malloc(sizeof(list));
    if (!new)
        return;

    new->prefix = strdup(prefix);
    new->iCount = 1;
    new->dSec = sec;
    list_add_tail(&new->entry, node);
}

void show_list(list *head)
{
    struct list_head *node;
    list_for_each(node, &head->entry)
    {
        printf("%s\t%d\t%f\t%f\n", container_of(node, list, entry)->prefix,
               container_of(node, list, entry)->iCount,
               container_of(node, list, entry)->dSec,
               container_of(node, list, entry)->dSec /
                   container_of(node, list, entry)->iCount);
    }
}

void free_list(list *head)
{
    struct list_head *node, *safe;

    list_for_each_safe(node, safe, &head->entry)
    {
        free(container_of(node, list, entry)->prefix);
        free(container_of(node, list, entry));
    }
    free(head);
}

int main()
{
    FILE *f;
    char sLine[BUFFER], augs[4][BUFFER];
    char prefix[5], sec[20];
    list *head = initial_list();

    f = fopen("dict_dis.txt", "r");

    while (fgets(sLine, BUFFER - 2, f)) {
        for (int i = 0, row = 0, col = 0; sLine[i] != '\0'; i++) {
            augs[row][col++] =
                (sLine[i] == ' ' || sLine[i] == '\n') ? '\0' : sLine[i];
            if (sLine[i] == ' ') {
                row++;
                col = 0;
            }
        }
        add_node(augs[1], atof(augs[2]), head);
    }
    show_list(head);

    fclose(f);
    free_list(head);
    return (0);
}
