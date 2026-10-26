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

void display()
{
    int i;

    for(i = 0; i <= top; i++)
        printf("%c", stack[i]);

    printf("\t\t%s\n", input + ip);
}

int reduce()
{
    /* i -> E */
    if(top >= 0 && stack[top] == 'i')
    {
        stack[top] = 'E';
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
        return 1;
    }

    /* E+E -> E, E-E -> E, E*E -> E, E/E -> E */
    if(top >= 2 &&
       stack[top] == 'E' &&
       stack[top-2] == 'E' &&
       (stack[top-1] == '+' ||
        stack[top-1] == '-' ||
        stack[top-1] == '*' ||
        stack[top-1] == '/'))
    {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }

    return 0;
}

int main()
{
    int i, row, col;
    char a, b, relation;

    printf("Enter expression (use i for identifier): ");
    scanf("%49s", input);

    if(strlen(input) + 1 >= sizeof(input))
    {
        printf("Rejected\n");
        return 0;
    }

    strcat(input, "$");

    stack[++top] = '$';

    printf("\nSTACK\t\tINPUT\n");
    display();

    while(1)
    {
        i = top;

        while(i >= 0 && stack[i] == 'E')
            i--;

        if(i < 0)
        {
            printf("Rejected\n");
            break;
        }

        a = stack[i];
        b = input[ip];

        /* Accept when stack is $E and input is $ */
        if(top == 1 &&
           stack[0] == '$' &&
           stack[1] == 'E' &&
           b == '$')
        {
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
            display();
        }
        else if(relation == '>')
        {
            if(!reduce())
            {
                printf("\nRejected\n");
                break;
            }

            display();
        }
        else
        {
            printf("\nRejected\n");
            break;
        }
    }

    return 0;
}
