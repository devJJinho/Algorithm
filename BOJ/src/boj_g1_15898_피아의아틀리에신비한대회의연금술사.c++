#include <iostream>
#include <vector>
#include <cstring>
#define MAX 10
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.04.24

*난이도 : G1
*개인 풀이 시간 : 1.2hour 
*개인 난이도 : 3/5 
*분류 : 브루트포스, 구현, 시뮬
*풀이 : O(4 * 4 * 10 P 3)
*느낀점 : 

*/

struct INFO{
    int value;
    char color;
};

int N;
INFO mater[MAX + 1][4][4];
bool isUsed[MAX + 1];
INFO dp[5][5][5];
int maxValue;
int calPoint(){
    //알파벳 수만큼 초기화
    int cnt[26];
    memset(cnt , 0 , sizeof(cnt));
    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            cnt[dp[3][i][j].color - 'A'] += dp[3][i][j].value;
        }
    }
    return 7 * cnt['R' - 'A'] + 5 * cnt['B' - 'A'] + 3 * cnt['G' - 'A'] + 2 * cnt['Y' - 'A'];
}

void rotate(int idx){
    INFO temp[4][4];
    memcpy(temp , mater[idx] , sizeof(temp));
    for(int i = 0 ; i < 4 ; i++){
        for(int j = 0 ; j < 4 ; j++){
            mater[idx][i][j] = temp[3 - j][i];
        }
    }
}

void mapCpy(int cnt, int idx , int x , int y){
    //직전 배열 복사
    memcpy(dp[cnt] , dp[cnt - 1] , sizeof(dp[cnt]));
    for(int i = 0 ; i < 4 ; i++){
        for(int j = 0 ; j < 4 ; j++){
            //재료의 크기인 4*4만큼 돌면서 덮어씌우기
        	INFO& mp = dp[cnt][y + i][x + j];
            mp.value += mater[idx][i][j].value;
            if(mp.value < 0)
                mp.value = 0;
            else if(mp.value > 9)
                mp.value = 9;
            if(mater[idx][i][j].color != 'W')
                mp.color = mater[idx][i][j].color;
        }
    }
}
void recul(int cnt){
    if(cnt == 4){
        int ret = calPoint();
        if(maxValue < ret) maxValue = ret;
        return;
    }
    //순열 만들기
    //재료의 사용 순서에 따라 다르기 때문에 순열
    for(int idx = 1 ; idx <= N ; idx++){
        //만약 사용하지 않은 재료라면
        if(!isUsed[idx]){
            isUsed[idx] = true;
            //4방향 회전 할 계획 => 4방향 회전 뒤엔 원위치로 복귀함
            for(int rota = 0 ; rota < 4 ; rota++){
                //시작위치는 (0,0) , (0,1)
                //        (1,0) , (1,1)  중 하나
                for(int posY = 0 ; posY < 2 ; posY++){
                    for(int posX = 0 ; posX < 2 ; posX++){
                        //복사와 재료 사용이 동시에 이루어짐
                        mapCpy(cnt , idx , posX , posY);
                        //dp[cnt]가 완성된 채로 다음 재귀로 감
                        recul(cnt + 1);
                    }
                }
                rotate(idx);
            }
            isUsed[idx] = false;
        }
    }
}
int main(){
    cin >> N;
    for(int cnt = 1 ; cnt <= N ; cnt++){
        for(int i = 0 ; i < 4 ; i++){
            for(int j = 0 ; j < 4 ; j++){
                cin >> mater[cnt][i][j].value;
            }
        }
        for(int i = 0 ; i < 4 ; i++){
            for(int j = 0 ; j < 4 ; j++){
                cin >> mater[cnt][i][j].color;
            }
        }
    }
    for(int i = 0 ; i < 4 ; i++){
        for(int j = 0 ; j < 4 ; j++)
            dp[0][i][j] = {0,'W'};
    }
    //재귀
    recul(1);
    cout << maxValue << endl;
}