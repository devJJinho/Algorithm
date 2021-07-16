#include <iostream> 
#include <fstream>
#include <string>
#include <queue>
#define INF 999
#define MAX 100

using namespace std;

const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

struct info {
    int x,y;
};

char map[MAX+2][MAX+2];
queue<int> crushArray;
int row,col;

bool isValid(int x,int y){
    return x>=1&&x<=col&&y>=1&&y<=row;
}
void crush(int y){
    int x=1;
    while(map[y][x]!='x'&&x<=col){
        x++;
    }
    if(x==col) return;
    map[y][x]='.';
    info mineral;
    for(int i=0;i<4;i++){
        int nx=x+dx[i];
        int ny=y+dy[i];
        if(!isValid(x,y)) continue;
        if(map[ny][nx]=='x'){
            mineral.x=nx;
            mineral.y=ny;
            break;
        }
    }

    bool isTouch;
    bool visited[MAX+2][MAX+2];

        queue<info> minQue;
        minQue.push(mineral);
        visited[mineral.y][mineral.x]=true;
        while(!minQue.empty()){
            info curInfo=minQue.front();
            minQue.pop();
            for(int j=0;j<4;j++){
                int nx=curInfo.x+dx[j];
                int ny=curInfo.y+dy[j];
                if(!isValid(nx,ny)) continue;
                if(ny==1) isTouch=true;
                if(map[ny][nx]='x'&&!visited[ny][nx]){
                    minQue.push({nx,ny});
                    visited[ny][nx]=true;
                }
            }
        }
    
        if(!isTouch){
        int diff=INF;
        for(int i=1;i<=col;i++){
            int lastMin;
            int j;
            for(j=row;j>=1;j--){
                if(map[j][i]=='x'&&!visited[j][i]) lastMin=j;
                if(visited[j][i]) break;
            }
            diff=min(diff,lastMin-j);
        }

        for(int i=row;i>=1;i--){
            for(int j=1;j<=col;j++){
                if(visited[i][j]){
                    map[i+diff][j]=map[i][j];
                }
            }
        }
        }
    }

//상하좌우


int main(){
    int i,j;
    ifstream fin;
    fin.open("file.txt");   
    fin>>row>>col;
    for(i=1;i<=row;i++){
        string temp;
        fin>>temp;
        for(j=1;j<=col;j++)
            map[i][j]=temp[j-1];
    }
    int num;
    fin>>num;
    for(i=0;i<num;i++){
        int temp;
        fin>>temp;
        crushArray.push(temp);
    }

    while(!crushArray.empty()){
        int crushRow=crushArray.front();
        crushArray.pop();
        crush(crushRow);
    }
}

