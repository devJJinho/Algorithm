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
*개인 풀이 시간 : 다시 푼 시간 : 5min
*개인 난이도 : 4/5 
*분류 : 순열
*풀이 : digit이 필요없었다.
       만약 첫번째 재귀 깊이에서 하나를 선택하고, 두번째,세번째,네번째에서 본인을 선택하지 않으면 한자리수가 나오기 때문!!!
       
*느낀점 : 재귀의 작동 방식에 대해 깊이 이해하자..
*/

void recul(vector<vector<int>> &dice,int depth,int cnt){
    //재귀의 depth 관리
    if(depth==dice.size()){
        if(available.size()){
            int sum=available[0];
        int depth=10;
        for(int i=1;i<cnt;i++){
            sum+=available[i]*depth;
            depth*=10;
        }
        cache[sum]=true;
    	return;
        }
        else return;
    } 

    for(int i=0;i<dice.size();i++){
        //나를 선택하지 않은 경우
        if(isUsed[i]) continue;
        isUsed[i]=true;
        //나를 선택하지 않았기 때문에 cnt는 증가하지 않는다.
        recul(dice,depth+1,cnt);
        isUsed[i]=false;
        //해당 주사위의 6면 각각의 경우
    	for(int j=0;j<dice[i].size();j++){
    		available.push_back(dice[i][j]);
    		isUsed[i]=true;
    		recul(dice,depth+1,cnt+1);
    		available.pop_back();
    		isUsed[i]=false;
    	}
    }
}

int main(){
    //vector<vector<int>> dice={{1,6,2,5,3,4},{9,9,1,0,7,8}};
    vector<vector<int>> dice={{0,1,5,3,9,2},{2,1,0,4,8,7},{6,3,4,7,6,5},{1,2,3,4,5,6}};
    recul(dice,0,0);
    int res;
    for(res=1;res<MAX;res++)
        if(!cache[res])break;
    cout<<res<<endl;
    return 0;
}
