#include <iostream>
#include <queue>
#include <vector>
#define MAX 50
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.02

*난이도 : G4
*개인 풀이 시간 : 52/60 hour 
*개인 난이도 : 2/5 
*분류 : 시뮬, 구현, 삼성문제
*풀이 : 주석 참조

*느낀점 : map이 따로 없기 때문에 map을 유지하지 않음

*/

struct info{
    int x,y,weight,dir,speed;
};
const int dx[]={0,1,1,1,0,-1,-1,-1};
const int dy[]={-1,-1,0,1,1,1,0,-1};
queue<info> balls;
int N,M,K;

void func(){
    vector<info> map[MAX+1][MAX+1];
    //파이어볼을 하나씩 꺼내서
    while(!balls.empty()){
        auto cur=balls.front();
        balls.pop();
        //1과 N이 연결되어 있다는 것을 아래와 같이 표현함
        //현재 코드에선 0을 기준점으로 하기 때문에 [0,N-1]
        int nx=(cur.x+dx[cur.dir]*cur.speed)%N;
        if(nx<0) nx+=N;
        int ny=(cur.y+dy[cur.dir]*cur.speed)%N;
        if(ny<0) ny+=N;
        //이동의 결과를 map에 표시. 
        //map은 중복 검사를 쉽게 하기 위해
        map[ny][nx].push_back({nx,ny,cur.weight,cur.dir,cur.speed});
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            int size=map[i][j].size();
            if(!size) continue;
            //두개 이상이면
            if(size>=2){
                int evenOdd[2]={0,0};
                int weightSum=0;
                int speedSum=0;
                //필요한 정보를 취합, 더불어 방향에 대한 정보도 배열을 통해 모음
                for(auto node:map[i][j]){
                    evenOdd[node.dir%2]++;
                    weightSum+=node.weight;
                    speedSum+=node.speed;
                }
                weightSum/=5;
                //무게가 0이면 소멸
                if(!weightSum) continue;
                speedSum/=size;
                vector<int> ndir;
                //'dir이 전부 홀수이거나 전부 짝수이거나'을 구현함
                if(evenOdd[0]==size||evenOdd[1]==size)
                    ndir={0,2,4,6};
                else ndir={1,3,5,7};
                //새로운 파이어볼을 저장
                for(int t=0;t<4;t++){
                    balls.push({j,i,weightSum,ndir[t],speedSum});
                }
                continue;
            }
            //하나만 있는 경우 넣어줌
            balls.push({j,i,map[i][j][0].weight,map[i][j][0].dir,map[i][j][0].speed});
        }
    }
}

int main(){
    cin>>N>>M>>K;
    for(int i=0;i<M;i++){
        int y,x,weight,speed,dir;
        cin>>y>>x>>weight>>speed>>dir;
        //0베이스를 위해 하나씩 줄임
        y-=1; x-=1;
        balls.push({x,y,weight,dir,speed});
    }
    while(K--){
        func();
    }
    int sum=0;
    while(!balls.empty()){
        auto cur=balls.front();
        balls.pop();
        sum+=cur.weight;   
    }
    cout<<sum<<endl;
}