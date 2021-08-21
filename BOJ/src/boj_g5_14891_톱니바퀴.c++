#include <iostream>
#include <queue>
#include <string>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.21

*난이도 : G5
*개인 풀이 시간 : 30min
*개인 난이도 : 1/5 
*분류 : 자료구조 deque, 구현
*풀이 : 톱니바퀴 4개는 deque 배열로 구현했다.
*느낀점 : 톱니바퀴 사이 영향은 재귀로 구현했다. 중복을 막기위해 visited 배열을 뒀으나, 재귀를 갈때 
        origin만 전달하면 중복을 막을 수 있었다.
*/

deque<int> gears[4];
void rotateGear(int index,bool dir,int origin){
    int rPolarity=gears[index][2];
    int lPolarity=gears[index][6];
    if(dir){
        int cur=gears[index].back();
        gears[index].pop_back();
        gears[index].push_front(cur);
    }
    else{
        int cur=gears[index].front();
        gears[index].pop_front();
        gears[index].push_back(cur);
    }   
    if(index-1>=0&&index-1!=origin&&lPolarity!=gears[index-1][2])
        rotateGear(index-1,!dir,index);
    if((index+1<=3&&index+1!=origin&&rPolarity!=gears[index+1][6]))
        rotateGear(index+1,!dir,index);
}

int calPoint(){
    int point=0;
    int weight=1;
    for(int i=0;i<4;i++){
        if(i)weight*=2;
        if(gears[i][0])
        point+=weight;
    }
    return point;
}

int main(){
    for(int i=0;i<4;i++){
        string line;
        cin>>line;
        for(int j=0;j<8;j++)
            gears[i].push_back(line[j]-'0');
    }
    int num;
    cin>>num;
    while(num--){
        int index,d;
        cin>>index>>d;
        bool dir=d>0?true:false;
        rotateGear(index-1,dir,6);
    }
    cout<<calPoint()<<endl;
}