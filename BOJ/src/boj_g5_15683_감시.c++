#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.07.19

*난이도 : G5
*개인 풀이 시간 : 2hour 
*개인 난이도 : 3/5 
*분류 : 구현, 브루트포스
*풀이 : 각 cctv 범위가 겹쳐졌을때 중복으로 체크되는 것을 방지하기 위해서 set을 두고 좌표를 넣었다. set은 구조적으로 중복을 허용하지 않기 때문에 마지막엔 유효한 탐색 좌표만 남게된다.
       하지만 결론적으로 set의 사용이 성능을 저하시켰다. 매번 트리를 타고 내려가며 검색하는 오버헤드가 문제인 듯 하다.(오히려 멥에 #을 그리는 경우가 더 나았다.)
       그리고 모든 경우의 수를 체크하는 탓에 중복되는 연산이 굉장히 많다. 만약 cctv의 수가 조금만 더 늘어났더라면 이 코드는 돌아가지 않았을 것이다.
       
       !!만약 이전 상태의 방문 여부를 그대로 가져올 수 있다면 다시 계산하는 오버헤드는 줄어들것이다!!
       --좋은 방식--
       지금 8*8 배열의 체크여부 때문에 set 사용까지 하는 일을 벌렸다. 좋은 방법으로는 bool isChecked[9][row][col] (총 cctv가 8개이기 때문에)을 선언하고, 
       isChecked[0]은 모두 false로 두고, 매 깊이마다 isChecked[i+1]=[i]로 복사하면 재귀로 순회하더라도 아전 상태를 받아와서 새로 출발할 수 있다.
       배열의 복사는 8*8배열의 복사이고 전체 visited 테이블의 크기는 640byte로 굉장히 작다...
       

*느낀점 : 문제 난이도에 비해 너무 어렵게 접근하고 시간도 많이 걸렸다.
        실제로 #을 입력하는 일을 안한점과 movePreset을 선언한 점은 잘했다.
        isVisited 배열을 사용해서 다시 불어봐야겠다.
*/


struct info{
    int cctv,x,y,dir;
};
const int dx[]={0,0,1,0,-1};
const int dy[]={0,-1,0,1,0};
vector<vector<char>> map(8,vector<char>(8)); 
int row,col;
bool cmp(info a,info b){
    return a.cctv>b.cctv;
}
vector<vector<int>> movePreset[6]={
    {{0}},
    {{1},{2},{3},{4}},
    {{1,3},{2,4}},
    {{1,2},{2,3},{3,4},{4,1}},
    {{1,2,3},{2,3,4},{3,4,1},{4,1,2}},
    {{1,2,3,4}}
};
bool isValid(int x,int y){
    return x>=0&&x<col&&y>=0&&y<row;
}

int findBlind(vector<info> &cctv){
    set<pair<int,int>> looked;
    for(auto a:cctv){
        int x=a.x;
        int y=a.y;
        int index=a.dir;
        for(int j=0;j<movePreset[a.cctv][index].size();j++){
            int dir=movePreset[a.cctv][index][j];
            int nx=x;
            int ny=y;
            while(isValid(nx,ny)){
                if(map[ny][nx]=='6') break;
                if(map[ny][nx]=='0'){
                    //set은 어차피 중복을 허용하지 않기 때문에 중복값을 insert하면 아무일도 일어나지 않음
                    //if(looked.find({nx,ny})==looked.end()){
                        looked.insert({nx,ny});
                    //}
                }
                nx+=dx[dir];
                ny+=dy[dir];
            }
        }
        
    }
    return looked.size();
}
void recul(vector<info> &cctv,int index,int &maxValue){
    if(index==cctv.size()){
        maxValue=max(maxValue,findBlind(cctv));
        return;
    }
    int curCC=cctv[index].cctv;
    for(int i=0;i<movePreset[curCC].size();i++){
        cctv[index].dir=i;
        recul(cctv,index+1,maxValue);
    }
}
int main(){
    cin>>row>>col;
    vector<info> cctv;
    int cnt=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cin>>map[i][j];
            if(map[i][j]=='0') cnt++;
            else if(map[i][j]-'0'>=1&&map[i][j]-'0'<=5){
                cctv.push_back({map[i][j]-'0',j,i,0});
            }
        }
    }
    int maxValue=0;
    //5가 나중에 나오는 것 보다 처음에 나오는게 오버헤드가 줄어들듯 하여 sorting 했으나 유의미한 차이는 없었음
    sort(cctv.begin(),cctv.end(),cmp);
    recul(cctv,0,maxValue);
    cout<<cnt-maxValue<<endl;
}


/*

//다시 풀때 참고할 코드

#include<stdio.h>
#include<string.h>
short N, M, A[10][10], ans=64, K;
short dir[5][4][4]={{{0},{1},{2},{3}},
			{{0,2},{1,3}},
			{{0,1},{1,2},{2,3},{3,0}},
			{{0,1,2},{1,2,3},{2,3,0},{3,0,1}},
			{{0,1,2,3}}};
short fs[5]={4, 2, 4, 4, 1}, sc[5]={1, 2, 2, 3, 4};
short cctv[8][2], cctvn[8], idx;
short dr[4]={-1, 0, 1, 0}, dc[4]={0, 1, 0, -1};
bool chk[9][10][10];
void sol(short n, short sum){
	if(n==idx){
		if(sum<ans)	ans=sum;
		return;
	}
	int t=cctvn[n];
	for(int i=0;i<fs[t];++i){
		memcpy(chk[n+1], chk[n], 100);
		short x=0;
		for(int j=0;j<sc[t];++j){
			short d=dir[t][i][j];
			for(short r=cctv[n][0], c=cctv[n][1];A[r][c]!=6;r+=dr[d], c+=dc[d]){
				if(!chk[n+1][r][c]){
					chk[n+1][r][c]=1;
					++x;
				}
			}
		}
		sol(n+1, sum-x);
	}
}
int main(){
	scanf("%hi %hi", &N, &M);
	for(int i=0;i<M+2;++i){
		A[0][i]=A[N+1][i]=6;
	}
	for(int i=1;i<=N;++i){
		A[i][0]=A[i][M+1]=6;
		for(int j=1;j<=M;++j){
			scanf("%hi", &A[i][j]);
			if(A[i][j]==6)	++K;
			else if(A[i][j]){
				cctvn[idx]=A[i][j]-1;
				cctv[idx][0]=i, cctv[idx][1]=j;
				++idx;
			}
		}
	}
	sol(0, N*M-K);
	printf("%hi\n", ans);
	return 0;
}

*/