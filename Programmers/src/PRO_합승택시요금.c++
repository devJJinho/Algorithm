#include <string>
#include <vector>
#include <algorithm>
#define MAX 200
#define INF 20000001
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.10

*난이도 : ? (카카오 블라인드 문제 중 하나)
*개인 풀이 시간 : 30min
*개인 난이도 : 2/5 (Level 5 치고는 쉬운편) 
*분류 : 그래프 / 플로이드 와샬
*풀이 : map[200][200]을 만들고, 양방향 그래프를 i->j j->i 동시에 입력함으로서 구현했다.
       자칫 비효율적으로 보일 수도 있었지만 성능에 있어서 영향은 없었다. 오히려 효율적이었음.

       !!!플로이드 와샬에서 3중 for문의 가장 바깥 for문에 '중간지점'이 위치해야된다!!!!

*느낀점 : 
        지문을 잘 읽어보고 시작하는 습관의 중요성 => 한지점까지 같이 가고 거기서 각자 흩어지는 경우를 읽지 못했음
        자료형의 최대값과 로직에서 발생할 수 있는 최대값을 항상 염두에 두고 풀이해야됨. 히든 케이스에선 꼭 물어봄.
*/

vector<vector<int>> map(MAX+1, vector<int>(MAX+1,INF));

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int i,j,k;
    for(vector<int> temp:fares){
        int start=temp[0];
        int end=temp[1];
        int value=temp[2];
        map[start][end]=map[end][start]=value;
    }
    for(k=1;k<=n;k++){
        for(j=1;j<=n;j++){
            for(i=1;i<=n;i++){
                map[i][j]=map[j][i]=min(map[i][j],map[i][k]+map[k][j]);
            }
        }
    }
    int minFare=INF;
    for(int i=1;i<=n;i++){
        minFare=min(minFare,map[s][i]+map[i][a]+map[i][b]);
    }
    minFare=min({minFare,map[s][a]+map[s][b],map[s][a]+map[a][b],map[s][b]+map[b][a]});
    return minFare;
}