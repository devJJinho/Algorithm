#include <iostream>
#include <algorithm>
#include <stdio.h>
#define MAX 200000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.02.08

*난이도 : G5
*개인 풀이 시간 : 1hr
*개인 난이도 : 2/5
*분류 : 이분탐색
*풀이 : 
       Dp를 사용하지 않은 이유 : 배열의 크기가 너무 큼
       가능한 distance를 이분탐색으로 좁혀가며 전체에 대해 가능한지 안한지 test함.

*느낀점 : 비교적 간단하게 풀었으나 이분탐색에서 while문 조건에 등호를 넣지않아서 오답 발생
        일반 int 배열에 대해서도 std::sort()가 작동함. 대신 범위는 (시작, 마지막+1)주소

*/

int n,c;
int home[MAX+1];

bool isInstallable(int distance){
    //첫번째 라우터는 첫번째 집에 고정해두고 함.
    //정렬한 배열을 상대로 진행하기 때문에 가장 넓은 간격을 구하기 위해서 인덱스가 가장 낮은 집(정렬된 배열에서 0번째)에 하나를 두고 봐야함.
    //0번째가 아닌 다른 곳에 둔다고 했을때 가장 넓은 간격은 0번째보다 작거나 같음.
    int router=c-1;
    int pre=home[0];
    for(int i=1;i<n;i++){
        if(!router) break;
        if((home[i]-pre)>=distance) {
            pre=home[i];
            router--;
        }
    }
    if(router) return false;
    return true;
}

//이분탐색
int bs(int bottom,int ceiling){
    int res;
    while(ceiling>=bottom){
        int mid=(bottom+ceiling)/2;
        bool isPossible=isInstallable(mid);
        //가능하면 Distance를 더 늘려본다
        if(isPossible){
            res=mid;
            bottom=mid+1;
            continue;
        }
        ceiling=mid-1;
    }
    return res;
}
int main(){
    cin>>n>>c;
    int temp;
    int max=0;
    int min=1000000001;
    for(int i=0;i<n;i++){
        scanf("%d",&temp);
        if(max<temp) max=temp;
        if(min>temp) min=temp;
        home[i]=temp;
    }
    //마지막 포인터는 하나 전까지 정렬함. 때문에 len+1번째 배열의 포인터가 end임.
    //sort(&home[0],&home[n-1]);
    sort(&home[0],&home[n]);
    //집의 간격 (최대값-최소값)/(라우터 사이 간격)을 하면 가능한 최대 간격이 나온다(최상의 경우 이 값이 정답)
    //이론상 위 간격보다 더 넓은 간격이 나올 수 없음. 때문에 이것을 ceiling으로 두고 이분탐색 진행
    int res=bs(1,(max-min)/(c-1)+1);
    cout<<res<<endl;
}