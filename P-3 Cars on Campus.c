/*
P-3 Cars on Campus
分数 20
作者 陈越
单位 浙江大学
Zhejiang University has 8 campuses and a lot of gates. From each gate we can collect the in/out times and the plate numbers of the cars crossing the gate. Now with all the information available, you are supposed to tell, at any specific time point, the number of cars parking on campus, and at the end of the day find the cars that have parked for the longest time period.

Input Specification:
Each input file contains one test case. Each case starts with two positive integers N (≤10 
4
 ), the number of records, and K (≤8×10 
4
 ) the number of queries. Then N lines follow, each gives a record in the format:

plate_number hh:mm:ss status
where plate_number is a string of 7 English capital letters or 1-digit numbers; hh:mm:ss represents the time point in a day by hour:minute:second, with the earliest time being 00:00:00 and the latest 23:59:59; and status is either in or out.

Note that all times will be within a single day. Each in record is paired with the chronologically next record for the same car provided it is an out record. Any in records that are not paired with an out record are ignored, as are out records not paired with an in record. It is guaranteed that at least one car is well paired in the input, and no car is both in and out at the same moment. Times are recorded using a 24-hour clock.

Then K lines of queries follow, each gives a time point in the format hh:mm:ss. Note: the queries are given in ascending order of the times.

Output Specification:
For each query, output in a line the total number of cars parking on campus. The last line of output is supposed to give the plate number of the car that has parked for the longest time period, and the corresponding time length. If such a car is not unique, then output all of their plate numbers in a line in alphabetical order, separated by a space.

Sample Input:
16 7
JH007BD 18:00:01 in
ZD00001 11:30:08 out
DB8888A 13:00:00 out
ZA3Q625 23:59:50 out
ZA133CH 10:23:00 in
ZD00001 04:09:59 in
JH007BD 05:09:59 in
ZA3Q625 11:42:01 out
JH007BD 05:10:33 in
ZA3Q625 06:30:50 in
JH007BD 12:23:42 out
ZA3Q625 23:55:00 in
JH007BD 12:24:23 out
ZA133CH 17:11:22 out
JH007BD 18:07:01 out
DB8888A 06:30:50 in
05:10:00
06:30:50
11:00:00
12:23:42
14:00:00
18:00:00
23:59:00
Sample Output:
1
4
5
2
1
0
1
JH007BD ZD00001 07:20:09
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


#define MAXN 10000

typedef struct Tnode *Record;
struct Tnode{
	char plat[8]; //palt number of the car
	int hh; //hour of the record
	int mm; //minute of the record
	int ss; //second of the record
	char status[4]; //'in' or 'out'
};


Record car[MAXN][MAXN]; //store the record of each car
int c=0; //count the number of cars
int recordnum[MAXN]={0}; //the number of records each car has
Record Time[MAXN]; //record the time each car has parked, units are seconds


void sort_car( int n, int a, int b ); //sort car[i]
int Compare( Record a, Record b ); //if a eariler than b, return 0; if later, return 1 

int Compare( Record a, Record b ){
	if( a->hh < b->hh ) 
		return 0;
	if( a->hh > b->hh ) 
		return 1;
	if( a->mm < b->mm ) 
		return 0;
	if( a->mm > b->mm ) 
		return 1;
	if( a->ss <= b->ss ) 
		return 0;
	if( a->ss > b->ss ) 
		return 1;
}


/*ues quick sort*/
void sort_car( int n, int a, int b ){
	int i, j;
	Record pivot=NULL;
	Record t;
	
	if(b-a<1)
		return;
	if(b-a<2){
		if( Compare(car[n][a],car[n][b])==1 ){
			t = car[n][a];
			car[n][a] = car[n][b];
			car[n][b] = t;
		}
		return;
	}
	
	/*find pivot*/
	int k=(a+b)/2;
	if( Compare( car[n][a], car[n][b] )==Compare( car[n][k], car[n][a] ) ){
		t = car[n][a];
		car[n][a] = car[n][b];
		car[n][b] = t;
	}
	else if( Compare( car[n][k], car[n][b] )==Compare( car[n][a], car[n][k] ) ){
		t = car[n][k];
		car[n][k] = car[n][b];
		car[n][b] = t;
	}
	pivot = car[n][b];
	
	i = a-1;
	j = b;
	for(;;){
		while( Compare(car[n][++i],pivot)==0 );
		while( Compare(car[n][--j],pivot)==1 );
		if(i<j){
			t = car[n][i];
			car[n][i] = car[n][j];
			car[n][j] = t;
		}
		else
			break;
	}
	t = car[n][i];
	car[n][i] = car[n][b];
	car[n][b] = t;
	sort_car( n, a, i-1 );
	sort_car( n, i+1, b);
}



