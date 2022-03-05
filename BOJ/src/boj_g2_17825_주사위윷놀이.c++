#include <iostream>
using namespace std;

/*

@author  :  Jinho Jeong
@date    :  2022.03.05
*난이도 : G2
*개인 풀이 시간 : 2hour
*개인 난이도 : 2/5 
*분류 : 구현, 시뮬, 삼성문제
*풀이 : 주석 참고

*느낀점 : 규칙이 없어서 이동을 어떻게 해야될지 고민이 많았음. 결국 배열에 전체 구현을 함
        여러가지 경로가 만나는 점 25와 40에서 모든 점이 만나야 중복 검사가 가능함 이 문제 때문에 테케3번과 제출 8%에서 에러가 남
    
*/

int maxValue;
int diceInst[10];
int diceStat[4];
int score[]={
    0,
    2,
    4,
    6,
    8,
    10, 
    12,
    14,
    16,
    18,
    20, 
    22,
    24,
    26,
    28,
    30, 
    32,
    34,
    36,
    38,
    40, //마지막
    0,  //파란색 길 
    13, 
    16,
    19,
    25, 
    30,
    35,
    40, 
    0,
    22, //파란색 길
    24,
    25, 
    0,  
    28, //파란색 길
    27,
    26,
    25, 
    0
};

int moveHorse(int index, int n){
    int start=diceStat[index];
    if(start==21) return 0;
    if(start==5){ //파란색 길
        start=22; n--;
    }
    else if(start==10){ //파란색 길
        start=30; n--;
    }
    else if(start==15){ //파란색 길
        start=34; n--;
    }
    while(n--){
        start+=1;
        if(start==21) break; //도착지
        if(start==32||start==37) start=25; //25에서 합치기
        if(start==28) start=20; //40에서 합치기
    }
    return start;
}

void recul(int cnt,int value){
    if(cnt>=10) {
        //최대값 업데이트
        if(value>maxValue) maxValue=value;
        return;
    }
    //순열을 만들기 위해 순열 길이 만큼 진행하면서 각각 선택하기, 말의 중복이 가능하기 때문에 visited는 불피요
    for(int index=0;index<4;index++){
        int prePosition=diceStat[index];
        //목표지점 받아오기
        int dest=moveHorse(index,diceInst[cnt]);
        bool canMove=true;
        for(int i=0;i<4;i++){
            if(i==index) continue;
            if(diceStat[i]==21) continue;
            //목표지점에 다른 말이 있으면 불가능
            if(diceStat[i]==dest){
                canMove=false;
                break;
            }
        }
        //불가능하면 다음 말로
        if(!canMove) continue;
        diceStat[index]=dest;
        recul(cnt+1,value+score[dest]);
        //공유하는 전역 변수를 위해 원상복귀
        diceStat[index]=prePosition;
    }
}

int main(){
    for(int i=0;i<10;i++)
        cin>>diceInst[i];
    recul(0,0);
    cout<<maxValue<<endl;
}