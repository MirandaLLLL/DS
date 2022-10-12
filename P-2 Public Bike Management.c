/*
There is a public bike service in Hangzhou City which provides great convenience to the tourists from all over the world. One may rent a bike at any station and return it to any other stations in the city.

The Public Bike Management Center (PBMC) keeps monitoring the real-time capacity of all the stations. A station is said to be in perfect condition if it is exactly half-full. If a station is full or empty, PBMC will collect or send bikes to adjust the condition of that station to perfect. And more, all the stations on the way will be adjusted as well.

When a problem station is reported, PBMC will always choose the shortest path to reach that station. If there are more than one shortest path, the one that requires the least number of bikes sent from PBMC will be chosen.



The above figure illustrates an example. The stations are represented by vertices and the roads correspond to the edges. The number on an edge is the time taken to reach one end station from another. The number written inside a vertex S is the current number of bikes stored at S. Given that the maximum capacity of each station is 10. To solve the problem at S 
3
​
 , we have 2 different shortest paths:

PBMC -> S 
1
​
  -> S 
3
​
 . In this case, 4 bikes must be sent from PBMC, because we can collect 1 bike from S 
1
​
  and then take 5 bikes to S 
3
​
 , so that both stations will be in perfect conditions.

PBMC -> S 
2
​
  -> S 
3
​
 . This path requires the same time as path 1, but only 3 bikes sent from PBMC and hence is the one that will be chosen.

Input Specification:
Each input file contains one test case. For each case, the first line contains 4 numbers: C 
max
​
  (≤100), always an even number, is the maximum capacity of each station; N (≤500), the total number of stations; S 
p
​
 , the index of the problem station (the stations are numbered from 1 to N, and PBMC is represented by the vertex 0); and M, the number of roads. The second line contains N non-negative numbers C 
i
​
  (i=1,⋯,N) where each C 
i
​
  is the current number of bikes at S 
i
​
  respectively. Then M lines follow, each contains 3 numbers: S 
i
​
 , S 
j
​
 , and T 
ij
​
  which describe the time T 
ij
​
  taken to move betwen stations S 
i
​
  and S 
j
​
 . All the numbers in a line are separated by a space.

Output Specification:
For each test case, print your results in one line. First output the number of bikes that PBMC must send. Then after one space, output the path in the format: 0−>S 
1
​
 −>⋯−>S 
p
​
 . Finally after another space, output the number of bikes that we must take back to PBMC after the condition of S 
p
​
  is adjusted to perfect.

Note that if such a path is not unique, output the one that requires minimum number of bikes that we must take back to PBMC. The judge's data guarantee that such a path is unique.

Sample Input:
10 3 3 5
6 7 0
0 1 1
0 2 1
0 3 3
1 3 1
2 3 1
Sample Output:
3 0->2->3 0
*/

#include <stdio.h>
#include <math.h>
#include<string.h>
#include<stdlib.h>

int path[501][501];      //establish a matrix to store the time of each road;
int PathTime[100];       //record how much time will be taken in this path;
int stack[501];          //to store the temporary path;
int m=1;                 //to count the number of stations of this path; 
int N, Sp, Cmax,M;       //Cmax is the maximum capacity of each station; N is the total number of stations; Sp is the index of the problem station; M is the number of roads.
int PathNum=0;           //the number of the all the paths from PBMC to Sp;
int graph[501][501];     //to store all the path from PBMC to Sp;

void dfs(int p){
    int i, j;
    for(i=1;i<=N;i++){
        if(path[p][i]!=0){
            if(i==Sp){     //reach the Sp(end of the path)
                for(j=0;j<m;j++){
                    graph[PathNum][j]=stack[j];
                }
               graph[PathNum][m]=Sp;   //store this path and change into another path; 
               PathNum++;
               return ;
           }
            else{                 
                stack[m] = i;     //put this into the stack;
                m++;              //the number of this path +1;
                dfs(i);           //repeat the operation regarding i as the start;
                m--;
            }
        }
    }   
}

int CalculateTime(int index){                   // calculate the time[index];
     int i;
     int x,y;
     int judge=0;
     int time=0;
     for(i=0;i<501;i++){
         x=graph[index][i];
         y=graph[index][i+1];
         time+=path[x][y];
         if(y==Sp){                                     //the circle terminate;
          break;
     }
     }
     return time;
}

