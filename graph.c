#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
#define initial 1 
#define waiting 2
#define visited 3
int adj[MAX][MAX];
int state[MAX],queue[MAX],front=-1,rear=-1,dindex=0,d=0;
int n,v,x;
char city[MAX][20];char scc[20];char dc[20];
void creategraph();
void BF_Traversal();
void DF_Traversal();
void BFS(int v);
void DFS(int v);
void insert_queue(int vertex);
int delete_queue();
int isEmpty_queue();
void search();
void dfssearch(int d);
void main()
{
      // clrscr();
       creategraph();
       getch();
}
void creategraph()
{
      int max_edge,i,j,origin,dest,graph_type,choice;
      printf("\n Enter 1. for undirected graph \n Enter 2.for directed graph ");
      printf("\n Enter your choice");
      scanf("%d",&graph_type);
      printf("\n Enter no. of vertices ");
      scanf("%d",&n);
      for(i=0;i<n;i++)
      {
           printf("\n Enter city at vertex %d ",i);
           scanf("%s",city[i]);
       }
       if(graph_type==1)
           max_edge=n*(n-1)/2;
       else
           max_edge=n*(n-1);
       for(i=0;i<max_edge;i++)
       {
            printf("\n Enter edge %d in index form (-1 -1 to quit): ",i);
            scanf("%d %d",&origin,&dest);
            if((origin==-1)&&(dest==-1))
                  break;
            if(origin>n||dest>n||origin<0||dest<0)
            {
                printf("\n Invalid vertex");
                i--;
             }
             else
             {
                   adj[origin][dest]=1;
                   if(graph_type==1)
                        adj[dest][origin]=1;
             }
        }
        printf("\n 1.BFS");
        printf("\n 2.DFS");
        printf("\n 3.path search");
        printf("\n Enter your choice");
        scanf("%d",&choice);
        switch(choice)
        {
             case 1:     BF_Traversal();
                         break;
             case 2:     DF_Traversal();
                         break;
             case 3:     search();
                         break;
             default:    printf("\n wrong choice");
                         break;
        }
}
void BF_Traversal()
{
     for(v=0;v<n;v++)
          state[v]=0;
     printf("\n Enter start vertex in index form ");
     scanf("%d",&v); 
     BFS(v);
}
void BFS(int v)
{
     int i;int co=0;
     insert_queue(v);
     state[v]=waiting;
     while(!isEmpty_queue())
     {
           if(co==n)
               break;
           v=delete_queue();
           strcpy(scc,city[v]);
           printf("%s ",scc);
           co++;
           state[v]=visited;
           for(i=0;i<n;i++)
           {
                if(adj[v][i]==1&&state[i]!=3)
                {
                     insert_queue(i);
                     state[i]=waiting;
                }
           }
      }
}
void insert_queue(int vertex)
{
      if(rear==MAX-1)
         printf(" queue overflow");
      else
      {
         if(front==-1)
             front=0;
         rear=rear+1;
         queue[rear]=vertex;
      }
}
int isEmpty_queue()
{
     if(front==-1&&front>rear)
           return 1;
     else
           return 0;
}
int delete_queue()
{
      int delete_item;
      if(front==-1&&front>rear)
      {
            printf(" queue underflow");
            exit(1);
      }
      delete_item=queue[front];
      front=front+1;
      return delete_item;
}
void DF_Traversal()
{
     for(v=0;v<n;v++)
         state[v]=0;
     printf("\n Enter start vertex in index form ");
     scanf("%d",&v);
     DFS(v);
}
void DFS(int v)
{
    int i;
    strcpy(scc,city[v]);
    printf("%s ",scc);
    state[v]=1;
    for(i=0;i<n;i++)
    {
       if(state[i]!=1&&adj[v][i]==1)
           DFS(i);
    }
}
void search()
{
     int i;
        for(d=0;d<n;d++)
           state[d]=0;
        printf("\n Enter source city ");
        scanf("%s",scc);
        for(i=0;i<n;i++)
        {
            x=strcmp(scc,city[i]);
            if(x==0)
                d=i;
        }

        printf("\n Enter destination city ");
        scanf("%s",dc);
        for(i=0;i<n;i++)
        {
            x=strcmp(dc,city[i]);
            if(x==0)
                dindex=i;
        }
        dfssearch(d);
}
void dfssearch(int d)
{
     int i;
     state[d]=1;
     for(i=0;i<n;i++)
     {
         if(state[i]!=1&&adj[d][i]==1)
         {
             if(i==dindex)
             {
                 printf("\n path exists");
             }
             else
                 dfssearch(i);
             break;
         }
     }
}