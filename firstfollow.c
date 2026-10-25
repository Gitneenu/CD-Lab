#include <stdio.h>
#include <string.h>

#define MAX 20
int n,m,change=0;
char p[MAX][MAX],nt[MAX],c;
int A,B,C,nullable;
char first[MAX][MAX],follow[MAX][MAX];

int fc[MAX],foc[MAX];



int NT(char c)
{
	if (c >='A' && c<='Z')
	{
		return 1;
	}
	return 0;
}

int indexNT(char c)
{
	for(int i=0;i<m;i++)
	{
		if(nt[i]==c)
		{
			return i;
		}
	}
	return -1;	
}

int contains(char set[MAX],int count,char c)
{
	for(int i=0;i<count;i++)
	{
		if(set[i]==c)
		{
			return 1;
		}
	}
	return 0;
}

int add(char set[][MAX],int count[MAX],int pos,char c)
{
	if (contains(set[pos],count[pos],c))
	{
		return 0;
	}
	set[pos][count[pos]++]=c;
	return 1;
}

void findfirst()
{
	do{
		change=0;
		for(int i=0;i<n;i++)
		{
			A=indexNT(p[i][0]);
			
			if (strcmp(p[i]+2,"#")==0)
			{
				change |= add(first,fc,A,'#');
				continue;
			}
			nullable=1;
			for(int j=2;p[i][j] != '\0';j++)
			{
				c=p[i][j];
				if (!NT(c))
				{
					change|=add(first,fc,A,c);
					nullable=0;
					break;
				}
				B=indexNT(c);
				for(int k=0;k<fc[B];k++)
				{
					if (first[B][k]!='#')
					{
						change|=add(first,fc,A,first[B][k]);
					}
				}
				
				if (!contains(first[B],fc[B],'#'))
				{
					nullable=0;
					break;
				}
				
			}
			if(nullable)
			{
				change|=add(first,fc,A,'#');
			}
		}
	}while(change);
}

void findfollow()
{
	add(follow,foc,0,'$');
	do
	{
		change=0;
		for(int i=0;i<n;i++)
		{
			A=indexNT(p[i][0]);
			
			for(int j=2;p[i][j]!='\0';j++)
			{
				if(!NT(p[i][j]))
				{
					continue;
				}
				B=indexNT(p[i][j]);
				nullable=1;
				for(int k=j+1;p[i][k]!='\0';k++)
				{
					c=p[i][k];
					if(c=='#')
					{
						break;
					}
					if(!NT(c))
					{
						change|=add(follow,foc,B,c);
						nullable=0;
						break;
					}
					C=indexNT(c);
					for(int a=0;a<fc[C];a++)
					{
						if (first[C][a]!='#')
						{
							change|=add(follow,foc,B,first[C][a]);
						}
					}
					if (!contains(first[C],fc[C],'#'))
					{
						nullable=0;
						break;
					}					
				}
				if (nullable)
				{
					for(int a=0;a<foc[A];a++)
					{
						change|=add(follow,foc,B,follow[A][a]);
					}
				}	
			}
		}
	}while(change);
}

void main()
{
	printf("Enter number of productions\n");
	scanf("%d",&n);
	
	for(int i=0;i<n;i++)
	{
		scanf("%s",p[i]);
	}
	
	for(int i=0;i<n;i++)
	{
		if(indexNT(p[i][0])==-1)
		{
			nt[m++]=p[i][0];
		}
	}
	
	findfirst();
	findfollow();
	
	for(int i=0;i<m;i++)
	{
		printf("FIRST(%c) = {",nt[i]);
		for(int j=0;j<fc[i];j++)
		{
			printf("%c ",first[i][j]);
		}
		printf("}");
	}
	
		for(int i=0;i<m;i++)
	{
		printf("FOLLOW(%c) = {",nt[i]);
		for(int j=0;j<foc[i];j++)
		{
			printf("%c ",follow[i][j]);
		}
		printf("}");
	}
	
}
