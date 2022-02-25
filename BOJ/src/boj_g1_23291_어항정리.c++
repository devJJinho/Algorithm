#include <iostream>
#include <deque>
#include <string.h>
#define SWAP(a,b,t) (((t)=(a)),((a)=(b)),((b)=(t)))
#define MAX 100
#define FISH_MAX 10000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.02.25

*난이도 : G1
*개인 풀이 시간 : 2hours
*개인 난이도 : 3/5 
*분류 : 구현, 시뮬레이션, 자료구조
*풀이 : 양방향 push,pop이 가능한 deque를 사용하며 문제에서 주어진 규칙을 구현함
       물고기 수 조정과 직렬화는 함수화 하여 재사용성을 높힘
       
*느낀점 : 
       
*/

deque<int> map[MAX];
int N,K;

void calibrate(int width,int height){
    //한쌍씩만 비교
    //수평 방향으로 i와, i-1끼리 비교
    int cali[MAX+1][MAX+1];
    //동시에 이루어져야하기 때문에 일괄 업데이트를 위한 배열 선언;
    memset(cali,0,sizeof(cali));
    for(int i=0;i<height;i++){
        for(int j=1;j<map[i].size();j++){
            int maxIndex=j-1,minIndex=j;
            if(map[i][j]>map[i][j-1]){
                int temp;
                SWAP(maxIndex,minIndex,temp);
            }
            int minus=map[i][maxIndex]-map[i][minIndex];
            minus/=5;
            cali[i][maxIndex]-=minus;
            cali[i][minIndex]+=minus;
        }
    }
    //수직방향 비교
     for(int i=height;i>0;i--){
        for(int j=0;j<map[i].size();j++){
            int maxIndex=i-1,minIndex=i;
            if(map[i][j]>map[i-1][j]){
                int temp;
                SWAP(maxIndex,minIndex,temp);
            }
            int minus=map[maxIndex][j]-map[minIndex][j];
            minus/=5;
            cali[maxIndex][j]-=minus;
            cali[minIndex][j]+=minus;
        }
    }
    //일괄 업데이트
    for(int i=0;i<height;i++){
        for(int j=0;j<map[i].size();j++)
            map[i][j]+=cali[i][j];
    }
}

void serialize(int width,int height){
    //새로우 deque에 직렬화 한 내용을 담음
    //기존 배열에 담으면 로직 수행이 안되거나 복잡해지기 때문
    deque<int> temp;
    for(int i=0;i<map[0].size();i++){
        for(int j=0;j<height;j++){
            if(map[j].size()>i){
                temp.push_back(map[j][i]);
            }
        }
    }
    for(int j=height-1;j>0;j--)
        map[j].clear();
    map[0]=temp;
}

int func(){
    int cnt=0;
    while(true){
        int minFish=FISH_MAX;
        int maxFish=0;
        //최대,최소 찾기
        for(int fish:map[0]){
            if(minFish>fish) minFish=fish;
            if(fish>maxFish) maxFish=fish;
        }
        //최대,최소 사이 차가 cnt이하면 return;
        if(K>=maxFish-minFish) return cnt;
        ++cnt;
        for(int i=0;i<map[0].size();i++)
            if(map[0][i]==minFish) map[0][i]++;
        int top=map[0].front();
        map[0].pop_front();
        map[1].push_front(top);
        
        //width, height는 초기값부터 시작해서 height는 1씩 커지고, width는 직전의 height를 물려받음
        int width=1;
        int height=2;
        while((N-width*height)>=height){
            for(int i=0;i<width;i++){
                for(int j=0;j<height;j++){
                    int cur=map[j].front();
                    map[j].pop_front();
                    map[width-i].push_back(cur);
                }
            }
            int temp;
            SWAP(width,height,temp);
            height++;
        }
        //while문 끝나고 난 가로,세로는 실제로 배열을 마는데 사용되진 않았지만(사이즈 초과에 의해) 내가 필요로 하는 width, height를 가지고 있음
        calibrate(width,height);
        serialize(width,height);
    
        //문제에서 주는 규칙을 일반화 하면
        //N/4씩 끊은 것을 0,1,2,3번째라고 하면

        // 1,2 3,4 5,6 7,8

        //  65
        //  34
        //  21
        //  78

        //순으로 들어감 때문에 이에 맞춰서 deque의 push_front, push_back을 사용함

        for(int i=0;i<3;i++){
            int cnt=0;
            //정방향
            int inputIndex;
            if(i%2) inputIndex=2;
            else inputIndex=i==0?1:3;
            for(int j=N/4*i;j<N/4*(i+1);j++){
                 int cur=map[0].front();
                map[0].pop_front();
                if(i%2)
                    map[inputIndex].push_back(cur);
                else
                    map[inputIndex].push_front(cur);
            }
        }
        //두 함수 모두 width는 사용하지 않음
        //대신 각 deque의 길이를 사용함 때문에 deque에는 필요 없는 쓰레기값이 있어선 안됨
        calibrate(N/4,4);
        serialize(N/4,4);
    }
}

int main(){
    cin>>N>>K;
    for(int i=0;i<N;i++){
        int temp;
        cin>>temp;
        map[0].push_back(temp);
    }
    cout<<func()<<endl;
}