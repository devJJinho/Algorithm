#include <iostream>
#define MAX 40000

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.26

*난이도 : G2
*개인 풀이 시간 : 1hour
*개인 난이도 : 2/5 
*분류 : LIS(N logN), 이분탐색
*풀이 : N logN 시간복잡도를 가지는 LIS로 풀어야하는 문제.
       
*느낀점 : 
       LIS 생성 과정중에 생기는 배열은 실제 LIS랑 다르다는게 인상적. 그렇다면 실제 LIS 구성요소를 아는 방법에 Log N 방법은 없는지?
*/

int semi[MAX+1];
int tie[MAX+1];
int index;
int N;

int lowerBound(int v){
    int bottom=0;
    int ceiling=index;
    int res=0;
    //같은게 있다면 그 중 가장 작은것, 아니라면 본인보다 큰 값이 있는 곳 return
    while(bottom<=ceiling){
        int mid=(bottom+ceiling)/2;
        //본인보다 같거나 큰게 발견되면 일단 Res에 담고 ceiling을 줄임
        //다시 이 조건을 만족하지 않는다 = 같거나 큰 값이 없다 => 위에서 저장한 Res값 return
        //아니라면 줄인 범위에서 다시 같은 일을 반복
        if(tie[mid]>=v){
            ceiling=mid-1;
            res=mid;
        }
        else{
            bottom=mid+1;
        }
    }
    return res;
}

int main(){
    cin>>N;
    for(int i=0;i<N;i++){
        scanf("%d",&semi[i]);
    }
    tie[index++]=semi[0];
    for(int i=1;i<N;i++){
        //만약 가장 뒤 값보다 크다면 바로 삽입
        if(tie[index-1]<semi[i]){
            tie[index++]=semi[i];
            continue;
        }
        //아니라면 LowerBound를 찾아서 해당 위치에 삽입
        tie[lowerBound(semi[i])]=semi[i];
    }
    printf("%d\n",index);
}