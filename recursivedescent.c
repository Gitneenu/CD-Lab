Grammar
E  → TE'
E' → +TE' | ε
T  → FT'
T' → *FT' | ε
F  → (E) | i



#include <stdio.h>
#include <string.h>

char input[100];
int pos=0;
int error=0;

void E(),T(),Eprime(),Tprime(),F();

void E()
{
	T();
	Eprime();
}

void Eprime()
{
	if (input[pos]=='+')
	{
		pos++;
		T();
		Eprime();
	}
}

void T()
{
	F();
	Tprime();
}

void Tprime()
{
	if(input[pos]=='*')
	{
		pos++;
		F();
		Tprime();
	}
}

void F()
{
	if (input[pos]=='i')
	{
		pos++;
	}
	else if(input[pos]=='(')
	{
		pos++;
		E();
		if (input[pos]==')')
		{
			pos++;
		}
		else
		{
			error=1;
		}
	}
	else
	{
		error=1;
	}
}

void main()
{
	printf("Enter expression\n");
	scanf("%s",input);
	
	strcat(input,"$");
	E();
	
	if (input[pos]=='$' && error==0)
	{
		printf("String Accepted\n");
	}
	else
	{
		printf("String Rejected\n");
	}
	
}
