#include <iostream>
#include <queue>
#include <vector>
#define MAX 500
#define INF 30000000000
using namespace std;

/*

@author  :  Jinho Jeong
@date    :  2022.02.03
*난이도 : G4
*개인 풀이 시간 : 3hour
*개인 난이도 : 3/5 
*분류 : 벨만포드 
*풀이 : overflow 문제 : 사이클이 있는 경우 셈의 결과가 굉장히 커질 수 있음
       예를들어 최대 500번의 반복 동안(벨만-포드 특징) 사이클이 있다면(사이클 가중치의 최대값 = 6000(간선최대값)*10,000(간선당 최대값, 음으로도 동일))이 더해짐.
       즉 500*6000*10,000=30,000,000,000 => int 범위 초과
       
       벨만포드 알고리즘으로 풀이함.

*느낀점 : 벨만포드에 얼리스탑 개념을 구현했는데 작동함.

*/

vector<pair<int,int>> map[MAX+1];
long long costList[MAX+1];
int n,m;

bool bf(int start){
    costList[start]=0;
    bool isChanged;
    for(int i=0;i<n;i++){
        isChanged=false;
        for(int j=1;j<=n;j++){
            if(costList[j]==INF) continue;
            for(auto node:map[j]){
                int nextNode=node.first;
                int nextCost=node.second;
                if(costList[nextNode]>costList[j]+nextCost){
                    costList[nextNode]=costList[j]+nextCost;
                    isChanged=true;
                }
            }
        }
        //n-1번 전이지만 최단거리의 변화가 없는 경우 일찍 종료
        if(!isChanged) return true;
    }
    //n번 돈 뒤 변했으면 사이클 존재
    return !isChanged;
}

int main(){
    cin>>n>>m;
    for(int i=0;i<=n;i++)
        costList[i]=INF;
    for(int i=0;i<m;i++){
        int a,b,cost;
        cin>>a>>b>>cost;
        map[a].push_back({b,cost});
    }
    bool res=bf(1);
    if(!res){
        cout<<"-1"<<endl;
        return 0;
    }
    for(int i=2;i<=n;i++){
        costList[i]==INF?cout<<"-1":cout<<costList[i];
        cout<<endl;
    }
}


/*
다익스트라 코드
음수 사이클이 생기면 작동 안됨
반례 : 
4 5
1 4 3
4 2 4
2 3 -4
3 4 -2
4 3 3
답 : -1
*/

struct info{
    int to,cost;
    bool operator<(const info &b)const{
        return cost>b.cost;
    }
};

vector<pair<int,int>> map[MAX+1];
int costList[MAX+1];
int n,m;

bool dijkstra(){
    priority_queue<info> pq;
    for(auto node:map[1]){
        pq.push({node.first,node.second});
        costList[node.first]=node.second;
    }
    while(!pq.empty()){
        info cur=pq.top();
        pq.pop();
        int nowTo=cur.to;
        int nowCost=cur.cost;
        for(auto node:map[nowTo]){
            if(node.first==1&&nowCost+node.second<0) return true;
            //본인으로 돌아오는 사이클 외에도 내부적으로 사이클 하나라도 있으면 작동 안됨
            if(costList[node.first]>nowCost+node.second){
                costList[node.first]=nowCost+node.second;
                pq.push({node.first,nowCost+node.second});
            }
        }
    }
    return false;
}