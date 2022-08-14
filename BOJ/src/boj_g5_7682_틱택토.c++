#include <iostream>
#include <string>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.08.14
*난이도 : G5
*개인 풀이 시간 : 1.5hr
*개인 난이도 : 2/5
*분류 : 시뮬레이션
*풀이 : 
        가능한 마지막 상태인지 묻는 문제.
        완탐 형식으로 푸는 것도 고민했으나, 문제에서 가능한 조건을 확인하는 방식으로 구현함.

*느낀점 :
        완탐으로 시뮬레이션 돌릴지 가능한 조건을 확인하는 식으로 구현할지 고민이 필요했음
*/

char map[3][3];

bool check(char stan){
    // 세로 방향 체크
    for(int j = 0 ; j < 3 ; j++){
        int i;
        for(i = 0 ; i < 3 ; i++){
            if(map[i][j] != stan) break;
        }
        if(i == 3) return true;
    }
    // 가로 방향 체크
    for(int i = 0 ; i < 3 ; i++){
        int j;
        for(j = 0 ; j < 3 ; j++){
            if(map[i][j] != stan) break;
        }
        if(j == 3) return true;
    }
    // 대각 체크
    if(map[0][0] == stan && map[0][0] == map[1][1] && map[0][0] == map[2][2])
        return true;
    if(map[0][2] == stan && map[0][2] == map[1][1] && map[0][2] == map[2][0])
        return true;

    return false;
}

int main(){
    string s;
    while(1){
        int x_cnt = 0 , o_cnt = 0, emp_cnt = 0;
        cin >> s;
        if(s == "end") break;
        bool isPossible = false;
        for(int i = 0 ; i < 3 ; i++){
            for(int j = 0 ; j < 3 ; j++){
                map[i][j] = s[i * 3 + j];
                //각각 카운트
                if(map[i][j] == '.') ++emp_cnt;
                else if(map[i][j] == 'X') ++x_cnt;
                else ++o_cnt;
            }
        }
        int gap = x_cnt - o_cnt;
        // X 먼저 두기 때문에 가능한 경우는 X-O 했을때 0(서로 같이 둠), 1(X가 하나 많음)만 가능함
        if(gap == 0){
            // 각각 같을 때, 가능한 경우는 후공인 O가 연속된 3칸을 완성한 경우임. 만약 선공이 3칸을 완성했다면 후공이 놓을 기회 조차 없음
            bool x_ret = check('X');
            bool o_ret = check('O');
            if(!x_ret && o_ret) isPossible = true;
        }
        else if(gap == 1){
            //하나 차이가 나는것은 선공인 X가 3칸을 완성한 경우. 이때 후공인 O가 완성 했을리는 없다 -> 그렇다면 X가 놓을 기회 조차 없음
            //그리고 아래 경우와 같이 9칸을 다 채웠는데 그 누구도 3칸을 완성하지 못한 케이스가 있음 
            // OXO
            // OXX
            // XOX
            bool x_ret = check('X');
            bool o_ret = check('O');
            if(!o_ret & x_ret || (!o_ret && !x_ret && !emp_cnt)) isPossible = true;
        }
        cout << (isPossible ? "valid\n" : "invalid\n");
    }

}