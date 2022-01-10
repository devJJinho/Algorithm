#include <iostream>
#include <vector>
#define MAX 100000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.01.10
*난이도 : G5
*개인 풀이 시간 : 3hour
*개인 난이도 : 3/5 
*분류 : DFS, Memoization
*풀이 : 무향 그래프에서 루트에 따라 전체 구조는 변함.
       하나의 루트에 대해 재귀를 호출하여 전체 dp를 완성하고 이후에 query에 대해선 단순 배열 접근으로 답을 출력함.
       visited 배열 대신에 자식 리스트 중 부모이면 건너띄는 방식으로 구현 => 한 노드에 대해 부모는 하나

*느낀점 : 유향 그래프처럼 들어온 정보를 무향 그래프에 맞게 양방향으로 저장하고 순회할땐 visited 배열 대신 부모 노드를 건너띄는 방식으로 구현한게 색달랐음.
    
*/

vector<int> indexList[MAX+1];
int dp[MAX+1];

int findChildNum(int root,int parent){
    int sum=1;
    for(int child:indexList[root]){
        if(child==parent) continue;
        sum+=findChildNum(child,root);
    }
    return dp[root]=sum;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int num,root,qNum;
    cin>>num>>root>>qNum;
    num--;
    while(num--){
        int from,to;
        cin>>from>>to;
        indexList[from].push_back(to);
        indexList[to].push_back(from);
    }
    findChildNum(root,-1);
    while(qNum--){
        int query;
        cin>>query;
        cout<<dp[query]<<"\n";
    }
    return 0;
}
