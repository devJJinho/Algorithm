#include <iostream>
#include <queue>
#include <cmath>
#define MAX 1000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.02.15

*난이도 : g3    
*개인 풀이 시간 : 1.5hour
*개인 난이도 : 2/5 
*분류 : union-find
*풀이 : 주어진 간선에선 cycle이 있을수도 있기 때문에 남은 간선 중에서 cycle이 없게끔 최소값 순으로 더함.
*느낀점 : m개의 노드에선 m-1개의 간선으로 모두 연결할 수 있긴 하지만 주어진 조건에서 몇개의 가
*/
ㅁ
pair<int,int> coor[MAX+1];
bool isSelected[MAX+1];
struct info{
    double distance;
    int a,b;
    bool operator>(const info &b) const{
        return distance>b.distance;
    }
};
int parent[MAX+1];
priority_queue<info,vector<info>,greater<info>> pq;
int findParent(int n){
    if(parent[n]==n) return n;
    return parent[n]=findParent(parent[n]);
}
double getDistance(int a,int b){
   double x=coor[a].first-coor[b].first;
   double y=coor[a].second-coor[b].second;
   return sqrt(pow(x,2)+pow(y,2));
}
void unionParent(int a, int b){
    a=findParent(a);
    b=findParent(b);
    if(b>a) parent[b]=a;
    else parent[a]=b;
}

 int main(){
     int n,m;
     cin>>n>>m;
     for(int i=1;i<=n;i++){
         int a,b;
         cin>>a>>b;
         coor[i]={a,b};
         parent[i]=i;
     }
     for(int i=0;i<m;i++){
         int a,b;
         cin>>a>>b;
         isSelected[a]=isSelected[b]=true;
         unionParent(a,b);
     }
    for(int i=1;i<=n-1;i++){
        for(int j=i+1;j<=n;j++){
            pq.push({getDistance(i,j),i,j});
        }
    }
    //주어진 간선으로 생긴 집단의 수를 체크
    //여러개의 노드가 하나의 집단으로 뭉친 경우 하나의 경우만 parent[i]==i이기 떄문에 하나로 인식, 그리고 union된 적이 없는 경우에도 parent[i]==i이기 때문에 하나로 count
    int groupCnt=0;
    for(int i=1;i<=n;i++){
        if(parent[i]==i) groupCnt++;
    }
    double sum=0;
    --groupCnt;
    while(groupCnt){
        auto cur=pq.top();
        pq.pop();
        int a=findParent(cur.a);
        int b=findParent(cur.b);
        if(a==b) continue;
        if(a>b)
            parent[a]=b;
        else
            parent[b]=a;
        sum+=cur.distance;
        groupCnt--;
    }
    printf("%.2f\n",(double)round(sum*100)/100);
 }



pair<int,int> coor[MAX+1];
struct info{
    double distance;
    int a,b;
    bool operator>(const info &b) const{
        return distance>b.distance;
    }
};
int parent[MAX+1];
priority_queue<info,vector<info>,greater<info>> pq;
int findParent(int n){
    if(parent[n]==n) return n;
    return parent[n]=findParent(parent[n]);
}
double getDistance(int a,int b){
   double x=coor[a].first-coor[b].first;
   double y=coor[a].second-coor[b].second;
   return sqrt(pow(x,2)+pow(y,2));
}
void unionParent(int a, int b){
    a=findParent(a);
    b=findParent(b);
    if(b>a) parent[b]=a;
    else parent[a]=b;
}

 int main(){
     int n,m;
     cin>>n>>m;
     for(int i=1;i<=n;i++){
         int a,b;
         cin>>a>>b;
         coor[i]={a,b};
         parent[i]=i;
     }
     for(int i=0;i<m;i++){
         int a,b;
         cin>>a>>b;
         //주어진 간선에 대해선 union-find 수행
         unionParent(a,b);
     }
    for(int i=1;i<=n-1;i++){
        //양방향 그래프이기 때문에 j=i+1으로 하는게 중복을 막음
        for(int j=i+1;j<=n;j++){
            pq.push({getDistance(i,j),i,j});
        }
    }
    double sum=0;
    //priority_queue로 최소값만 찾기 때문에 효율적
    //pq 안에는 가능한 모든 간선이 있고 union-find 결과가 같으면(이미 연결되어 있으면) continue;
    //만약 다른 집단이라면 연결
    //가능한 모든 간선이 비워질때까지 수행
    //n개의 노드에 대해 n-1개의 간선을 사이클 없이 두면 mst가 완성되기 하지만 이미 주어진 간선이 cycle이 없다는 보장이 없기 때문에 선택할 간선을 계산 할 수 없음
    //다만 가능한 간선에서 가장 작은 순으로 union-find의 결과가 다를때 부모를 같게 하는 과정만 연달아 수행함.
    while(!pq.empty()){
        auto cur=pq.top();
        pq.pop();
        int a=findParent(cur.a);
        int b=findParent(cur.b);
        if(a==b) continue;
        if(a>b)
            parent[a]=b;
        else
            parent[b]=a;
        sum+=cur.distance;
    }
    printf("%.2f\n",(double)round(sum*100)/100);
 }