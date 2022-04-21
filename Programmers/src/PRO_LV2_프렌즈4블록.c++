#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#define SWAP(a,b,t) ((t) = (a) , (a) = (b) , (b) = (t))
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.04.22

*난이도 : Level2
*개인 풀이 시간 : 20/60 Hour
*개인 난이도 : 2/5 
*분류 : 구현, 시뮬레이션, 중력구현
*풀이 : 

*느낀점 : 
*/

int solution(int m, int n, vector<string> board) {
    int cnt = 0;
    while(true){
        bool del[m][n];
        memset(del , 0 , sizeof(del));
        //4칸 연속해서 체크하기 위해서 m-1, n-1만큼 돌기
        for(int i = 0 ; i < m - 1 ; i++){
            for(int j = 0 ; j < n - 1 ; j++){
                if(board[i][j] == '*') continue;
                char stan = board[i][j];
                //연속하는 2*2개가 모두 같으면 del 배열에 체크
                //만약 char 아스키 값이 값다면 !(0) = 1 이 되어서 1 && 1 && 1이 되어서 실행됨
                if(!(board[i + 1][j] - stan) && !(board[i][j + 1] - stan) && !(board[i + 1][j + 1] - stan)){
                    del[i][j] = del[i + 1][j] = del[i][j + 1] = del[i + 1][j + 1] = true; 
                }
            }
        }
        //del 체크된 것 삭제 플레그 실행하기
        int tCnt = 0;
        for(int i = 0 ; i < m ; i++){
            for(int j = 0 ; j < n ; j++)
                if(del[i][j]){
                    ++tCnt;
                    board[i][j] = '*';
                }
        }
        if(!tCnt) break;
        cnt += tCnt;
        char temp;
        //아래부터 하나씩 SWAP으로 내리기
        for(int i = m - 1 ; i > 0 ; i--){
            for(int j = 0 ; j < n ; j++){
                //빈칸일때만 실행해야함
                if(board[i][j] != '*') continue;
                int k;
                //빈칸이 아닌 무언가(내릴만한 블록이 있을 때 까지 진행)
                for(k = i - 1 ; k >= 0 ; k--){
                    if(board[k][j] != '*') break;
                }
                //만약 블록이 있다면 SWAP
                if(k >= 0) 
                    SWAP(board[i][j] , board[k][j] , temp);
            }
        }
    }
    return cnt;
}