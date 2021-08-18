#include <iostream>
#include <vector>
#define ABS(x) (((x)<0)?-(x):(x))
#define MAX 20
#define INF 99999999

using namespace std;

/*
 
@author  :  Jinho Jeong
@date    :  2021.08.18

*난이도 : Silver 3
*개인 풀이 시간 : 30min
*개인 난이도 : 2/5
*분류 : 재귀, 조합
*풀이 : 재귀로 가능한 조합을 모두 구해서 vector에 담고 vector를 참조해서 모든 경우를 시도해봤다.
*느낀점 : 풀이 자체는 모든 조합을 시도해봐야 되는 것이나, 나의 풀이는 조합을 구할때 메모리와 시간이 많이 들었다.
        조합을 구하고 풀이하는 것이 아니라 조합을 구하는 재귀 안에 풀이를 같이 넣어야함. 
        정석 풀이는 DFS+백트래킹이라고 함 => 다시 풀 예정
        
*/

int n;
int map[MAX+1][MAX+1];

vector<vector<int>> combi;

void recul_combi(vector<int> v,int depth){
    if(v.size()==n/2){
        combi.push_back(v);
        return ;
    }
    if(depth==n) return ;
    else{
        recul_combi(v,depth+1);
        v.push_back(depth);
        recul_combi(v,depth+1);
    }
}

int main(){
 cin>>n;
 for(int i=0;i<n;i++){
     for(int j=0;j<n;j++){
         int temp;
         cin>>temp;
         map[i][j]=temp;
     }
 }

 vector<int> v;
 recul_combi(v,0);
 
 int minDiff=INF;
 for(vector<int> a:combi){
     bool isVisited[MAX+1]={false};
     int sumA=0;
     for(int i=0;i<n/2;i++){
         isVisited[a[i]]=true;
         for(int j=0;j<n/2;j++){
             sumA+=map[a[i]][a[j]];
         }
     }
     vector<int> b;
     for(int i=0;i<n;i++){
         if(!isVisited[i]) {
             b.push_back(i);
         }
     }
     int sumB=0;
     for(int i=0;i<n/2;i++){
         for(int j=0;j<n/2;j++){
             sumB+=map[b[i]][b[j]];
         }
     }
    minDiff=min(minDiff,ABS(sumA-sumB));
 }
cout<<minDiff<<endl;
}