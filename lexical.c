#include <stdio.h>
#include <string.h>
#include <ctype.h>

int iskeyword(char word[])
{
	char *k[]={"int","float","char","void","if","else","for","while","return"};
	for(int i=0;i<9;i++)
	{
		if(strcmp(k[i],word)==0)
		{
			return 1;
		}
	}
	return 0;
}

void main()
{
	char str[1000],line[500],word[300];
	int i=0,j;
	while (i<1000)
	{
		if(fgets(line,sizeof(line),stdin)==NULL)
		{
			break;
		}
		if(strcmp(line,"END\n")==0 || strcmp(line,"END")==0)
		{
			break;
		}
		if (strlen(line)>1000-i)
		{
			break;
		}
		strcpy(str+i,line);
		i=i+strlen(line);
	}
	str[i]='\0';
	i=0;
	while(str[i]!='\0')
	{
		if(str[i]==' '||str[i]=='\t' ||str[i]=='\n')
		{
			i++;
			continue;
		}
		if(isalpha(str[i]) || str[i]=='_')
		{
			j=0;
			while(isalnum(str[i]) ||str[i]=='_')
			{
				word[j++]=str[i];
				i++;
			}
			word[j]='\0';
					
			if(iskeyword(word))
			{
				printf("Keyword %s",word);
			}
			else
			{
				printf("Identifier %s",word);
			}
		}
		else if(isdigit((unsigned char)str[i]))
		{
			j=0;
			while(isdigit((unsigned char)str[i]))
			{
				word[j++]=str[i];
				i++;
			}
			word[j]='\0';
			printf("Number: %s",word);
		}
		else if(strchr("+-*/%=<>!&|",str[i]))
		{
			printf("Operator: %c",str[i]);
			i++;
		}
		else if(strchr(";,(){}[]",str[i]))
		{
			printf("Special Symbols: %c",str[i]);
			i++;
		}
		else{
			i++;
		}
	}
}
