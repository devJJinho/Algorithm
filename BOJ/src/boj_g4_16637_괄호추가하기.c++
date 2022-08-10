#include <iostream>
#include <string>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.08.08

*난이도 : G4
*개인 풀이 시간 : 1hr
*개인 난이도 : 3/5 
*분류 : 브루트포스, 재귀
*풀이 : 중첩된 괄호x, 연산자 하나를 사이에 두고 두 수 사이에 괄호침 등의 조건이 있기 때문에 비교적 간단한 로직으로 구현 가능.
       가능한 모든 경우를 브루트포스 방식으로 탐색
*느낀점 : 오랜만에 풀이했더니 풀이 방법이 정말 하나도 생각나지 않음..
        
*/
int N;
string fol;
int result = -1 * 1<<31;

int cal(int a , int b , char op){
    int ret;
    switch(op){
        case '+' : ret = a + b; break;
        case '-' : ret = a - b; break;
        default : ret = a * b;
    }
    return ret;
}

void find_Max(int ret , int idx){
    // 식 범위를 넘어가면 return
    if(idx >= N){
        result = max(result , ret);
        return;
    }
    // 만약 처음이라면 idx - 1이 음수이기 때문에 합 연산으로 시작
    char op = idx == 0 ? '+' : fol[idx - 1];
    int temp = cal(ret , fol[idx] - '0', op);
    //괄호 없이 탐색
    find_Max(temp , idx + 2);
    //묶을 괄호가 있으면 묶기
    if(idx <= N - 3 && idx != 0){
        temp = cal(fol[idx] - '0' , fol[idx + 2] - '0', fol[idx + 1]);
        temp = cal(ret , temp , fol[idx - 1]);
        //먼저 계산하고 탐색
        find_Max(temp , idx + 4);
    }
}
int main(){
    cin >> N >> fol;
    find_Max(0 , 0);
    cout << result;
}