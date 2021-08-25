#include <string>
#include <vector>
#include <set>
#define MAX 100
#define has(x,y,isBeam) (map[y+1][x+1][isBeam])
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.24

*난이도 : kakao blind 2019
*개인 풀이 시간 : 3hr
*개인 난이도 : 3/5 
*분류 : 추상화 / 자료구조 사용(set)
*풀이 : 문제의 지문에서 입력값의 경우가 '가능한 경우'만 주어진다고 했기 때문에 내가 일일이 범위 내에 있는지, 중복되는지 체크할 필요가 없었다. 
       보와 기둥 각각의 조건만 구현한 뒤 삽입, 삭제 한 뒤 모든 보,기둥이 조건을 만족하는지 체크하고, 만족하지 않으면 되돌리면 되는 문제다.

*느낀점 : 처음에는 구현 문제로 생각하고 200줄 가까이 되는 코드를 짰으나, 너무 고려해야될 것이 많아 이상함을 느껴 검색 후 아래와 같이 풀었다.
        모든 문제에서 추상화가 가능한지 생각하는게 중요하다.
        너무 많은 조건이 나온다면 그건 내가 이상하게 접근하고 있을 가능성이 크다.
        사실 set 하나만으로도 풀 수 있으나, set.find를 매번 하는 것 보다 배열에 접근하는것이 빠를듯하여 map을 두고 했다.
        map의 최대값은 100*100이라 보와 기둥을 찾기위해 2*100*100 하는 것은 마치 희소행렬을 배열로 구현한 것처럼 비효울적일 듯하여 map의 원소를 담은 set을 같이 전달했다.
        vector가 아닌 set을 한 이유는 '삭제' 동작해서 find를 빨리하기 위함이다.
        배열에 접근할때 매번 범위 내에 있는지 체크하는 것을 막기 위해 배열을 최대크기 보다 2크게 만들어서 버퍼 역할을 했다. 범위를 벗어난 값은 무조건 false, 매크로 함수 has()로 접근을 쉽게 했다.
*/


// 0 : pillar // 1 : beam 
bool map[MAX+2][MAX+2][2]={false};

bool isValid(set<vector<int>> &list){
    for(auto node:list){
        int x=node[0];
        int y=node[1];
        bool isBeam=node[2];
        if(isBeam){
            if(has(x,y-1,0)||has(x+1,y-1,0)||(has(x-1,y,1)&&has(x+1,y,1))) continue;
            else return false;
        }
        else{
            if(y==0||has(x,y-1,0)||has(x,y,1)||has(x-1,y,1)) continue;
            else return false;
        }
    }
    return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    set<vector<int>> list;
    for(auto node:build_frame){
        int x=node[0];
        int y=node[1];
        bool isBeam=node[2];
        bool isInstall=node[3];
        if(isInstall){
            list.insert({x,y,isBeam});
            has(x,y,isBeam)=true;
            if(!isValid(list)){
                list.erase(list.find({x,y,isBeam}));
                has(x,y,isBeam)=false;
            }
        }
        else{
            list.erase(list.find({x,y,isBeam}));
            has(x,y,isBeam)=false;
            if(!isValid(list)){
                list.insert({x,y,isBeam});
                has(x,y,isBeam)=true;
            }
        }
    }
    for(auto a:list)
        answer.push_back(a);

    return answer;
}

/////////////////////////////////////////
//////////구현 문제로 생각하고 푼 방식//////////
/////////////////////////////////////////

/*

#define MAX 100
//어떤 자료구로로 어떻게 현 상태를 표현할지?
//3차원 배열로 표현할까?
//삭제때 재귀가 필요할까? => 놉 좌우만 확인하면 된다.
using namespace std;

//[][][0] : pillar
//[][][1] : beam
struct info{
    bool start,end;
};
info map[MAX+1][MAX+1][2]={false,false};
int len;

bool isInside(int x,int y){
    return x>=0&&x<len&&y>=0&&y<len;
}

bool canInsBeam(int x,int y){
    int nx=x+1,ny=y;
    if(map[y][x][1].start) return false;
    if(!isInside(nx,ny)) return false;
    //보가 바닥에 설치되는 경우
    if(y==0) return false;
    //한쪽 끝에 기둥이 있는 경우
    else if(map[y][x][0].end||map[ny][nx][0].end) return true;
    //양쪽 끝에 보가 있는 경우
    else if(map[y][x][1].end&&map[ny][nx][1].start) return true;
    else 
        return false;
}

bool canInsPillar(int x,int y){
    int nx=x,ny=y+1;
    if(map[y][x][0].start) return false;
    if(!isInside(nx,ny)) return false;
    //바닥 위인 경우
    if(y==0) return true;
    //아래 다른 기둥이 있을때
    else if(map[y][x][0].end) return true;
    //기둥의 위치에서 시작하는 보가 있을때
    else if(map[y][x][1].start) return true;
    //기둥의 위치에서 끝나는 보가 있을때
    else if(map[y][x][1].end) return true; 
    else 
        return false;
}

void writePillar(int x,int y,bool value){
    int nx=x,ny=y+1;
    map[y][x][0].start=value;
    map[ny][nx][0].end=value;
}
void writeBeam(int x,int y,bool value){
    int nx=x+1,ny=y;
    map[y][x][1].start=value;
    map[ny][nx][1].end=value;
}

bool checkAround(vector<tuple<int,int,int>> list){
    bool res=true;
    for(auto check:list){
        int x=get<0>(check);
        int y=get<1>(check);
        bool isBeam=get<2>(check);
        if(isBeam){
            writeBeam(x,y,false);
            if(!canInsBeam(x,y)){
                res=false;
                break;
            }
            writeBeam(x,y,true);
        }
        else{
            writePillar(x,y,false);
            if(!canInsPillar(x,y)){
                res=false;
                break;
            }
            writePillar(x,y,true);
        }
    }
    return res;
}

bool canRemovePillar(int x,int y){
    int nx=x,ny=y+1;
    writePillar(x,y,false);
    vector<tuple<int,int,int>> list;
    //기둥이 사라짐으로써 영향 받는것
    //기둥에 올려진 보, 기둥 위의 기둥
    if(map[ny][nx][0].start) list.push_back({nx,ny,0});
    if(map[ny][nx][1].end) list.push_back({nx-1,ny,1});
    if(map[ny][nx][1].start) list.push_back({nx,ny,1});
    bool res=checkAround(list);
    writePillar(x,y,true);
    return res;
}

bool canRemoveBeam(int x,int y){
    int nx=x+1,ny=y;
    writeBeam(x,y,false);
    vector<tuple<int,int,int>> list;
    if(map[y][x][0].start) list.push_back({x,y,0});
    if(map[ny][nx][0].start) list.push_back({nx,ny,0});
    if(map[y][x][1].end) list.push_back({x-1,y,1});
    if(map[ny][nx][1].start) list.push_back({nx,ny,1});
    bool res=checkAround(list);
    writeBeam(x,y,true);
    return res;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    len=n;
    for(auto node:build_frame){
        int x=node[0];
        int y=node[1];
        bool isBeam=node[2];
        bool isInstall=node[3];
        
        if(isInstall){
            if(isBeam){

            }
            else{

            }
        }
        else{
            if(isBeam){

            }
            else{

            }

        }
        
    }
    vector<vector<int>> answer;
    return answer;
}

*/




