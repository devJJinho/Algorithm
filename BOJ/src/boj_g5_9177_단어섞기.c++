#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#define MAX 200
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.11

*난이도 : G5
*개인 풀이 시간 : 30min
*개인 난이도 : 3/5
*분류 : 재귀 / DFS / 메모이제이션
*풀이 : 2가지 방법으로 풀었다.
       재귀 수를 줄이고자 for문 안에서 분기가 필요할때만 재귀를 썼으나 결과적으로 성능이 더 나빴다.
       
*느낀점 :
        첫번째 함수 성능 : 20ms / 두번째 함수 성능 : 16ms
        입력받은 문자열 끝에 '.'를 삽입함으로써 재귀 함수에서 코드가 간결해졌다. 
        memset를 사용하기 위해선 <string.h>를 include 해야 됨.
        bfs를 사용한 풀이도 있으나 개인적으로 dp가 좋아보인다.
*/

string a,b,testCase;
bool cache[MAX+1][MAX+1];

//for문 + 재귀
bool recul_isValid(int aIndex,int bIndex,int tIndex){
    for(int i=tIndex;i<=testCase.length();i++){
        if(aIndex>=a.length()&&bIndex>=b.length()) return true;
        if(cache[aIndex][bIndex]) return false;
        cache[aIndex][bIndex]=true;
        if(aIndex>=a.length())
            if(b[bIndex]==testCase[i]){
                ++bIndex;
            }
            else return false;
        else if(bIndex>=b.length())
            if(a[aIndex]==testCase[i]){
                ++aIndex;
            }
            else return false;
        else{
            if(a[aIndex]==testCase[i]&&testCase[i]==b[bIndex]){
                bool caseA=recul_isValid(aIndex+1,bIndex,i+1);
                bool caseB=recul_isValid(aIndex,bIndex+1,i+1);
                return caseA||caseB;
            }
            else if(a[aIndex]==testCase[i]) {
                ++aIndex;
            }
            else if(b[bIndex]==testCase[i]) {
                ++bIndex;
            }
            else return false;
        }
    }
}

//for문 + 재귀 최적화
bool recul_isValid(int aIndex,int bIndex,int tIndex){
    for(int i=tIndex;i<=testCase.length();i++){
        if(i==testCase.length()) return true;
        if(cache[aIndex][bIndex]) return false;
        cache[aIndex][bIndex]=true;
            if(a[aIndex]==testCase[i]&&testCase[i]==b[bIndex]){
                bool caseA=recul_isValid(aIndex+1,bIndex,i+1);
                bool caseB=recul_isValid(aIndex,bIndex+1,i+1);
                return caseA||caseB;
            }
            else if(a[aIndex]==testCase[i]) {
                ++aIndex;
            }
            else if(b[bIndex]==testCase[i]) {
                ++bIndex;
            }
            else return false;
        }
}

//재귀
bool dp(int aIndex,int bIndex,int tIndex){
    if(tIndex==testCase.length())
        return true;
    if(cache[aIndex][bIndex]) 
        return false;
    //지금 방문하고도 결과를 못내고 다시 방문한다면 갔던 길을 또 가는 격이니 결과는 false이다.
    cache[aIndex][bIndex]=true;
    if(a[aIndex]==testCase[tIndex]&&b[bIndex]==testCase[tIndex])
        return dp(aIndex+1,bIndex,tIndex+1)||dp(aIndex,bIndex+1,tIndex+1);
    else if(a[aIndex]==testCase[tIndex])
        return dp(aIndex+1,bIndex,tIndex+1);
    else if(b[bIndex]==testCase[tIndex])
        return dp(aIndex,bIndex+1,tIndex+1);
    else 
        return false;
}

int main(){
    int num;
    cin>>num;
    for(int n=1;n<=num;n++){
        cin>>a>>b>>testCase;
        a.push_back('.');
        b.push_back('.');
        memset(cache,false,sizeof(cache));
        bool result=dp(0,0,0);
        string res=result?"yes ":"no ";
        cout<<"Data set "<<n<<": "<<res<<endl;
    }
}