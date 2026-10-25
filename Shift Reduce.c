#include <stdio.h>
#include <string.h>

char input[200];
int top=-1;
char stack[200];
int ip=0;

void display(char action[])
{
	for(int i=0;i<=top;i++)
	{
		printf("%c",stack[i]);
	}
	printf("\t%s\t%s\n",input+ip,action);
}

int reduce()
{
	if (top >=0 && stack[top]=='i')
	{
		stack[top]='E';
		display("Reduce : E->i");
		return 1;
	}
	if (top>=2 && stack[top-2]=='E' && stack[top-1]=='+' && stack[top]=='E')
	{
		top=top-2;
		stack[top]='E';
		display("Reduce: E->E+E");
		return 1;	
	}
	if (top>=2 && stack[top-2]=='E' && stack[top-1]=='-' && stack[top]=='E')
	{
		top=top-2;
		stack[top]='E';
		display("Reduce: E->E-E");
		return 1;	
	}
	if (top>=2 && stack[top-2]=='E' && stack[top-1]=='*' && stack[top]=='E')
	{
		top=top-2;
		stack[top]='E';
		display("Reduce: E->E*E");
		return 1;	
	}
	if (top>=2 && stack[top-2]=='E' && stack[top-1]=='/' && stack[top]=='E')
	{
		top=top-2;
		stack[top]='E';
		display("Reduce: E->E/E");
		return 1;	
	}
	if (top>=2 && stack[top-2]=='(' && stack[top-1]=='E' && stack[top]==')')
	{
		top=top-2;
		stack[top]='E';
		display("Reduce: E->E+E");
		return 1;	
	}
	return 0;
}

void main()
{
	printf("Enter expression\n");
	scanf("%s",input);
	
	strcat(input,"$");
	
	printf("STACK\tINPUT\tACTION\n");
	display("START");
	
	while(1)
	{
		if(input[ip]!='$')
		{
			stack[++top]=input[ip++];
			display("SHIFT");
		}
		
		while(reduce());
		if (input[ip]=='$' && top==0 && stack[top]=='E')
		{
			printf("Accepted");
			break;
		}
		if (input[ip]=='$')
		{
			printf("Rejected");
			break;
		}
	}
}



Try will i+I
