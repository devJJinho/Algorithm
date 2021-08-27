#include <iostream>
#include <vector>
#define MAX 10000
#define SWAP(a,b,c) c=a; a=b; b=c; 
using namespace std;

bool cache[10000];
int res[4];
bool isUsed[4]={false};

vector<int> available;

/*
@author  :  Jinho Jeong
@date    :  2021.08.28

*난이도 : 
*개인 풀이 시간 : 3hr
*개인 난이도 : 4/5 
*분류 : 순열+조합
*풀이 : 
*느낀점 : 순열+조합 모두 써서 풀었는데 이게 최적의 방법인가에 대한 의구심이 있다.      
*/

void permu(vector<int> &available,int depth,int n){
	if(depth==n){
		int sum=available[0];
        int index=10;
        for(int i=1;i<n;i++){
            sum+=available[i]*index;
            index*=10;
        }
        cache[sum]=true;
    	return;
	}
	for(int i=depth;i<n;i++){
		int temp;
		SWAP(available[depth],available[i],temp);
		permu(available,depth+1,n);
		SWAP(available[depth],available[i],temp);
	}
}

void recul(vector<vector<int>> &dice,int cnt){
    if(cnt==dice.size()){
    	permu(available,0,available.size());
    	return;
    }
    for(int i=0;i<dice.size();i++){
    	for(int j=0;j<dice[i].size();j++){
    		available.push_back(dice[cnt][j]);
    		recul(dice,cnt+1);
    		available.pop_back();
    	}
    	recul(dice,cnt+1);
    }
}

int main(){
    //vector<vector<int>> dice={{1,6,2,5,3,4},{9,9,1,0,7,8}};
    vector<vector<int>> dice={{0,1,5,3,9,2},{6,3,4,7,6,5},{2,1,0,4,8,7},{2,1,0,4,8,7}};
    recul(dice,0);
    int i;
    for(i=1;i<MAX;i++)
        if(!cache[i])break;
    cout<<i<<endl;
    return 0;
}
