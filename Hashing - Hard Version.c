/*
Given a hash table of size N, we can define a hash function H(x)=x%N. Suppose that the linear probing is used to solve collisions, we can easily obtain the status of the hash table with a given sequence of input numbers.

However, now you are asked to solve the reversed problem: reconstruct the input sequence from the given status of the hash table. Whenever there are multiple choices, the smallest number is always taken.

Input Specification:
Each input file contains one test case. For each test case, the first line contains a positive integer N (≤1000), which is the size of the hash table. The next line contains N integers, separated by a space. A negative integer represents an empty cell in the hash table. It is guaranteed that all the non-negative integers are distinct in the table.

Output Specification:
For each test case, print a line that contains the input sequence, with the numbers separated by a space. Notice that there must be no extra space at the end of each line.

Sample Input:
11
33 1 13 12 34 38 27 22 32 -1 21
Sample Output:
1 13 12 21 33 34 38 27 22 32

*/

#include<stdio.h>
#include<stdlib.h>

 
 typedef struct Node*Hash;
 struct Node{
  int key;
  int collision;
};

int N;
struct Node Array[1000];

int FindMin(){
    int i;
    int min=-1;
    int minKey;
    for(i=0;i<N;i++){
      if(Array[i].collision==0){
          int temp=Array[i].key;
              if(min==-1){
               min=i;
               minKey=temp;
              }
              else{
                 if(temp<minKey){
                     min=i;
               minKey=temp;
                 }
              }
      }
    }

    return min;
}

void CollisionChange(int index){
      int i;
      for(i=0;i<N;i++){
          if(Array[i].collision>0){
          int m=(Array[i].key)%N;
          if(m<i){
              if(index<=i&&(index>=m))
              Array[i].collision--;
          }
          if(m>i){
              if(index<=i||index>=m)
              Array[i].collision--;
          }
          }
      }
      return;
}



int main(){
    
    scanf("%d",&N);
    
    int i;
    for(i=0;i<N;i++){
        scanf("%d",&Array[i].key);
    }
int count=0;
for(i=0;i<N;i++){
    int temp=Array[i].key;
    if(temp>=0){
        count++;     //有效数字+1；
        int M=temp%N;           //记录余数
  if(M<=i){
      Array[i].collision=i-M;
  }
  else{
      Array[i].collision=i+N-M;
      }                              //记录冲突次数
    }
    else
    Array[i].collision=-1;
  }


 int h;
   int temp;
    temp=FindMin();               //在collision为0中找到最小值的index；
    h=Array[temp].key;
    printf("%d",h);            //输出最小值
    Array[temp].collision=-1;
    count--;                      //有效个数-1
    CollisionChange(temp);
    
while(count>0){                   //还有有效数没有输出时；
    temp=FindMin();
    h=Array[temp].key;
    printf(" %d",h);
    Array[temp].collision=-1;
    count--;
    CollisionChange(temp);
}
return 0;
}

