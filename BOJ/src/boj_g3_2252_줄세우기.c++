#include <iostream>
#include <vector>
#include <queue>
#define MAX 32000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.08
*난이도 : G3
*개인 풀이 시간 : 20min
*개인 난이도 : 2/5 
*분류 : 위상정렬
*풀이 : 주석참고
*느낀점 : 배열 전체를 돌면서 진입차수가 0인 것을 확인하는거보다 처음에 한번 확인하고 그 다음부턴 진입차수를 하나 줄이며 0이 되면 queue에 넣는게 주요함.

*/

int cnt[MAX+1];
int N,M;
vector<int> stuOrder[MAX+1];
void func(){
    queue<int> zeroQue;
    for(int i=1;i<=N;i++){
        if(!cnt[i]) zeroQue.push(i);
    }
    while(!zeroQue.empty()){
        int sitStu=zeroQue.front();
        zeroQue.pop();
        cout<<sitStu<<" ";
        for(int behindStu:stuOrder[sitStu]){
            if(!--cnt[behindStu]) zeroQue.push(behindStu);
        }
    }
}

int main(){
    cin>>N>>M;
    int a,b;
    while(M--){
        scanf("%d %d",&a,&b);
        ++cnt[b];
        stuOrder[a].push_back(b);
    }
    func();
}