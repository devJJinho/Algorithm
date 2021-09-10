#include <iostream>
#include <vector>

using namespace std;

/*
*난이도 : S2
*개인 풀이 시간 : 30min
*개인 난이도 : 2/5 
*분류 : 구현, DFS
*풀이 : isVisited를 1차원을 만들기 위해서 vector<>list를 전달했는데 괜히 복잡하게 풀었다.
       최대 50*50배열이기 때문에 그냥 2차원 배열의 isVisited를 두고 이중 포문을 돌면 됐다

*느낀점 : 최대한 간단하게 풀자. 아무리 아이디어가 좋아도 복잡한 코딩은 디버깅에 너무 많은 변수가 존재한다.
*/



int row,col;

const int dx[]={0,1,0,-1};
const int dy[]={-1,0,1,0};

bool isValid(int x,int y){
    return x>=0&&x<col&&y>=0&&y<row;
}
int findCluster(vector<vector<pair<bool,int>>> &map, vector<pair<int,int>> &point){
    vector<bool> isVisited((int)point.size(),false);
    int cnt=0;
    while(true){
        vector<int> stack;
        int i;
        for(i=0;i<isVisited.size();i++)
            if(!isVisited[i]) break;
        if(i==isVisited.size()) return cnt;
        stack.push_back(i);
        isVisited[i]=true;
        while(!stack.empty()){
            int cur=stack.back();
            int x=point[cur].first;
            int y=point[cur].second;
            stack.pop_back();
            for(int i=0;i<4;i++){
                int nx=x+dx[i];
                int ny=y+dy[i];
                if(isValid(nx,ny)){
                    pair<bool,int> nPoint=map[ny][nx];
                    if(nPoint.first&&!isVisited[nPoint.second]){
                        stack.push_back(nPoint.second);
                        isVisited[nPoint.second]=true;
                    }
                }
            }
        }
        cnt++;
    }
}

int main(){
    int n;
    cin>>n;
    while(n--){
        int num;
        cin>>row>>col>>num;
        vector<vector<pair<bool,int>>> map(row+1,vector<pair<bool,int>>(col+1,{false,0}));
        vector<pair<int,int>> point;
        for(int i=0;i<num;i++){
            int a,b;
            cin>>a>>b;
            point.push_back({b,a});
            map[a][b]={true,i};
        }
        cout<<findCluster(map,point)<<endl;
    }
    return 0;
}


/*

///////////////////
////2차원배열 순회////
//////////////////

#include <iostream>
#include <vector>

using namespace std;

int row,col;

const int dx[]={0,1,0,-1};
const int dy[]={-1,0,1,0};

bool isValid(int x,int y){
    return x>=0&&x<col&&y>=0&&y<row;
}

void dfs(bool map[][50], bool isVisited[][50],int x,int y){
    vector<pair<int,int>> stack;
    stack.push_back({x,y});
    isVisited[y][x]=true;
    while(!stack.empty()){
        pair<int,int> cur=stack.back();
        stack.pop_back();
        int x=cur.first;
        int y=cur.second;
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(isValid(nx,ny)){
                if(map[ny][nx]&&!isVisited[ny][nx]){
                    stack.push_back({nx,ny});
                    isVisited[ny][nx]=true;
                }
            }
        }
    }
}

int main(){
    int n;
    cin>>n;
    while(n--){
        int num;
        cin>>row>>col>>num;
        bool map[50][50]={false};
        bool isVisited[50][50]={false};
        for(int i=0;i<num;i++){
            int a,b;
            cin>>a>>b;
            map[a][b]=true;
        }
        int cnt=0;
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(map[i][j]&&!isVisited[i][j]){
                    dfs(map,isVisited,j,i);
                    cnt++;
                }
            }
        }
        cout<<cnt<<endl;
    }
    return 0;
}

*/