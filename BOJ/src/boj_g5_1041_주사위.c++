#include <iostream>
#define END(a) cout<<a<<endl;
#define INF 500
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.07

*난이도 : G5
*개인 풀이 시간 : 2hr
*개인 난이도 : 2/5
*분류 : 구현, 수학 그리디
*풀이 : 
     간단한 수학 문제이다. 
     3개면 최소값, 2개면 최소값, 주사위 최소값을 구한뒤 그것을 활요하여 전체 정육면제를 구현하면 된다
     다만 5개 면만 고려하기 때문에 조금의 더 생각이 필요하다.
     그리고 수가 int 범위를 초과하기 때문에 long long으로 캐스팅도 해야된다.

*느낀점 :
       문제의 조건을 잘 확인하자.
       최대값과 최소값에 대한 대비를 철저히 해야된다.
       히든 케이스에 대비하기 위해선 스스로 테케를 만들어 확인하는 습관을 들여야한다. 

*/

int dice[7]={0,};

pair<int,int> findMin(){
    int twoMin,threeMin;
    twoMin=threeMin=INF;
    for(int d=1;d<=6;d++){
        for(int i=1;i<=6;i++){
            //7-i가 맞은편이다. 따라서 d와 같지 않고 d의 맞은편도 아닌 경우 선택
            if(i==d||i==7-d) continue;
            twoMin=min(twoMin,dice[d]+dice[i]);
            for(int j=1;j<=6;j++){
                //세번째 선택은 두번째 선택의 조건에 (두번재 선택과 중복X, 두번째 선택과 맞은편 아님)을 만족해야됨
                if(j==d||j==7-i||j==7-d||j==i) continue;
                threeMin=min(threeMin,dice[d]+dice[i]+dice[j]);
            }
        }
    }
    return {twoMin,threeMin};
}
long long calSum(int one,int two,int three,int n){
    long long sum=0;
    sum+=three*4;
    sum+=two*(n-2)*4;
    sum+=two*(n-1)*4;
    //(long long 캐스팅이 없으면 Int 오버플로우가 난다 주의해야됨!!)
    sum+=(long long)one*(n-2)*(n-2);
    sum+=(long long)one*(n-1)*(n-2)*4;
    return sum;
}
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=6;i++)
        cin>>dice[i];
    if(n==0) {END(0); return 0;}
    //주사위가 하나일 때, 최대값만 제외하고 다 더한다. (최대값이 바닥으로)
    if(n==1) {
        int sum=0;
        int m=0;
        for(int i=1;i<=6;i++){
            m=max(m,dice[i]);
            sum+=dice[i];
        }
        END(sum-m);
        return 0;
    }
    pair<int,int> m=findMin();
    int one=INF;
    for(int i=1;i<=6;i++)
        one=min(one,dice[i]);
    END(calSum(one,m.first,m.second,n));
    return 0;
}