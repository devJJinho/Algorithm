#include <iostream>
#include <vector>
#include <string>
#define ABS(a) (((a)<0)?-(a):(a))
#define MAX 100
#define INF 200
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.02.10

*난이도 : G4
*개인 풀이 시간 : 2
*개인 난이도 : 2/5
*분류 : 구현, 시뮬레이션, 자료구조
*풀이 : 미친로봇이 2개이상 겹쳐지는 경우를 체크하기 위해 100*100 배열을 선언함.
       그리고 vector를 비웠다가 다시 map을 보고 채우는 과정을 반복함.
*느낀점 : 더 효율적인 코드가 있는지 고민 필요

*/

//이동방향 지문에 맞춰서
const int dx[]={0,-1,0,1,-1,0,1,-1,0,1};
const int dy[]={0,1,1,1,0,0,0,-1,-1,-1};
pair<int,int> player;
vector<pair<int,int>> robots;
int map[MAX+1][MAX+1];
int r,c;
//두 점을 입력하면 이동할 방향을 알려주는 함수
int calDir(pair<int,int> robot){
    int min=INF;
    int minDir;
    for(int dir=1;dir<=9;dir++){
        //덧샘의 분배법칙을 생각하지 못해 디버깅에 한참 걸림.
        int cnt=ABS(player.first-(robot.first+dx[dir]))+ABS(player.second-(robot.second+dy[dir]));
        if(min>cnt) {
            min=cnt;
            minDir=dir;
        }
    }
    return minDir;
}
void clearMap(){
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            map[i][j]=0;
}
int main(){
    cin>>r>>c;
    for(int i=0;i<r;i++){
        string temp;
        cin>>temp;
        for(int j=0;j<c;j++){
            if(temp[j]=='I') player={j,i};
            if(temp[j]=='R') {
                ++map[i][j];
                robots.push_back({j,i});
            }
        }
    }
    string inst;
    cin>>inst;
    int cnt=0;
    bool isDone=true;
    for(int i=0;i<inst.length();i++){
        cnt++;
        player.first+=dx[inst[i]-'0'];
        player.second+=dy[inst[i]-'0'];
        if(map[player.second][player.first]){
            isDone=false;
            break;
        }
        clearMap();
        for(pair<int,int> robot :robots){
            int nDir=calDir(robot);
            int nx=robot.first+=dx[nDir];
            int ny=robot.second+=dy[nDir];
            if(player.first==nx&&player.second==ny){
                isDone=false;
                break;
            }
            ++map[ny][nx];
        }
        if(!isDone) break;
        robots.clear();
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++)
                if(map[i][j]==1) robots.push_back({j,i});
        }
    }
    if(!isDone){
        cout<<"kraj "<<cnt<<endl;
        return 0;
    }
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(map[i][j]==1) cout<<"R";
            else if(i==player.second&&j==player.first) cout<<"I";
            else cout<<".";
        }
        cout<<endl;
    }
}