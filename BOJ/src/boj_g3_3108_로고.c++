#include <iostream>
#define MAX 1000
#define SWAP(a,b,t) (((t)=(a)),((a)=(b)),((b)=(t)))
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.02.06
*난이도 : G3
*개인 풀이 시간 : 4hr
*개인 난이도 : 2/5 
*분류 : union-find, 시뮬, 구현
*풀이 : 한 줄 긋기가 아니고 경로의 중첩이 가능 -> 접하냐 접하지 않냐로 구분
       접하는 경우 union-find로 같은 그룹으로 만듦
       0,0도 같은 연산을 수행
       union-find 결과로 나온 루트의 개수 사이 간선의 개수가 정답
*느낀점 : 전체 구조는 빠르게 잡았으나, 중첩된 직사각형을 찾는 코드에서 x,y축을 따로 생각해서 오답이 발생함

*/

struct info{
    int x1,y1,x2,y2;
};
int parent[MAX+1];
info coor[MAX+1];

int findParent(int n){
    if(n==parent[n]) return n;
    return findParent(parent[n]);
}

void unionParent(int a,int b){
    a=findParent(a);
    b=findParent(b);
    if(a==b) return;
    if(a<b)
        parent[b]=a;
    else    
        parent[a]=b;
}

bool checkCrossed(int a,int b){
    int lowerX=a,upperX=b,lowerY=a,upperY=b;
    int temp;
    if(coor[a].x1>coor[b].x1) SWAP(lowerX,upperX,temp);
    if(coor[a].y1>coor[b].y1) SWAP(lowerY,upperY,temp);
    if(coor[a].x1<coor[b].x1&&coor[a].x2>coor[b].x2&&coor[a].y1<coor[b].y1&&coor[a].y2>coor[b].y2)return false;
    if(coor[b].x1<coor[a].x1&&coor[b].x2>coor[a].x2&&coor[b].y1<coor[a].y1&&coor[b].y2>coor[a].y2)return false;
    bool isXcrossed=coor[upperX].x1>=coor[lowerX].x1&&coor[upperX].x1<=coor[lowerX].x2;
    bool isYcrossed=coor[upperY].y1>=coor[lowerY].y1&&coor[upperY].y1<=coor[lowerY].y2;
    return isXcrossed&&isYcrossed;
}

int main(){
    int n;
    cin>>n;
    parent[0]=0;
    coor[0]={0,0,0,0};
    for(int i=1;i<=n;i++){
        parent[i]=i;
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        coor[i]={x1,y1,x2,y2};
    }

    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(i==j) continue;
            if(findParent(i)==findParent(j)) continue;
            bool isCrossed=checkCrossed(i,j);
            if(isCrossed){
                unionParent(i,j);
            }
        }
    }
    //n개 사이 연결선(여기서는 두꺼비를 드는 행위)는 n-1번
    int cnt=1;
    for(int i=1;i<=n;i++) if(parent[i]==i) cnt++;
    cout<<cnt-1<<endl;
}