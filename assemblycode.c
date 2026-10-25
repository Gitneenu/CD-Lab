#include <stdio.h>
#include <string.h>

void main()
{
	int n;
	char line[100];
	printf("Enter number of three adresss code instructions\n");
	scanf("%d",&n);
	getchar();
	
	char result[50],op1[50],op2[50],op;
	
	for(int i=0;i<n;i++)
	{
		fgets(line,sizeof(line),stdin);
		if (strstr(line,"GOTO")!=NULL)
		{
			char label[40];
			sscanf(line, "GOTO %s",label);
			printf("JUMP %s\n",label);
		}
		else if(sscanf(line, "%s = %s %c %s",result,op1,&op,op2)==4)
		{
			switch(op)
			{
				case '+':
					printf("MOV AX %s\n",op1);
					printf("ADD AX %s\n",op2);
					printf("MOV %s AX\n",result);
					break;
					
				case '-':
					printf("MOV AX %s\n",op1);
					printf("SUB AX %s\n",op2);
					printf("MOV %s AX\n",result);
					break;
					
				case '*':
					printf("MOV AX %s\n",op1);
					printf("MUL AX %s\n",op2);
					printf("MOV %s AX\n",result);
					break;
				
				default:
					printf("Invalid operation\n");
			}
		}
		else if(sscanf(line,"%s=%s",result,op1)==2)
		{
			printf("MOV AX %s",op1);
			printf("MOV %s AX",result);
		}
	}
}
