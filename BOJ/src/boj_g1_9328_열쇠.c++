#include <iostream>
#include <string>
#include <queue>
#define MAX 100
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.02.14

*난이도 : G1
*개인 풀이 시간 : 1.5hour
*개인 난이도 : 2/5 
*분류 : string, 구현, 시뮬
*풀이 : 가능성 있는 배열을 유지하며 나중에 키를 찾아 방문 할 수 있으면 그 위치부터 다시 탐색 진행

*느낀점 : 가장자리의 경우 열쇠를 찾고 바로 사방으로 탐색부터 하게 됨. 4방에 대해서 열쇠, 문에 대한 로직을 수행하기 때문에 원점에 대해서도 동일한 로직을 수행하기 위해 dir에 원점도 추가함

*/

char map[MAX+1][MAX+1];
bool isVisited[MAX+1][MAX+1];
const int dx[]={0,0,0,-1,1};
const int dy[]={0,-1,1,0,0};

int searchDoc(int r,int c){
    queue<pair<int,int>> startPoint;
    vector<char> keys;
    int docCnt=0;
    for(int i=0;i<r;i++){
        int dist=(i==0||i==r-1)?1:c-1;
        for(int j=0;j<c;j+=dist){
            if(map[i][j]!='*') {
                startPoint.push({j,i});
            }
        }
    }
    bool isOpened=true;
    while(isOpened){
        vector<pair<int,int>> st;
        int queSize=startPoint.size();
        for(int i=0;i<queSize;i++){
            auto front=startPoint.front();
            startPoint.pop();
            char block=map[front.second][front.first];
            if(!(block>='A'&&block<='Z')) {
                st.push_back(front);
                continue;
            }
            startPoint.push(front);
        }
        while(!st.empty()){
            auto cur=st.back();
            st.pop_back();
            for(int dir=0;dir<5;dir++){
                int nx=cur.first+dx[dir];
                int ny=cur.second+dy[dir];
                if(nx>=0&&nx<c&&ny>=0&&ny<r){
                    if(isVisited[ny][nx]||map[ny][nx]=='*') continue;
                    if(map[ny][nx]=='$') docCnt++;
                    else if(map[ny][nx]>='A'&&map[ny][nx]<='Z') {
                        startPoint.push({nx,ny});
                        continue;
                    }
                    else if(map[ny][nx]>='a'&&map[ny][nx]<='z') {
                        keys.push_back(map[ny][nx]);
                    }
                    st.push_back({nx,ny});
                    isVisited[ny][nx]=true;
                }
            }
        }
        isOpened=false;
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                for(int t=0;t<keys.size();t++){
                    if(map[i][j]+32==keys[t]) {
                        if(!isOpened) isOpened=true;
                        map[i][j]='.';
                    }
                }
            }
        }
        keys.clear();
    }
    return docCnt;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    while(n--){
        int r,c;
        cin>>r>>c;
        for(int i=0;i<r;i++){
            string temp;
            cin>>temp;
            for(int j=0;j<c;j++){
                isVisited[i][j]=false;
                map[i][j]=temp[j];
            }
        }
        string key;
        cin>>key;
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                for(int t=0;t<key.length();t++)
                    if(map[i][j]+32==key[t]) map[i][j]='.';
            }
        }
        cout<<searchDoc(r,c)<<endl;
    }
}