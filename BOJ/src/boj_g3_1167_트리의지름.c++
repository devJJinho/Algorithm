#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.10.03

*난이도 : G3
*개인 풀이 시간 : 2hr
*개인 난이도 : 2/5 
*분류 : 수학, 재귀(DFS)
*풀이 : 트리의 지름은 '임의의 점에서 가장 먼 점을 찾고, 그 점에서 가장 먼 점 사이의 거리이다' 
       이것을 코드로 구현했다. 가장 먼 점을 찾기 위해서 임의의 한 점에서 DFS로 가장 먼 점을 찾는 재귀 함수를 구현했다.
       
       가장 먼 두 점을 잡고 당겼을때 두 점이 팽팽해지고 그것을 지름으로 본다. 임의의 두 점은 그 지름 안의 위치할 것이고 그것에서 가장 먼 점은 지름을 이루는 두 점 중에 하나일 것이다.
       그렇게 한 점을 찾고 그 점에서 가장 먼 점을 구하면 지름을 가로질러 반대 점으로 갈 것이다. 
       자세한 증명은 귀류법을 사용하면 된다. 가장 먼 점 (x,y)일때 임의의 점 (a,b)의 각각의 경우를 증명하면 된다.

*느낀점 : 전체 범위에 대해서 dfs 했을땐 시간 초과가 걸렸다. 이런 문제는 이런 아이디어가 없으면 풀기 어렵다. 많이 풀어보는 수 밖에 없겠다.

*/

vector<vector<pair<int,int>>> tree(100001);
bool isVisited[100001];
int n,maxPath,nIndex;
void recul(int start,int sum,int depth){
    if(sum>maxPath) {
        maxPath=sum;
        nIndex=start;
    }
    if(depth==n) return;
    for(auto cur:tree[start]){
        int next=cur.first;
        if(isVisited[next]) continue;
        isVisited[next]=true;
        recul(cur.first,sum+cur.second,depth+1);
        isVisited[next]=false;
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int index,temp1,temp2;
        cin>>index;
        while(true){
            cin>>temp1;
            if(temp1==-1) break;
            cin>>temp2;
            tree[index].push_back({temp1,temp2});
        }
    }
    isVisited[1]=true;
    recul(1,0,0);
    isVisited[1]=false;
    isVisited[nIndex]=true;
    maxPath=0;
    recul(nIndex,0,0);
    cout<<maxPath<<endl;
}