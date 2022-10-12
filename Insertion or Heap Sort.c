/*
According to Wikipedia:

Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. Each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there. It repeats until no input elements remain.

Heap sort divides its input into a sorted and an unsorted region, and it iteratively shrinks the unsorted region by extracting the largest element and moving that to the sorted region. it involves the use of a heap data structure rather than a linear-time search to find the maximum.

Now given the initial sequence of integers, together with a sequence which is a result of several iterations of some sorting method, can you tell which sorting method we are using?

Input Specification:
Each input file contains one test case. For each case, the first line gives a positive integer N (≤100). Then in the next line, N integers are given as the initial sequence. The last line contains the partially sorted sequence of the N numbers. It is assumed that the target sequence is always ascending. All the numbers in a line are separated by a space.

Output Specification:
For each test case, print in the first line either "Insertion Sort" or "Heap Sort" to indicate the method used to obtain the partial result. Then run this method for one more iteration and output in the second line the resulting sequence. It is guaranteed that the answer is unique for each test case. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

Sample Input 1:
10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0
Sample Output 1:
Insertion Sort
1 2 3 5 7 8 9 4 6 0
Sample Input 2:
10
3 1 2 8 7 5 9 4 6 0
6 4 5 1 0 3 2 7 8 9
Sample Output 2:
Heap Sort
5 4 3 1 0 2 6 7 8 9
*/

#include<stdio.h>
#include<stdlib.h>

int N;
int HeapSeq[100];
int InsertSeq[100];
int Label=0;
int JudgeSeq[100];

void DeleteMin(int count){
   int tmp;
   int i;
   int max;
   int maxP;
   tmp=HeapSeq[0];
   HeapSeq[0]=HeapSeq[N-count];
   HeapSeq[N-count]=tmp;
   int Fnode=0;
   while(2*Fnode+1<(N-count)){
       maxP=2*Fnode+1;
       max=HeapSeq[maxP];
       if(2*Fnode+2<(N-count)){
         if(HeapSeq[2*Fnode+2]>max){
             maxP=2*Fnode+2;
             max=HeapSeq[maxP];
         }
       }
       if(HeapSeq[Fnode]>max){
           break;
       }
       else{
           tmp=HeapSeq[Fnode];
           HeapSeq[Fnode]=HeapSeq[maxP];
           HeapSeq[maxP]=tmp;
           Fnode=maxP;
       }

   }
    int NUM=0;
for(i=0;i<N;i++){
    if(HeapSeq[i]!=JudgeSeq[i])
    break;
    else
    NUM++;
}
if(NUM==N)
Label=2;
return;
}

void Insert(int count){
 int i;
 int tmp;
 for(i=count;i>0;i--){
     if(InsertSeq[i]<InsertSeq[i-1]){
         tmp=InsertSeq[i-1];
         InsertSeq[i-1]=InsertSeq[i];
         InsertSeq[i]=tmp;
     }
     else
     break;
 }
 int NUM=0;
for(i=0;i<N;i++){
    if(InsertSeq[i]!=JudgeSeq[i])
    break;
    else
    NUM++;
}
if(NUM==N)
Label=1;
return;
}

void BuildMax(){
    int i;
    int tmp;
    int max;
    int maxP;
    int Fnode;
    if(N%2!=0){               //最后一个父节点有两个孩子
        Fnode=(N-2)/2;     //最后一个父节点
        max=HeapSeq[N-2];
        maxP=N-2;
            if(HeapSeq[N-2]<HeapSeq[N-1]){
                max=HeapSeq[N-1];
                maxP=N-1;
            }                           //找到较大的那个子节点
            if(HeapSeq[Fnode]<max){
                tmp=HeapSeq[Fnode];
                HeapSeq[Fnode]=HeapSeq[maxP];
                HeapSeq[maxP]=tmp;
            }
        }
    else{
         Fnode=(N-2)/2;
            if(HeapSeq[Fnode]<HeapSeq[N-1]){
                tmp=HeapSeq[Fnode];
                HeapSeq[Fnode]=HeapSeq[N-1];
                HeapSeq[N-1]=tmp;
            }
}

for(i=((N-2)/2)-1;i>=0;i--){
        Fnode=i;
        while((2*Fnode+1)<N){
            max=HeapSeq[2*Fnode+1];
            maxP=2*Fnode+1;
            if(HeapSeq[2*Fnode+1]<HeapSeq[2*Fnode+2]){
                max=HeapSeq[2*Fnode+2];
                maxP=2*Fnode+2;
            }
            if(HeapSeq[Fnode]>max)
                 break;
            else{
                tmp=HeapSeq[Fnode];
                HeapSeq[Fnode]=max;
                HeapSeq[maxP]=tmp;
                Fnode=maxP;
            }
        }       
    }
return ;
}



int main(void){
    scanf("%d",&N);
    int i;
    for(i=0;i<N;i++){
     if(i==N-1)
     scanf("%d",&InsertSeq[i]);
     else
     scanf("%d ",&InsertSeq[i]);
    }

    for(i=0;i<N;i++){
      HeapSeq[i]=InsertSeq[i];
    }
    
    for(i=0;i<N;i++){
     if(i==N-1)
     scanf("%d",&JudgeSeq[i]);
     else
     scanf("%d ",&JudgeSeq[i]);
    }
    BuildMax();
    int count=1;
    while(1){
      Insert(count);
      if(Label==1)
      break;
      DeleteMin(count);
      if(Label==2)
      break;
      count++;
    }
    if(Label==1){
        Insert(count+1);
        printf("Insertion Sort\n");
        for(i=0;i<N;i++){
        if(i==N-1)
        printf("%d",InsertSeq[i]);
        else
        printf("%d ",InsertSeq[i]);
    }
    }
    else{
        DeleteMin(count+1);
        printf("Heap Sort\n");
        for(i=0;i<N;i++){
        if(i==N-1)
        printf("%d",HeapSeq[i]);
        else
        printf("%d ",HeapSeq[i]);
    }
    }
    return 0;
}

