#include <iostream>

#define MAX 1000000000000

using namespace std;

/*
 
@author  :  Jinho Jeong
@date    :  2022.02.04

*난이도 : Silver 4
*개인 풀이 시간 : 30min
*개인 난이도 : 2/5
*분류 : 수학, 모듈러 연산, 피보나치 수열
*풀이 : 피보나치 수열의 모둘러 연산은 주기가 있음.
       점화식이 fn=fn-1+fn-2, 그리고 모듈러 연산은 분배법칙이 성립함 mod(fn)=mod(fn-1)+mod(fn-1) => mod한 결과를 유지하면 됨
       점화식에 의해 현재 항에 영향을 주는 항은 직전 두개의 항임, 직전 두개항만 유지하고 두 항이 각각 1,1일때 Fn은 2가 나올 수 밖에 없음 => 주기 발생
    
*느낀점 : 피보나치가 주기가 있는 줄 몰랐음. 주기가 있다는 것을 모른다면 관련 문제 풀기가 까다로울듯
        
*/

int main(){
    int n;
    cin>>n;
    for(int cs=1;cs<=n;cs++){
        int temp,mod;
        cin>>temp>>mod;
        int modFibo[2]={1,1};
        int i;
        for(i=3;i<=MAX;i++){
            int curFibo=(modFibo[0]+modFibo[1])%mod;
            modFibo[0]=modFibo[1];
            modFibo[1]=curFibo;
            if(i!=3&&modFibo[0]==1&&modFibo[1]==1)
                break;
        }
        cout<<cs<<" "<<i-2<<endl;
    }
}