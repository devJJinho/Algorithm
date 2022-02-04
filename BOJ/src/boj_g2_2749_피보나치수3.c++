#include <iostream>
#define MOD 1000000
typedef unsigned long long ull;
using namespace std;

/*
 
@author  :  Jinho Jeong
@date    :  2022.02.04

*난이도 : G2
*개인 풀이 시간 : 30min
*개인 난이도 : 2/5
*분류 : 수학, 모듈러 연산, 피보나치 수열
*풀이 : 피보나치 수열의 모둘러 연산은 주기가 있음.
       점화식이 fn=fn-1+fn-2, 그리고 모듈러 연산은 분배법칙이 성립함 mod(fn)=mod(fn-1)+mod(fn-1) => mod한 결과를 유지하면 됨
       점화식에 의해 현재 항에 영향을 주는 항은 직전 두개의 항임, 직전 두개항만 유지하고 두 항이 각각 1,1일때 Fn은 2가 나올 수 밖에 없음 => 주기 발생

       백준 9471_피사노주기를 참조

       패턴을 찾은 뒤에 n을 패턴 길이로 모듈러 연산을 하고 해당 수까지 피보나치를 수를 찾아감. 직전 2개 수만 유지하기 때문에 메모리 절약
    
*느낀점 : 
        
*/

ull findPattern(){
    ull i;
    int modFibo[2]={1,1};
    for(i=3;i<=1000000000000;i++){
        int curFibo=(modFibo[0]+modFibo[1])%MOD;
        modFibo[0]=modFibo[1];
        modFibo[1]=curFibo;
        if(modFibo[0]==1&&modFibo[1]==1)
            break;
    }
    return i-2;
}

int main(){
    ull n;
    cin>>n;
    //패턴길이 찾기
    ull patLen=findPattern();
    n%=patLen;
    int res;
    if(n==0) res=0;
    else if(n==1) res=1;
    else{
        int modFibo[2]={1,1};
        for(int i=2;i<=n-1;i++){
            int curFibo=(modFibo[0]+modFibo[1])%MOD;
            modFibo[0]=modFibo[1];
            modFibo[1]=curFibo;
        }
        res=modFibo[1];
    }
    //패턴길이로 모듈러 하면서 n만큼 진행하기 => 배열 필요 없음
    cout<<res<<endl;
}