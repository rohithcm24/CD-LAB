#include<stdio.h>
#include<stdlib.h>
int k,states,terminals,closure[100][100][100],visited[100],visited1[100],cls[100][100],temp[100];
void epsilon_closure(int n)
{
	int i,j;
	for(j=0;closure[n][0][j]!=-1&&visited[closure[n][0][j]]==0;j++)
	{
		if(visited[closure[n][0][j]]!=1)
        {
			printf("Q%d ",closure[n][0][j]);
            temp[k++]=closure[n][0][j];
        }    
		visited[closure[n][0][j]]=1;
		epsilon_closure(closure[n][0][j]);
	}	
}
void state_closure(int n,int i)
{
	int j;
	for(j=0;closure[n][i][j]!=-1;j++)
	{  
		visited1[closure[n][i][j]]=1;
	}	
}
int main()
{
	int i,j,n,l;
	printf("ENTER NUMBER OF STATES:");
	scanf("%d",&states);
	printf("\nENTER NUMBER OF TERMINALS:");
	scanf("%d",&terminals);
	for(i=0;i<states;i++)
	{
		printf("\nEnter the transitions for state:Q%d\n",i);
		for(j=0;j<terminals;j++)
		{
			printf("\nHow many transitions for Q%d By accepting %d:",i,j);
			scanf("%d",&n);
			for(k=0;k<n;k++)
			{
				printf("\nEnter the state reached by accepting %d  for Q%d:",j,i);
				scanf("%d",&closure[i][j][k]);
			}
			for(k=n;k<states;k++)
			{
				closure[i][j][k]=-1;
			}
		}
	}	
	printf("\nTransition Table:\n");
	for(i=0;i<states;i++)
	{
		for(j=0;j<terminals;j++)
		{
			printf("\nQ%d accepting %d moves to:",i,j);
			for(k=0;closure[i][j][k]!=-1;k++)
			{
				printf("Q%d ",closure[i][j][k]);	
			}	
		}
	}
	for(i=0;i<states;i++)
	{
        k=1;
		printf("\nEpsilon transition of state Q%d:Q%d ",i,i);
		for(j=0;j<states;j++)
			visited[j]=0;
		visited[i]=1;
		epsilon_closure(i);
		cls[i][0]=i;
        for(j=1;j<k;j++)
        {
			cls[i][j]=temp[j];
		}			
		cls[i][k]=-1;
	}
	for(i=0;i<states;i++)
	{
		printf("\n\nTransition of Q%d:\n",i);
		for(j=1;j<terminals;j++)
		{
			printf("\nAccepting %d:",j);
			for(k=0;k<states;k++)
				visited1[k]=0;
			for(k=0;cls[i][k]!=-1;k++)
			{
				state_closure(cls[i][k],j);
			}
			for(k=0;k<states;k++)
				visited[k]=0;
			for(k=0;k<states;k++)
			{
				if(visited1[k]!=0)
				{
					visited[k]=1;
					epsilon_closure(k);
				}
			}
			for(k=0;k<states;k++)
			{
				if(visited[k]!=0)
				{
					printf("Q%d ",k);
				}
			}
		}
	}
	return 0;
}
