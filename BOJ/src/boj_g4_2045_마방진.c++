#include <iostream>
#include <vector>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.04.21

*난이도 : G4
*개인 풀이 시간 : 2hour 
*개인 난이도 : 3/5 
*분류 : 구현, 수학, 시뮬
*풀이 :
       
*느낀점 : 문제를 단순화 했다면 이것의 반례를 잘 생각해봐야함. 너무 단순화한 나머지 문제 상황 외에 다른 상황이 포함 될 수도 있음
       
        
*/

int map[3][3];
int ptCnt;
int row[3] = {0,0,0};
int col[3] = {0,0,0};

void findClue(int totalSum){
    int cnt = 0;
    while(cnt < ptCnt){
        //행 열 각각에 대해 공백이 하나 인 줄만 찾아서 복구함
        for(int i = 0 ; i < 3 ; i++){
            //공백이 하나인 경우에만 진행
            if(row[i] != 1) continue;
            int x = 0 , sum = 0 ;
            //합을 구하면서 동시에 공백 위치를 찾음
            for(int j = 0 ; j < 3 ; j++){
                sum += map[i][j];
                if(map[i][j] == 0) x = j;
            }
            //공백에 계산한 값을 대입
            map[i][x] = totalSum - sum;
            //삭제된 공백의 행,열 카운트 값을 내림
            row[i]--; col[x]--;
            cnt++;
        }
        for(int j = 0 ; j < 3 ; j++){
            if(col[j] != 1) continue;
            int y = 0 , sum = 0 ;
            for(int i = 0 ; i < 3 ; i++){
                sum += map[i][j];
                if(map[i][j] == 0) y = i;
            }
            map[y][j] = totalSum - sum;
            row[y]--; col[j]--;
            cnt++;
        }
    }
}

int getSum(){
    //온전한 한 줄을 찾기 위해 진행
    int i = 0;
    for( ; i < 3 ; i++){
        if(row[i] == 0 || col[i] == 0) break;
    }
    int sum = 0;
    //만약 온전한 행이나 열이 하나도 없으면 대각에서 찾을 수 있거나 아님 수학적으로 (전체 합/2)을 해야됨
    if(i == 3){
        //대각 가능한지 체크
       if(map[0][2] && map[1][1] && map[2][0]) return map[0][2] + map[1][1] + map[2][0];
       if(map[0][0] && map[1][1] && map[2][2]) return map[0][0] + map[1][1] + map[2][2];
       //양쪽 대각이 불가능하면 공백이 대각에 있는 것
       //전체 합을 구하고 /2를 Return
       for(int y = 0 ; y < 3 ; y++)
           for(int x = 0 ; x < 3 ; x++)
               sum += map[y][x];
       return sum / 2;
    }
    //만약 온전한 행 또는 열을 발견하면 그것의 합을 구한 뒤 Return
    if(row[i] == 0){
        for(int  j = 0 ; j < 3 ; j++)
            sum += map[i][j];
    }
    else{
        for(int j = 0 ; j < 3 ; j++)
            sum += map[j][i];
    }
    return sum;
}

int main(){
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            scanf("%d" , &map[i][j]);
            if(map[i][j] == 0){
                //빈칸을 발견하면 개수 count, 행/열 각각 카운트해서 up
                ptCnt++;
                row[i]++;
                col[j]++;
            }
        }
    }
    int sum = getSum();
    findClue(sum);
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            cout << map[i][j] << " ";
        }
        cout<<endl;
    }
}