#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 60
char infix[MAX],postfix[MAX];
char ch;
int j=0;
int optop=-1;
char opstack[MAX],localstack[MAX][MAX];
int top=-1;
char op1[MAX],op2[MAX],result[MAX];
int tempcount=1;

int prece(char ch)
{
	if (ch=='+' ||ch=='-')
	{
		return 1;
	}
	else if (ch=='*' ||ch=='/')
	{
		return 2;
	}
	return 0;
}

void posty()
{
	for(int i=0;infix[i]!='\0';i++)
	{
		ch=infix[i];
		if (ch==' ')
		{
			continue;
		}
		if (isalnum(ch))
		{
			postfix[j++]=ch;
		}
		else if (ch=='(')
		{
			opstack[++optop]=ch;
		}
		else if(ch==')')
		{
			while(optop!=-1 && opstack[optop]!='(')
			{
				postfix[j++]=opstack[optop--];
			}
			optop--;
		}
		else
		{
			while(optop!=-1 && prece(opstack[optop])>=prece(ch))
			{
				postfix[j++]=opstack[optop--];
			}
			opstack[++optop]=ch;
		}
	}
	while(optop!=-1)
	{
		postfix[j++]=opstack[optop--];
	}
	postfix[j] = '\0';
}

void tac()
{
	for(int i=0;postfix[i]!='\0';i++)
	{
		ch=postfix[i];
	
		if (isalnum(ch))
		{
		localstack[++top][0]=ch;
		localstack[top][1]='\0';
		}
		else
		{
		strcpy(op2,localstack[top--]);
		strcpy(op1,localstack[top--]);
		sprintf(result,"t%d",tempcount++);
		printf("%s = %s %c %s\n",result,op1,ch,op2);
		strcpy(localstack[++top],result);
		
		}
	}
}

void main()
{
	printf("Enter infix expression\n");
	scanf("%s",infix);
	
	posty();
	printf("Postfix Expression %s",postfix);
	
	printf("Three Address Code\n");
	tac();
}
