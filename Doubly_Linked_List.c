#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define NODE struct list_node *

#define NULL_CHECK(item)                           \
    {                                              \
        if (!item)                                 \
        {                                          \
            printf("Unable to allocate memory\n"); \
            return -1;                             \
        }                                          \
    }

struct list_node
{
    int data;
    NODE prev;
    NODE linked_node;
};

NODE Get_Tail(NODE *head)
{
    NODE current_node = *head;
    NODE last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->linked_node;
    }

    return last_node;
}

int Append(NODE *head, int data, bool Begin)
{
    NODE appended_node = (NODE)malloc(sizeof(struct list_node));
    NULL_CHECK(appended_node);
    if (Begin)
    {
        appended_node->prev = NULL;
        appended_node->data = data;
        appended_node->linked_node = *head;
        (*head)->prev = appended_node;
        *head = appended_node;
    }
    else
    {
        NODE tp = Get_Tail(head);
        appended_node->prev = tp;
        appended_node->data = data;
        appended_node->linked_node = NULL;
        tp->linked_node = appended_node;
    }
    return 0;
}

int Append_Middle(NODE head, int data, int index, bool Before)
{
    NODE temp = head;
    NODE appended_node = (NODE)malloc(sizeof(struct list_node));
    NULL_CHECK(appended_node);
    appended_node->data = data;

    for (int i = 0; i <= index - 1; i++)
    {
        temp = temp->linked_node;
    }
    if (Before)
    {
        if (temp->prev)
            temp->prev->linked_node = appended_node;
        appended_node->prev = temp->prev;
        appended_node->linked_node = temp;
        temp->prev = appended_node;
    }
    else
    {
        if (temp->linked_node)
            temp->linked_node->prev = appended_node;
        appended_node->linked_node = temp->linked_node;
        appended_node->prev = temp;
        temp->linked_node = appended_node;
    }
    return 0;
}

int POP_First(NODE head)
{
    if (!head)
        return -1;

    NODE current_node = head;

    head = head->linked_node;
    current_node->linked_node = NULL;
    return current_node->data;
}

NODE POP_Last(NODE head)
{
    if (!head)
        return NULL;
    NODE previous_node = head;
    NODE current_node = head;
    while (current_node->linked_node)
    {
        previous_node = current_node;
        current_node = current_node->linked_node;
    }
    previous_node->linked_node = NULL;
    return current_node;
}

int REMOVE(NODE head, int index)
{
    NODE current_node = head;
    for (int i = 0; i <= index - 1; i++)
    {
        if (index == 0)
        {
            head = current_node->linked_node;
            free(current_node);
            current_node = NULL;
            return -1;
        }
        current_node = current_node->linked_node;
    }
    current_node->prev->linked_node = current_node->linked_node;
    current_node->linked_node->prev = current_node->prev;
    free(current_node);
    int ephe_data = current_node->data;
    current_node = NULL;
    return ephe_data;
}

int LinkedListLenght(NODE *head)
{
    NODE temp = *head;
    if (!temp)
    {
        return 0;
    }
    int lenght = 1;
    while (temp->linked_node)
    {
        lenght++;
        temp = temp->linked_node;
    }
    return lenght;
}

int RandomMax(int i)
{
    srand(time(NULL));
    int random = 0;
    random = (rand() % i);
    return random;
}

NODE Shuffle(NODE head)
{
    int list_lenght = LinkedListLenght(&head);
    NODE current_node = head;
    NODE temp = NULL;
    int index = 0;

    for (int i = list_lenght; i > 0; i--)
    {
        temp = Get_Tail(&current_node);
        index = RandomMax(i);
        for (int j = 0; j < index; j++)
        {
            current_node = current_node->linked_node;
        }
        
        if (current_node->prev == NULL)
            current_node->linked_node->prev = NULL;
        else if (current_node->linked_node != NULL)
        {
            current_node->prev->linked_node = current_node->linked_node;
            current_node->linked_node->prev = current_node->prev;
        }
        if (current_node->linked_node != NULL)
        {
            current_node->linked_node = NULL;
            current_node->prev = temp;
            temp->linked_node = current_node;
        }
        
        for (int j = 0; j < list_lenght - 1; j++)
        {
            if (current_node->prev == NULL)
                break;
            current_node = current_node->prev;
        }
    }

    return current_node;
}

int main(int argc, char const *argv[])
{
    NODE head = malloc(sizeof(struct list_node));
    head->linked_node = NULL;
    head->prev = NULL;
    head->data = 10;

    Append(&head, 20, true);
    Append(&head, 33, true);
    Append(&head, 70, true);

    Append(&head, 10, false);
    Append(&head, 50, false);
    Append(&head, 40, false);
    Append_Middle(head, 44, 2, true);
    Append_Middle(head, 80, 1, true);
    Append_Middle(head, 22, 4, false);
    Append_Middle(head, 17, 3, false);
    NODE prova = head;
    while (prova != NULL)
    {
        printf("%d ", prova->data);
        prova = prova->linked_node;
    }
    head = Shuffle(head);
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->linked_node;
    }
    return 0;
}
