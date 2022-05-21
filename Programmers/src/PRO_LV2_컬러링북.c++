#include <vector>
#include <string.h>
#include <queue>
#include <algorithm>
#define MAX 100
using namespace std;

/*

@author  :  Jinho Jeong
@date    :  2022.05.21

*난이도 : Level2
*개인 풀이 시간 : 30min
*개인 난이도 : 2/5 
*분류 : 문자열 , 구현
*풀이 : 

*느낀점 : 

*/

const int dx[] = {0 , 0 , -1 , 1};
const int dy[] = {-1 , 1 , 0 , 0};

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    vector<int> ret;
    bool visited[MAX][MAX];
    memset(visited , 0 , sizeof(visited));
    for(int i = 0 ; i < m ; i++){
        for(int j = 0 ; j < n ; j++){
            //공백이거나 방문했으면 진행
            if(picture[i][j] == 0 || visited[i][j]) continue;
            visited[i][j] = true;
            int color = picture[i][j];
            queue<pair<int,int>> que;
            que.push({j , i});
            int cnt = 0;
            while(!que.empty()){
                auto cur = que.front();
                cnt++;
                que.pop();
                for(int dir = 0 ; dir < 4 ; dir++){
                    int nx = cur.first + dx[dir];
                    int ny = cur.second + dy[dir];
                    //같은 색이면 queue에 담기
                    if(nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[ny][nx]){
                        if(picture[ny][nx] == color){
                            que.push({nx , ny});
                            visited[ny][nx] = true;
                        }
                    }
                }
            }
            //연속된 하나의 블록을 찾으면 그것을 담기
            ret.push_back(cnt);
        }
    }
    //정렬하기
    sort(ret.begin() , ret.end());
    vector<int> answer(2);
    answer[0] = ret.size();
    //오름차순으로 정렬됐기 때문에 back()이 최대값
    answer[1] = ret.back();
    return answer;
}