#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#define ABS(a,b) (a-b<0?(a-b)*-1:a-b) 
#define MAX 100000

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.07.19

*난이도 : G1
*개인 풀이 시간 : 1hour 
*개인 난이도 : 2/5 
*분류 : Kruskal 알고리즘(MST를 최소값부터 담아가며 만드는 것), 그래프, 최소신장트리, Union-Find
*풀이 : 모든 엣지에 대해서 담아두고 시작은 하지 못한다. 100000^2의 메모리 복잡도를 가진다. 대략 60GB
       대신 거리의 기준이 축간 거리 중 최소이기 때문에 가능한 간선은 x,y,z 각각 오름차순으로 정렬하고 그 사이값들의 집합이다.
       가능한 간선의 최소값부터 담으며 union-find 체크를 하고 사이클을 형성하는 간선은 무시하고 넘어간다.
       선택한 간선의 개수가 n-1이면 사이클 없는 최소신장트리가 완성되었기 때문에 끝낸다.

*느낀점 : 간선의 길이가 n-1이란 것에서 최소신장트리임을 알아차렸으나 dp문제일것이라는 잘못된 힌트에 빠져 다른 경우를 전혀 생각하지 못했다.
        문제 풀이의 방향을 정하는 나만의 기준과 철학이 필요하다.
*/

int parent[MAX];
vector<tuple<int,int,int>> map;
vector<pair<int,int>> x,y,z;
vector<tuple<int,int,int>> edge;
int n;

int getParent(int paren){
    if(parent[paren]==paren){
        return paren;
    }
    return parent[paren]=getParent(parent[paren]);
}

bool changeParent(int a,int b){
    a=getParent(a);
    b=getParent(b);
    if(a==b) return false;
    if(a>b){
        parent[a]=b;
    }
    else   
        parent[b]=a;
    return true;
}

int kruskal(){
    int total,cnt;
    total=cnt=0;
    for(int i=0;i<n;i++){
        parent[i]=i;
    }
    for(int index=0,cnt=0;cnt<n-1;index++){
        if(changeParent(get<1>(edge[index]),get<2>(edge[index]))){
            total+=get<0>(edge[index]);
            cnt++;
        }
    }
    return total;
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        int a,b,c;
        cin>>a>>b>>c;
        x.push_back({a,i});
        y.push_back({b,i});
        z.push_back({c,i});
    }
    sort(x.begin(),x.end());
    sort(y.begin(),y.end());
    sort(z.begin(),z.end());

    for(int i=1;i<n;i++){
        edge.push_back({ABS(x[i-1].first,x[i].first),x[i-1].second,x[i].second});
        edge.push_back({ABS(y[i-1].first,y[i].first),y[i-1].second,y[i].second});
        edge.push_back({ABS(z[i-1].first,z[i].first),z[i-1].second,z[i].second});
    }
    sort(edge.begin(),edge.end());
    cout<<kruskal()<<endl;  
    return 0;
}