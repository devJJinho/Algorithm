#include <iostream>
#include <queue>
#include <string>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.28

*난이도 : ? (카카오 블라인드 문제 중 하나)
*개인 풀이 시간 : 20min
*개인 난이도 : 2/5
*분류 : BFS
*풀이 : 조건에 따라 만든 3가지 경우를 queue에 담아서 BFS를 실행했다.
       queue에서 가져온 값이 패턴보다 길면 해당 값은 더이상 가능성이 없기 때문에 continue => queue의 크기가 제어 가능하다.

*느낀점 : 첫문제에 시간을 너무 쓴 나머지 풀 생각 조차 못했다. 아쉬울 뿐이다.
        
*/

bool findPattern(string pat){
    queue<string> q;
    q.push("a");

    while(!q.empty()){
        string cur=q.front();
        cout<<cur<<endl;
        q.pop();
        if(cur==pat)
            return true;
        if(cur.length()>=pat.length()) continue; 
        int cnt=0;
        for(int i=0;i<cur.length();i++)
            if(cur[i]=='a')cnt++;
        //#1
        string required;
        for(int i=0;i<cnt;i++)
            required.push_back('b');
        string next1=required;
        next1+=cur+required;
        q.push(next1);
        //#2
        string next2="a";
        next2+=cur;
        //#3
        string next3=cur;
        next3.push_back('a');
        q.push(next2);
        if(next2!=next3)
            q.push(next3);
    }
    return false;
}
int main(){
    string test1="abab";
    cout<<findPattern(test1)<<endl;
    return 0;
}