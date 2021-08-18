#include <iostream>
#include <vector>
#define MAX 20
#define ABS(x) (((x)<0)?-(x):x)
#define INF 9999999
using namespace std;

/*
 
@author  :  Jinho Jeong
@date    :  2021.08.18

*난이도 : Silver 3
*개인 풀이 시간 : 30min
*개인 난이도 : 2/5
*분류 : DFS, 백트래킹
*풀이 : 더 효율적인 방법으로 다시 풀었다.
*느낀점 : isVisited, minDiff를 밖에 둠으로써 재귀에선 인자 전달이 줄어들었다. 첫번째 풀이 대비 메모리 1/8, 실행시간 1/3으로 줄었다.
        
*/


int map[MAX+1][MAX+1];
bool isVisited[MAX+1]={false};
int minDiff=INF;
int n;
void DFS(int index,int cnt){
    if(cnt==n/2){
        vector<int> a,b;
        for(int i=0;i<n;i++){
            if(isVisited[i]) a.push_back(i);
            else b.push_back(i);
        }
        int sumA,sumB;
        sumA=sumB=0;
        for(int i=0;i<n/2;i++){
            for(int j=i+1;j<n/2;j++){
                sumA+=map[a[i]][a[j]];
                sumA+=map[a[j]][a[i]];
            }
        }
        for(int i=0;i<n/2;i++){
            for(int j=i+1;j<n/2;j++){
                sumB+=map[b[i]][b[j]];
                sumB+=map[b[j]][b[i]];
            }
        }
        minDiff=min(minDiff,ABS(sumA-sumB));
        return;
    }
    else{
        for(int i=index+1;i<n;i++){
            if(!isVisited[i]){
                isVisited[i]=true;    
                DFS(i,cnt+1);
                //백트래킹 
                isVisited[i]=false;
            }
        }
    }
}

int main(){
    int i,j;
    cin>>n;
    
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            cin>>map[i][j];
        }
    }
    DFS(0,0);
    cout<<minDiff<<endl;
}