int main(){
	int N, K; //N = the number of records
			  //K = the number of queries;
	int i, j, k;
	scanf("%d %d\n", &N, &K);
	
	/*get all records*/
	for(i=0; i<N; i++){
		Record R=(Record)malloc(sizeof(struct Tnode));
		scanf("%s",R->plat);
		scanf("%d:%d:%d ",&(R->hh),&(R->mm),&(R->ss));
		scanf("%s",R->status);
		for(k=0; k<c; k++){
			if( strcmp(R->plat,car[k][0]->plat)==0) //find the index of the car
				break;
		}
		if( k==c ) //this palt is not in car[][],we get a new plat
			c++;
		car[k][recordnum[k]] = R;
		recordnum[k]++;
		
	}
	
	/*find the records which have no pair and delete it*/
	for( i=0; i<c; i++){
		sort_car( i, 0, recordnum[i]-1);
	}
	for( i=0; i<c; i++){
		j = 0;
		for(j=0; j<recordnum[i]; j++){
			if( *(car[i][j]->status)=='i' ){
				if( j==recordnum[i]-1 ){
					recordnum[i]--;
					for(k=j; k<recordnum[i]; k++){
						car[i][k] = car[i][k+1];
					}
					car[i][recordnum[i]] = NULL;
				}
				else if( *(car[i][j+1]->status)=='i' ){
					recordnum[i]--;
					for(k=j; k<recordnum[i]; k++){
						car[i][k] = car[i][k+1];
					}
					car[i][recordnum[i]] = NULL;
					j--;
				}
			}
		}
		for(j=0; j<recordnum[i]; j++){
			if( *(car[i][j]->status)=='o' ){
				if( j==0 ){
					recordnum[i]--;
					for(k=j; k<recordnum[i]; k++){
						car[i][k] = car[i][k+1];
					}
					car[i][recordnum[i]] = NULL;
				}
				else if( *(car[i][j-1]->status)=='o' ){
					recordnum[i]--;
					for(k=j; k<recordnum[i]; k++){
						car[i][k] = car[i][k+1];
					}
					car[i][recordnum[i]] = NULL;
					j--;
				}
					
			}
		}
	}
	
	/*count the total number of cars parking on campus and output it*/
	for( i=0; i<K; i++){ 
		Record R=(Record)malloc(sizeof(struct Tnode)); //R store the queries
		scanf("%d:%d:%d",&(R->hh),&(R->mm),&(R->ss));
		
		int i, j;
		int s=0; //s store the number of car in the campus
		
		for(i=0; i<c; i++){
			for(j=0; j<recordnum[i]; j++){
				if( Compare(car[i][j], R)==0 ){
					if( *(car[i][j]->status)=='i' )
						s++;
					else
						s--;
				}
				else
					break;
			}
		}
		printf("%d\n",s);
	}
	
	
	/*get the time each car has parked, then find cars that has parked for the longest time period and output them*/
	for(i=0; i<c; i++){
		Time[i] = (Record)malloc(sizeof(struct Tnode));
		for(j=0; j<recordnum[i]; j+=2){
			Time[i]->hh += car[i][j+1]->hh - car[i][j]->hh;
			Time[i]->mm += car[i][j+1]->mm - car[i][j]->mm;
			Time[i]->ss += car[i][j+1]->ss - car[i][j]->ss;
			if(Time[i]->ss<0){
				Time[i]->ss += 60;
				Time[i]->mm -= 1;
			}
			if(Time[i]->mm<0){
				Time[i]->mm += 60;
				Time[i]->hh -= 1;
			}
		}
	}
	
	/*output*/
	int maxnum[MAXN], t=0; //maxnum store the index of cars we need, t store the number of cars
	Record max=Time[0];
	int temp;
	for(i=1; i<c; i++){ //find max
		if(Compare(Time[i], max)==1)
			max = Time[i];
	}
	for(i=0; i<c; i++){ //find cars
		if(Time[i]->hh==max->hh && Time[i]->mm==max->mm && Time[i]->ss==max->ss){
			maxnum[t] = i;
			t++;
		}	
	}
	for(i=0;i<t-1;i++)
	{
		for(j=0;j<t-1;j++)
		{
			if(strcmp(car[maxnum[j]][0]->plat,car[maxnum[j+1]][0]->plat)>0)
			{
				temp=maxnum[j];
				maxnum[j]=maxnum[j+1];
				maxnum[j+1]=temp;
			}
		}
	}
	
	for(i=0; i<t; i++){ //output cars
		printf("%s",car[maxnum[i]][0]->plat);
		printf(" ");
	}
	
	printf("%02d:%02d:%02d",max->hh,max->mm,max->ss);

	return 0;
}

