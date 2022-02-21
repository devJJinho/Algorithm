#include <iostream>
#include <vector>
#define MAX 32000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.02.21

*난이도 : G2
*개인 풀이 시간 : 0.5hour
*개인 난이도 : 1/5 
*분류 : 위상정렬
*풀이 : 위상정렬으로 하되, 진입차수가 0인 것이 많으면 그땐 주어진 규칙에 맞춰 선택함.
       
*느낀점 : 
       위상정렬을 알면 쉬운 문제였음.
*/

int inNode[MAX+1];
int N,M;
vector<int> edge[MAX+1];

int findAavailable(){
    for(int i=1;i<=N;i++)
        if(inNode[i]==0) return i;
}

//사용한 엣지는 0에서 달라져야함
 int main(){
     vector<int> res;
     cin>>N>>M;
     int a,b;
     for(int i=0;i<M;i++){
         scanf("%d %d",&a,&b);
         inNode[b]++;
         edge[a].push_back(b);
     }
     int cnt=1;
     res.resize(N+1);
     while(cnt<=N){
         int next=findAavailable();
         --inNode[next];
         for(int end:edge[next])
            inNode[end]--;
        res[cnt++]=next;
     }
     for(int i=1;i<=N;i++)
        cout<<res[i]<<" ";
 }