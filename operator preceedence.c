#include <stdio.h>
#include <string.h>

char stack[50], input[50];
int top = -1, ip = 0;

char table[8][8] = {
/*       +    -    *    /    (    )    i    $ */
 /* + */ {'>','>','<','<','<','>','<','>'},
 /* - */ {'>','>','<','<','<','>','<','>'},
 /* * */ {'>','>','>','>','<','>','<','>'},
 /* / */ {'>','>','>','>','<','>','<','>'},
 /* ( */ {'<','<','<','<','<','=','<',' '},
 /* ) */ {'>','>','>','>',' ','>',' ','>'},
 /* i */ {'>','>','>','>',' ','>',' ','>'},
 /* $ */ {'<','<','<','<','<',' ','<',' '}
};

int indexOf(char c)
{
    switch(c)
    {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '(': return 4;
        case ')': return 5;
        case 'i': return 6;
        case '$': return 7;
    }
    return -1;
}

void display(const char *action)
{
    int i;

    for(i = 0; i <= top; i++)
        printf("%c", stack[i]);

    printf("\t\t%s\t\t%s\n", input + ip, action);
}

int reduce(char *action)
{
    /* i -> E */
    if(top >= 0 && stack[top] == 'i')
    {
        stack[top] = 'E';
        strcpy(action, "Reduce i -> E");
        return 1;
    }

    /* (E) -> E */
    if(top >= 2 &&
       stack[top] == ')' &&
       stack[top-1] == 'E' &&
       stack[top-2] == '(')
    {
        top -= 2;
        stack[top] = 'E';
        strcpy(action, "Reduce (E) -> E");
        return 1;
    }

    /* E op E -> E */
    if(top >= 2 &&
       stack[top] == 'E' &&
       stack[top-2] == 'E' &&
       (stack[top-1] == '+' ||
        stack[top-1] == '-' ||
        stack[top-1] == '*' ||
        stack[top-1] == '/'))
    {
        char op = stack[top-1];

        top -= 2;
        stack[top] = 'E';

        sprintf(action, "Reduce E%cE -> E", op);
        return 1;
    }

    return 0;
}

int main()
{
    int i, row, col;
    char a, b, relation;
    char action[30];

    printf("Enter expression (use i for identifier): ");
    scanf("%49s", input);

    if(strlen(input) + 1 >= sizeof(input))
    {
        printf("Rejected\n");
        return 0;
    }

    strcat(input, "$");

    stack[++top] = '$';

    printf("\nSTACK\t\tINPUT\t\tACTION\n");
    display("Initialize");

    while(1)
    {
        i = top;

        while(i >= 0 && stack[i] == 'E')
            i--;

        if(i < 0)
        {
            printf("\nRejected\n");
            break;
        }

        a = stack[i];
        b = input[ip];

        /* Accept condition */
        if(top == 1 &&
           stack[0] == '$' &&
           stack[1] == 'E' &&
           b == '$')
        {
            display("Accept");
            printf("\nAccepted\n");
            break;
        }

        row = indexOf(a);
        col = indexOf(b);

        if(row == -1 || col == -1)
        {
            printf("\nRejected\n");
            break;
        }

        relation = table[row][col];

        if(relation == '<' || relation == '=')
        {
            if(b == '$')
            {
                printf("\nRejected\n");
                break;
            }

            stack[++top] = b;
            ip++;

            sprintf(action, "Shift %c", b);
            display(action);
        }
        else if(relation == '>')
        {
            if(!reduce(action))
            {
                printf("\nRejected\n");
                break;
            }

            display(action);
        }
        else
        {
            printf("\nRejected\n");
            break;
        }
    }

    return 0;
}