int main(void){
    int i, j;
    scanf("%d %d %d %d",&Cmax,&N,&Sp,&M);
    int C[N+1];                    //the number of bicycles in this station;
    for(i=1;i<=N;i++){             //input the current amount of bicycles of each station ;
        if(i<N)
        scanf("%d ",&C[i]);
        else
        scanf("%d",&C[i]);
    }
    
    if(N==0){
        printf("0 0 0");
    }
    else{
    for(i=0;i<=N;i++){
        for(j=0;j<=N;j++){
             path[i][j]=0;
             graph[i][j]=50000;
        }
        path[i][0]=0;           //Each path's first station is PBMC(0);
    }                            //initialize the graph and path;

    int x,y,t;
    for(i=0;i<M;i++){
        scanf("%d %d %d",&x,&y,&t);
        path[x][y]=path[x][y]=t;     //there exist a path between x and y;
    }
    x=0;
    stack[0]=0;
    dfs(0);                     //find all the paths and store them in the graph[][];

    for(i=0;i<PathNum;i++){
        PathTime[i]=CalculateTime(i);
    }                                 //Calculate each path's time and put the results into the time;
    
    int MinIndex[PathNum];                     //record the index of shortest time's path in path[][];
        MinIndex[0]=0;
    int countShort=1;                          //record how many paths take shortest time;
    for(i=1;i<PathNum;i++){                   //find the paths which take the shortest time ;
            if(PathTime[i]<PathTime[MinIndex[0]]){
                MinIndex[0]=i;
                countShort=1;
            }
            else if(PathTime[i]==PathTime[MinIndex[0]]){  //if the path cost same time as the MinIndex[0] do,put this index into the MinIndex and the number of the shortest path +1;
                MinIndex[countShort]=i;
                countShort++;
            }
        } 
    int needNum=Cmax/2-C[Sp];              //the number of bicycls of the Sp needed;   
    int SentOut[PathNum];                  //record each shortest path's number of bicycles need to be sent out from the PBMC;
    int SentBack[PathNum];                 //record each shortest path's number of bicycles need to be sent back from the PBMC;
    for(i=0;i<PathNum;i++){
        SentBack[i]=0;
        SentOut[i]=0;        
    }                                         //initialize the SentOut and the SentBack;
     
    int Temp;                                 //index of the shortest line;
    for(i=0;i<countShort;i++){                //calculate each path's number of senting out and senting back; 
        Temp=MinIndex[i];
           for(j=1;j<=N;j++){
               int tmpstation=graph[Temp][j];
               if (tmpstation!=Sp){
               if(C[tmpstation]>=(Cmax/2)){       //when the station's bicycles are more than half of the Cmax;
                 SentBack[Temp]+=(C[tmpstation]-(Cmax/2));    //the spare bicycles needed tobe sent back so the SentBack[Temp] increase;
           }
                else{                                           //when the station's bicycles are fewer than half of the Cmax;
                   if((Cmax/2-C[tmpstation])<=SentBack[Temp]){   //when current accumulated bicycles can meet this station's need
                       SentBack[Temp]-=(Cmax/2-C[tmpstation]);     //only SentBack need to decrease;
                   }
                   else{                                           //when current accumulated bicycles cannot meet this station's need
                       SentOut[Temp]+=(Cmax/2-C[tmpstation])-SentBack[Temp];  //need extra bicycles from the PBMC;
                       SentBack[Temp]=0;                                      // the sentback return to 0;
                   }
                }
               }
           else{                                                  //reach the Sp;
               if(SentBack[Temp]>=needNum){                       //when current accumulated bicycles can meet this station's need
                  SentBack[Temp]-=needNum;                        //only SentBack need to decrease;
               }
               else{                                             //when current accumulated bicycles cannot meet this station's need
                   SentOut[Temp]+=(needNum-SentBack[Temp]);      //need extra bicycles from the PBMC;
                   SentBack[Temp]=0;                             // the sentback return to 0;
               }
           break;
           }
           }
       }

       int finalIndex=MinIndex[0];                         //record the result's line's index;
       for(i=1;i<countShort;i++){                         //find the smallest sentout;
       Temp=MinIndex[i];
       if(SentOut[Temp]<SentOut[finalIndex]){
           finalIndex=Temp;
       }
       if(SentOut[Temp]==SentOut[finalIndex]){  
           if(SentBack[Temp]<SentBack[finalIndex]){    //find the smallest sentback;
               finalIndex=Temp;
           }
       }
    }

     printf("%d ",SentOut[finalIndex]);       //putput the final path's sentout;
     for(i=0;i<=N;i++){
        if(graph[finalIndex][i]!=50000){      //output the final path sequence ;     
        if(graph[finalIndex][i]!=Sp)
      printf("%d->",graph[finalIndex][i]);
      else
      printf("%d ",Sp);
    }
    else
    break;
    }
    printf("%d",SentBack[finalIndex]);        //putput the final path's sentback;
    }
    return 0;
}
