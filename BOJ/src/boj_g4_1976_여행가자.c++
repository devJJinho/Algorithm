#include <iostream>
#include <vector>
#define INF 400
#define MAX 201
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.01.25

*난이도 : G4
*개인 풀이 시간 : 30min 
*개인 난이도 : 3/5 
*분류 : 플로이드 와샬
*풀이 : 플로이드 와샬의 바깥쪽 for loop는 t만큼 돌아야함.
       범위도 지정해주지만 그 아래 이중 포문이 도는 기회를 주기 때문.
*느낀점 : union-find로도 풀이 할 예정
       
        
*/

int map[MAX][MAX];

int main(){
    int n,m;
    vector<int> path;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            bool isConnected;
            cin>>isConnected;
            if(map[i][j]==1) continue;  
            if(i==j) {
                map[i][j]=1;
                continue;
            }
            map[i][j]=map[j][i]=isConnected?1:INF;
        }
    }
    for(int i=0;i<m;i++){
        int city;
        cin>>city;
        path.push_back(city);
    }
    //t는 전체 범위로 가져가야한다.
    //
    for(int t=1;t<=n;t++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(map[i][t]+map[t][j]<map[i][j]) map[i][j]=map[i][t]+map[t][j];
            }
        }
    }
    bool isPossible=true;
    for(int i=0;i<path.size()-1;i++){
        if(map[path[i]][path[i+1]]>=INF){
            isPossible=false;
            break;
        }
    }
    if(isPossible) cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;
}