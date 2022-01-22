#include <iostream>
#include <vector>
#define ABS(a) ((a)<(0)?-(a):(a))
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.01.22

*난이도 : b1
*개인 풀이 시간 : 20min
*개인 난이도 : 1/5 
*분류 : 단순 계산, 구현
*풀이 : 이전 풀이에서 BFS로 풀이했다면 이번에는 좌표값 계산으로만 풀이함.
       직전 풀이의 n^2만큼의 bfs 복잡도에서 n^2만큼의 단순 계산으로 복잡도가 낮아짐.

*느낀점 : 
       문제의 요구 사항을 보고 풀이하는 것이 중요.
       이번 풀이에선 간단한 주석을 통해 알고리즘 설계를 하고 시작했더니 구현이 용이했음. 계속 연습할 필요가 있음. 
       매크로 함수에서 괄호가 중요함.
*/

//n*n+1 크기의 배열 필요
int n;
pair<int,int> map[50];

int calMin(int origin, int goal){
    //정사각형 행렬이기 때문에 x,y가 같은 변수와 로직을 공유함
    //함수형으로 짜고 재사용하는게 나음
    //1. 시작과 목표점의 차의 절대값
    //2. 시작점이 0 || n-1인 경우 배열을 넘어가서(+1) 목표까지 차의 절대값
    //1,2 둘 중에 작은 값을 Return
    int res;
    res=ABS(goal-origin);
    if(origin==0){
        res=min(res,1+ABS(goal-(n-1)));
    }
    if(origin==n-1){
        res=min(res,goal+1);
    }
    return res;
}

int findPath(){
    //전체 경로 저장할 변수
    int total=0;
    //0~1, 1~2, .. 이런식으로 각각의 최단거리를 더해가야함
    int index=0;
    while(index<n*n){
        int cnt=1;
        cnt+=calMin(map[index].first,map[index+1].first);
        cnt+=calMin(map[index].second,map[index+1].second);
        //index, index+1 사이 최단거리를 함수를 불러 계산한다
        //return값을 total에 합함
        total+=cnt;
        index++;
    }
    return total;
}

int main(){
    //입력받기
    //입력받으면서 각 숫자마다 좌표 기록
    //[0]번지엔 (0,0) 넣어서 원점으로부터 좌표 구함
    vector<vector<int>> list={{11,9,8,12},{2,15,4,14},{1,10,16,3},{13,7,5,6}};
    n=list.size();
    map[0]={0,0};
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            map[list[i][j]]={j,i};
        }
    }
    int res=findPath();
    cout<<res<<endl;
    return 0;
}