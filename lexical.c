#include <stdio.h>
#include <string.h>
#include <ctype.h>

int iskeyword(char wor[])
{
	char *k[] = {"int","float","char","void","if","else","for","while","return"};
	int n=9,j;
	for (j=0;j<n;j++)
	{
		if (strcmp(k[j],wor)==0)
		{
			return 1;
		}
	}
	return 0;
}

void main()
{
	char str[1000],word[50],line[400];
	int i=0,j;
	
	while(i<999)
	{
		if (fgets(line,sizeof(line),stdin)==NULL)
		{
			break;
		}
		if (strcmp(line,"END\n")==0||strcmp(line,"END")==0)
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
		if (str[i]==' '||str[i]=='\t'||str[i]=='\n')
		{
			i++;
			continue;
		}
		
		if (isalpha(str[i]))
		{
			j=0;
			while(isalnum(str[i]))
			{
				word[j++]=str[i++];
			}
			word[j]='\0';
			if (iskeyword(word))
			{
				printf("%s: Keyword\n",word);
			}
			else
			{
				printf("%s: Identifier\n",word);
			}
			i++;
			
		}
		else if(isdigit(str[i]))
		{
			while(isdigit(str[i]))
			{
				putchar(str[i]);
				i++;
			}
			printf(":Number\n");
		}
		else if(strchr("+-*/%<>",str[i]))
		{
			printf("%c: Operator\n",str[i]);
			i++;
		}
		else if(strchr(";,{}[]",str[i]))
		{
			printf("%c Special Symbol\n",str[i]);
			i++;
		}
		else
		{
			i++;
		}
	}
}
