#include <iostream>
#include <set>
using namespace std;
const int dx[]={0,-1,0,1,-1,0,1,-1,0,1};
const int dy[]={0,1,1,1,0,0,0,-1,-1,-1};

char map[101][101];
int r,c;
set<pair<int,int>> robot;
pair<int,int> player;

bool stage(int move){
    player.first+=dx[move];
    player.second+=dy[move];
    if(robot.find(player)!=robot.end()) return false;
    
    int value;
    int dir;
    for(auto rb:robot){
        for(int i=1;i<=9;i++){
            if(i==5) continue;

        }
    }

}

int main(){
    cin>>r>>c;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cin>>map[i][j];
            if(map[i][j]=='I') player={j,i};
            if(map[i][j]=='R') robot.insert({j,i});
        }
    }
    string instruction;
    cin>>instruction;
    for(int i=0;i<instruction.length();i++){

    }
}