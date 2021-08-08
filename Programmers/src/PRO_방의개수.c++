#include <string>
#include <vector>
#include <map>

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.06

*난이도 : Level 5
*개인 풀이 시간 : 1hour 
*개인 난이도 : 4/5 (Level 5 치고는 쉬운편) 
*분류 : 그래프 / 자료구조 map 사용
*풀이 : 방이 생성되는 조건 : 한 좌표에 2번 이상 방문하면서 해당 간선이 중복이 아닌 경우로 정의했다. => 고로 좌표를 관리가 주요함.
       좌표를 2차원 배열로 두기에는 좌표가 (0,0)에서 시작해서 상대적으로 늘어나기 때문에 최악의 경우를 대비하기 위해선 [200000][200000] 크기의 2차원 배열이 필요함 => 불가능
       {해당 좌표의 존재 유무}, {해당 좌표에 딸린 value}을 최대한 빨리 체크하기 위해선 좌표를 key로 하는 multimap의 사용이 적절해보였음
       multimap은 레드블랙트리로 구현했기 때문에 탐색 성능이 2진 탐색과 동일

       간선의 중복 여부는 한 좌표에 어떤 move로 왔는지 기록해서 구분함.
       다른 사람의 풀이에선 (출발 좌표->도착 좌표)로 묶어서 기록하기도 했지만, move방향의 역이 출발 좌표기 때문에 굳이 두 좌표를 유지할 필요가 없었다.
       그리고 간선은 양방향이기 대문에 ((도착지좌표),move), ((출발지좌표),move의 역방향) 을 동시에 기록함.

*느낀점 : 
        unordered_map, hash, map, multimap 등등 자료구조의 종류가 많았고 특성을 잘 알아야 필요에 따라 적절히 사용할 수 있을거 같다
        사실 처음엔 unordered_map의 key를 구조체나 pair로 구성하려 했으나, Unordered_map은 hash로 구현했기 때문에 내가 해시 구조체나 페어에 대한 '해시'함수를 구현해야됐다.
        (std::내가 만든 구조체에 대한 해시 함수가 없기 때문)
        이에 반해 map은 트리로 구성되어 있고 필요한 compare 함수가 pair에 대해선 구현되어 있기 때문에 연산자 오버라이딩 없이 바로 사용이 가능했음
        (pair의 경우 처음인자 비교-> 두번째 인자 비교)로 넘어감. 만약 구조체를 사용했다면 연산자 오버라이딩은 해야함.
*/

const int dx[]={0,1,2,1,0,-1,-2,-1};
const int dy[]={-2,-1,0,1,2,1,0,-1};

multimap<pair<int,int>,int> coordi;

int solution(vector<int> arrows) {
    int x=0;
    int y=0;
    int answer=0;
    //방향 8은 허수이다. 어느 방향을 타고 온 점이 아니기 때문
    coordi.insert(make_pair(make_pair(0,0),8));
    for(int move:arrows){
        //겹치는 점을 체크하기 위해 수직 방향 이동은 한번에 2칸 움직임, 대각선은 1*1 움직임 두번으로 구성했다.
        for(int i=0;i<2;i++){
            int nx=x+dx[move];
            int ny=y+dy[move];
            bool hasSameDir=false;
            bool isFirstInput=true;
            //해당 좌표에 처음 오는 것인지, 2번 이상 방문이라면 최초 간선인지 체크
            for (auto it = coordi.lower_bound(make_pair(nx,ny)); it != coordi.upper_bound(make_pair(nx,ny)); it++){
                isFirstInput=false;
                //같은 간선이 있다면 바로 break
                if(it->second==move) {
                    hasSameDir=true;
                    break;
                }
            }
            if(!hasSameDir){
                int oppoDir=move>=4?move-4:move+4;
                coordi.insert(make_pair(make_pair(nx,ny),move));
                //간선이 양방향이기 때문에 출발지, 도착지에 각각 기록해야됨
                coordi.insert(make_pair(make_pair(x,y),oppoDir));
                //해당 좌표에 2번 이상 방문&&처음 그려지는 간선 일때 방 생성!!
                if(!isFirstInput) {
                    answer++;
                }
            }
            x=nx;
            y=ny;
            if(move%2==0) break;
        }
    }
    return answer;
}