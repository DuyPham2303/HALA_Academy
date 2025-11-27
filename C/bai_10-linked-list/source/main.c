#include "list.h"
#include "log.h"
#include <stdio.h>

void test1()
{
    ListStatus st;
    Node *head = CreateNode(23, &st);

    for (int i = 1; i < 6; i++)
        push_back(&head, i);

    printf("push back : ");
    printNode(head);

    pop_back(&head);
    pop_back(&head);
    pop_back(&head);

    printf("pop back : ");
    printNode(head);

    for (int i = 7; i < 12; i++)
        push_front(&head, i);

    printf("push front : ");
    printNode(head);

    pop_front(&head);
    pop_front(&head);
    pop_front(&head);

    printf("pop front : ");
    printNode(head);

    int frontdata, backdata;
    front(head, &frontdata);
    back(head, &backdata);
    printf("front : %d\nback : %d\nsize: %d\n", frontdata, backdata, size(head));
}

void Full_Test()
{
    Node *head = NULL;
    int running = 1;

    while (running)
    {
        printf("\n-- Linked List Test Menu --\n");
        printf("0)  exit\n");
        printf("1)  push_front\t");
        printf("2)  push_back\t");
        printf("3)  pop_front\t");
        printf("4)  pop_back\n");
        printf("5)  insert\t");
        printf("6)  erase\t");
        printf("7)  front\t");
        printf("8)  back\n");
        printf("9)  get \t");
        printf("10) size\t");
        printf("11) print\t");
        printf("12) clear");
        printf("\n-------------------------\n");
        printf("Choose an option: ");

        int opt = -1;
        if (scanf("%d", &opt) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            goto ErrorlogInput;
        }

        switch (opt)
        {
        case 0:
        {
            running = 0;
            break;
        }

        case 1:
        {
            int v;
            printf("value: ");
            if (scanf("%d", &v) != 1)
            {
               goto ErrorlogInput;
            }
            ListStatus st = push_front(&head, v);
            if (st != LIST_OK)
            {
                list_log(st, "push_front failed");
            }
            break;
        }

        case 2:
        {
            int v;
            printf("value: ");
            if (scanf("%d", &v) != 1)
            {
                goto ErrorlogInput;
            }
            ListStatus st = push_back(&head, v);
            if (st != LIST_OK)
            {
                list_log(st, "push_back failed");
            }
            break;
        }

        case 3:
        {
            ListStatus st = pop_front(&head);
            if (st != LIST_OK)
                list_log(st, "pop_front failed");
            break;
        }

        case 4:
        {
            ListStatus st = pop_back(&head);
            if (st != LIST_OK)
                list_log(st, "pop_back failed");
            break;
        }

        case 5:
        {
            int pos, val;
            printf("insert position: ");
            if(scanf("%d",&pos) != 1) goto ErrorlogInput;

            printf("insert value: ");
            if(scanf("%d",&val) != 1) goto ErrorlogInput;

            ListStatus st = insert(&head, val, pos);
            if (st != LIST_OK)
                list_log(st, "insert failed");
            break;
        }

        case 6:
        {
            int pos;
            printf("pos: ");
            if (scanf("%d", &pos) != 1)
            {
               goto ErrorlogInput;
            }
            ListStatus st = erase(&head, pos);
            if (st != LIST_OK)
                list_log(st, "erase failed");
            break;
        }

        case 7:
        {
            int out;
            ListStatus st = front(head, &out);
            if (st == LIST_OK)
                printf("front = %d\n", out);
            else
                list_log(st, "front failed");
            break;
        }

        case 8:
        {
            int out;
            ListStatus st = back(head, &out);
            if (st == LIST_OK)
                printf("back = %d\n", out);
            else
                list_log(st, "back failed");
            break;
        }

        case 9:
        {
            int pos;
            printf("pos: ");
            if (scanf("%d", &pos) != 1)
            {
                printf("bad input\n");
                break;
            }
            int out;
            ListStatus st = get(head, pos, &out);
            if (st == LIST_OK)
                printf("get(%d) = %d\n", pos, out);
            else
                list_log(st, "get failed");
            break;
        }

        case 10:
        {
            printf("size = %d\n", size(head));
            break;
        }

        case 11:
        {
            printNode(head);
            break;
        }

        case 12:
        {
            ListStatus st = clear(&head);
            if (st != LIST_OK)
                list_log(st, "clear failed");
            break;
        }

        ErrorlogInput:
            printf("Unknown/Invalid option \n");
            break;
        }
    }

    /* Final cleanup */
    if (head)
        clear(&head);
    printf("Exiting\n");
}

int main(void)
{
    Full_Test();
    return 0;
}