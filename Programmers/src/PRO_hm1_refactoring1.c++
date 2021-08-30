#include <iostream>
#include <vector>
#define MAX 10000
using namespace std;

bool cache[10000];
bool isUsed[4]={false};

vector<int> available;
/*
@author  :  Jinho Jeong
@date    :  2021.08.29

*난이도 : 
*개인 풀이 시간 : 다시 푼 시간 : 20min
*개인 난이도 : 4/5 
*분류 : 순열
*풀이 : 순열만 사용해서 풀었다. 
       recul 함수에 선택한 수의 개수 : cnt, 참조 중인 주사위 : depth (조합이었으면 index를 받고, for문의 시작값을 index로 초기화 하면 됨)
       선택한 주사위를 다시 선택하지 않기 위해 isUsed 배열 사용, 조합된 수의 자리수 선택을 위해 digit 변수 선언
       
*느낀점 : 재귀의 작동 과정, 순열과 조합의 정의에 대해 정확히 알 필요가 있다.
        재귀는 전역에 둘 변수, 재귀 사이에 주고받은 변수의 구성에 따라 정말 무궁무진하게 사용할 수 있다.
*/

void recul(vector<vector<int>> &dice,int depth,int cnt,int digit){
    if(cnt==digit){
        int sum=available[0];
        int depth=10;
        for(int i=1;i<cnt;i++){
            sum+=available[i]*depth;
            depth*=10;
        }
        cache[sum]=true;
    	return;
    }
    //재귀의 depth 관리, 해당 깊이에서 위 구문이 실행 안됐다면 return;
    if(depth==dice.size()) return;

    for(int i=0;i<dice.size();i++){
        //나를 선택하지 않은 경우
        if(isUsed[i]) continue;
        isUsed[i]=true;
        //나를 선택하지 않았기 때문에 cnt는 증가하지 않는다.
        recul(dice,depth+1,cnt,digit);
        isUsed[i]=false;
        //해당 주사위의 6면 각각의 경우
    	for(int j=0;j<dice[i].size();j++){
    		available.push_back(dice[i][j]);
    		isUsed[i]=true;
    		recul(dice,depth+1,cnt+1,digit);
    		available.pop_back();
    		isUsed[i]=false;
    	}
    }
}

int main(){
    //vector<vector<int>> dice={{1,6,2,5,3,4},{9,9,1,0,7,8}};
    vector<vector<int>> dice={{5,6,7,8,9,1},{6,3,4,7,9,5},{2,1,0,4,8,7},{1,2,3,4,5,6}};
    for(int i=1;i<=dice.size();i++){
        recul(dice,0,0,i);
    }
    int res;
    for(res=1;res<MAX;res++)
        if(!cache[res])break;
    cout<<res<<endl;
    return 0;
}
