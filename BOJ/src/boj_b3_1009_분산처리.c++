#include <iostream>
#include <vector>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.05

*난이도 : B3
*개인 풀이 시간 : 1hour 20min 
*개인 난이도 : 2/5 
*분류 : 배열의 이해, 정수론
*풀이 : 자연수 a의 n승의 일의자리수는 반복된다. mod10의 결과 0~9와 a를 곱하면 일의자리에 영향을 미치는 것은 결국 a의 일의자리수이다. 
       때문에 가능한 패턴은 최대 4자리이다.
       그것을 이용해서 패턴을 찾고 패턴으로 모듈러 한 결과를 출력한다.
       다만 mod의 결과가 0인 경우 컴퓨터 번호로는 10번이다. 
    
*느낀점 : 문제를 잘 읽고 풀이하자.

*/


int main(){
    int n;
    cin>>n;
    while(n--){
        int a,b;
        cin>>a>>b;
        vector<int> pat={a%10};
        while(pat.size()<=b){
            int t=pat.back();
            t*=a;
            t%=10;
            if(t==pat[0]) break;
            pat.push_back(t);
        }
        cout<<(pat[(b-1)%pat.size()]?pat[(b-1)%pat.size()]:10)<<endl;
    }
}