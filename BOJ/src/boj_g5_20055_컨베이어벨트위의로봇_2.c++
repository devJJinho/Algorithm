#include <iostream>
#include <deque>
#include <cstring>
#define MAX 100
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.04.20

*난이도 : G5
*개인 풀이 시간 : 4 hour 
*개인 난이도 : 3/5
*분류 : 구현, 시뮬, 삼성 기출
*풀이 : 주석 참조

*느낀점 : 인덱스 활용이 너무 어려웠음
         도착 여부를 판단하기 위해 == N 을 한것이 오랜 디버깅의 이유
         N - 1 이어야 N번째 자리(1 base 기준)에 도착했는지 알 수 있음
*/

int N , NN, K;
int belt[MAX * 2 + 1];
int kCnt = 0;
deque<int> robots;
int main(){
    cin >> N >> K;
    NN = 2 * N;
    for(int i = 0 ; i < NN ; i++){
        scanf("%d" , &belt[i]);
    }
    int loadP = 0;
    int cnt = 0;
    while(kCnt < K){
        ++cnt;
        //올리는 점의 위치는 현재 위치 -1
        //예를들어 길이가 6이라면 0 -> 5 -> 4 -> 3 -> 2 -> 1 -> 0 순
        loadP = (loadP - 1 + NN) % NN;
        int arrCnt = 0;
        bool visited[NN];
        memset(visited, 0, sizeof(visited));
        for(int& rb : robots){
            //robots[i]에 저장되어 있는 것은 로봇이 올라가던 시점 정보
            //robots[i]에 저장되어 있는 것은 현재 시점보다 멀 순 없다
            //한칸 움직이더라도 그것은 robots[i]--로 구현됨, 이는 현시점 - 예전 시점의 값을 크게 하는게 목적이기 때문에 예전 시점은 더 예전으로 가야함
            if(cnt - rb == N - 1){
                arrCnt++;
                continue;
            }
            //cnt - rb 는 즉 i번째 로봇이 현재로 부터 얼마 전에 놓인 로봇인지 나타냄
            //얼마 전인지 알았으면 현재 놓는 위치는 뒤로 빠지기 때문에, 반대 방향으로 더하면 로봇이 놓일 당시의 좌표를 알 수 있음
            int x = (loadP + cnt - rb) % NN;
            int nx = (x + 1) % NN;
            if(belt[nx] > 0 && !visited[nx]){
                x = nx;
                rb--;
                if(--belt[nx] == 0) kCnt++;
            }
            if(cnt - rb == N - 1){
                arrCnt++;
                //도착점에 visited 체크 하지 않기 위해 continue 수행
                continue;
            }
            // 그 외에는 visited 체크
            // 만약 앞으로 한칸 갔다면 x가 nx로 업데이트 됐기 때문에 이동하는 경우, 그대로 있는 경우 모두 대응 가능
            visited[x] = true;
        }
        //먼저 넣은 로봇부터 도착할 것이기 때문에 앞에서 빠진 수 만큼 Pop 됨
        while(arrCnt--)
            robots.pop_front();
        //놓는 위치에 놓을 수 있으면 놓기
        if(belt[loadP] > 0){
            if(--belt[loadP] == 0) kCnt++;
            robots.push_back(cnt);
        }
    }
	cout << cnt << endl;
}