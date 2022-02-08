#include <iostream>
#define MAX 400
#define MAX_LEN 4000001
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.01.11
*난이도 : G4
*개인 풀이 시간 : 1hour
*개인 난이도 : 2/5 
*분류 : 플로이드 와샬
*풀이 : 정점 하나에 대해서 사이클을 찾는 코드를 생각함. 하지만 반복되는 계산이 많아서 시간 초과 발생함.
       플로이드 와샬은 O(n^3)이지만 v가 최대 400개 인 상황에선 충분히 사용가능한 코드임.

*느낀점 : 트리와 그래프 그리고 순회 방법을 숙지할 필요가 있음.
        MAX값은 사이클이 있는 그래프를 찾기 때문에(플로이드 와샬에서 i==j일때 처리를 따로 하지 않음) 총 n개의 간선이 쓰일 수 있음 때문에 간선최대값(400)*가중치최대값(10000)+1
    
*/

int bridge[MAX+1][MAX+1];

int main(){
    int v,e;
    cin>>v>>e;
    for(int i=0;i<=v;i++)
        for(int j=0;j<=v;j++)
            bridge[i][j]=MAX_LEN;
    while(e--){
        int from,to,len;
        cin>>from>>to>>len;
        bridge[from][to]=len;
    }
    //floyd warshall
    for(int m=1;m<=v;m++){ 
        for(int a=1;a<=v;a++){
            for(int b=1;b<=v;b++){
                int bypass=bridge[a][m]+bridge[m][b];
                if(bridge[a][b]>bypass)
                    bridge[a][b]=bypass;
            }
        }
    }
    int minLen=MAX_LEN;
    for(int i=1;i<=v;i++){
        if(bridge[i][i]<minLen) minLen=bridge[i][i];
    }
    cout<<(minLen==MAX_LEN?-1:minLen)<<endl;
}

// 정점 하나에 대해서 사이클을 검사하는 코드, 시간 초과 발생.
/*
#include <iostream>
#include <vector>
#define MAX 400
#define MAX_LEN 4000000
using namespace std;
int minLen=MAX_LEN;
vector<pair<int,int>> bridge[MAX+1];

void dfs(int curNode,int parent,int sum){
    //사이클이 확인되면 거리의 합을 업데이트
    if(curNode==parent){
        if(sum<minLen) minLen=sum;
        return;
    }
    for(pair nNode:bridge[curNode]){
        int value=sum+nNode.second;
        //현재 최소 거리보다 줄어들 가능성이 없으면 dfs 진행 중단.
        if(value>=minLen) continue;
        dfs(nNode.first,parent,value);
    } 
}

int main(){
 int v,e;
 cin>>v>>e;
 while(e--){
     int from,to,len;
     cin>>from>>to>>len;
     bridge[from].push_back({to,len});
 }
 for(int index=1;index<=v;index++){
    for(pair node:bridge[index]){
        dfs(node.first,index,node.second);
    }
 }
 cout<<(minLen==MAX_LEN?-1:minLen)<<endl;
 return 0;
}
*/