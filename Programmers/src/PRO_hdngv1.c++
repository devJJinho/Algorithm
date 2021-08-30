#include <iostream>
#include <vector>
#include <set>

#define MAX 200001
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.30

*난이도 : 2/5
*개인 풀이 시간 : 1hour
*개인 난이도 : 2/5 
*분류 : 재귀+백트래킹 혹은 DFS
*풀이 : 가능한 n의 범위가 굉장히 크다. 최대값의 2차원 배열의 크기는 무려 4GB이다. (bool 기준으로 했을 때)
       재귀의 경우 깊어지긴 하지만, 배열의 포인터를 가지고 진행했을땐, 하나의 배열을 가지고 모두를 둘러볼 수 있다는 장점이 있다. 
       그리고 이전의 상태를 기억하고자 전체를 스택에 넣을 필요도 없다.
       방문했는지 체크하는 isVisited의 경우 검색이 빠른 set으로 구현했다.

*느낀점 : 재귀의 사용이 필요한 시점에 대한 감을 조금은 얻었다.
        문제의 조건을 계속 읽으며 문제에서 무엇을 요구하는지 정확히 알 필요가 있다.

*/

vector<int> tree;
vector<vector<int>> to(MAX); 
vector<int> cnt(MAX,0);
set<int> isVisited[MAX];
int n;

void recul(vector<int> &history,bool isPath[]){
    int last=history.back();
    int first=history.front();
    if(isVisited[first].find(last)==isVisited[first].end()){
        set<int> isUsed;
        for(int i:history){
            if(isUsed.find(tree[i])==isUsed.end()){
                cnt[tree[i]]++;
                isUsed.insert(tree[i]);
            }
        }
        isVisited[first].insert(last);
        isVisited[last].insert(first);
    }
    if(!to[last].size()) return;
    for(int next:to[last]){
        if(!isPath[next]){
            history.push_back(next);
            isPath[next]=true;
            recul(history,isPath);
            history.pop_back();
            isPath[next]=false;
        }
    }
}

int main(){
    cin>>n;
    tree.push_back(0);
    for(int i=0;i<n;i++){
        int temp;
        cin>>temp;
        tree.push_back(temp);
    }
    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        to[a].push_back(b);
        to[b].push_back(a);
    }
    for(int i=1;i<=n;i++){
        vector<int> his={i};
        bool isPath[MAX]={false};
        isPath[i]=true;
        recul(his,isPath);
    }
    for(int i=1;i<=n;i++)
        cout<<cnt[i]<<endl;
}


/*
5
1 2 3 4 5
1 2
2 3
3 4
3 5

답: 
5
8
10
5
5

3
1 2 1
1 2
2 3

답:
5
4
10

1
1

답: 
1
*/