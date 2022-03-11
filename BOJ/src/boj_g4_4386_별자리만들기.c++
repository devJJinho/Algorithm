#include <iostream>
#include <queue>
#include <cmath>
#define MAX 100
using namespace std;

pair<double,double> points[100];
int parent[MAX];

/*

@author  :  Jinho Jeong
@date    :  2022.03.11

*난이도 : G4
*개인 풀이 시간 : 20min 
*개인 난이도 : 2/5 
*분류 : 크루스칼 알고리즘, Union-find, 수학
*풀이 : 주석 참조
*느낀점 : 수함 함수의 사용에 익숙해질 필요가 있음.
        
*/

int findParent(int n){
    if(parent[n]==n) return n;
    return parent[n]=findParent(parent[n]);
}

bool unionParent(int a,int b){
    a=findParent(a);
    b=findParent(b);
    if(a==b) return false;
    if(a>b) parent[a]=b;
    else parent[b]=a;
    return true;
}
//Min-heap을 위한 구조
struct info{
    int a,b;
    double dist;
    bool operator<(const info& b)const{
        return dist>b.dist;
    }
};
//유클리드 거리 계산
double calDist(int a,int b){
    return sqrt(pow(points[a].first-points[b].first,2)+pow(points[a].second-points[b].second,2));
}
priority_queue<info> pq;
int main(){
    int N;
    cin>>N;
    double a,b;
    for(int i=0;i<N;i++){
        parent[i]=i;
        scanf("%lf %lf",&a,&b);
        points[i]={a,b};
    }
    //양방향 간선이기 때문에 i,j가 겹치지 않게
    for(int i=0;i<N-1;i++){
        for(int j=i+1;j<N;j++){
            pq.push({i,j,calDist(i,j)});
        }
    }
    //간선의 선택은 N-1개
    int cnt=N-1;
    double sum=0.0;
    while(cnt){
        auto cur=pq.top();
        pq.pop();
        //다른 집단 사이에서 합치게 되면 true
        bool res=unionParent(cur.a,cur.b);
        if(res){
            sum+=cur.dist;
            --cnt;
        }
    }
    //소수점 2자리에서 반올림하기 위한 코드
    cout<<round(sum*100)/100<<endl;
}