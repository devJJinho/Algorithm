#include <iostream>
#include <string.h>
#include <stack>
#include <vector>
#define MAX 100000

using namespace std;

struct INFO{
    int x,y,dir;
};
stack<int> button;
stack<INFO> st;
const int dx[]={0,1,1,1};
const int dy[]={0,-1,1,0};
bool map[10][MAX];
int dMap[MAX];
int N;
bool isInside(int x, int y){
	return x<N && y<10;
}
int main(){
    cin>>N;
    for(int i = 0 ; i < 10 ; i++){
        string str;
        cin>>str;
        for(int j = 0 ; j < N ; j++)
            map[i][j] = str[j] != 'X';
    }
    st.push({0,9,0});
    while(!st.empty()){
        auto cur = st.top();
        st.pop();
        dMap[cur.x] = cur.dir;
        if(cur.x == N-1) break;
        bool hori = false;
        int nx,ny;
        if(cur.y != 0){
            nx = cur.x + 1;
            ny = cur.y - 1;
            if(map[ny][nx]) st.push({nx,ny,1});
        }
        else hori = true;
        if(cur.y != 9){
            nx = cur.x + 1;
            ny = cur.y + 1;
            if(map[ny][nx]) st.push({nx,ny,2});
        }
        else hori = true;
        if(hori){
            if(map[cur.y][cur.x+1]) st.push({cur.x + 1,cur.y,3});
        }
    }
    vector<pair<int,int>> answer(MAX);
    int idx = 0;
    int preDir = dMap[0];
    int preClock = 0;
    bool isUp = false;
    for(int x = 1 ; x < N ; x++){
    	int dir = dMap[x];
    	if(!isUp && dir == 1){
    		isUp = true;
    		preClock = x - 1;
    	}
        else if(dir == 2 && preDir != 2){
        	isUp = false;
        	answer[idx++] = {preClock, x - preClock - 1};
        }
        preDir = dir;
    }
    if(isUp) answer[idx++] = {preClock, N - preClock - 1};
    cout<<idx<<endl;
    for(int i = 0 ; i < idx ; i++){
    	printf("%d %d\n",answer[i].first, answer[i].second);
    }
}
