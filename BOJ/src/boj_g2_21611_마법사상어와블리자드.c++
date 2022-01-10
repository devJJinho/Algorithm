#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 50
using namespace std;
// -> ^ <- v
const int dx[]={1,0,-1,0};
const int dy[]={0,-1,0,1};
const int convDir[]={0,1,3,2,0};

int n;
int map[MAX+1][MAX+1];
int index[MAX+1][MAX+1];
vector<int> list;

bool isValid(int x,int y){
    return x>=0&&x<n&&y>=0&&y<n;
}

void initIndex(){
    int cnt=0;
    int curX=(n-1)/2;
    int curY=(n-1)/2;
    index[curY][--curX]=cnt++;
    list.push_back(map[curY][curX]);
    index[++curY][curX]=cnt++;
    list.push_back(map[curY][curX]);
    int dir=0;
    int len=3;
    while(true){
        for(int j=0;j<2;j++){
            for(int i=0;i<len-1;i++){
                curX+=dx[dir];
                curY+=dy[dir];
                if(!isValid(curX,curY)) return;
                index[curY][curX]=cnt++;
                list.push_back(map[curY][curX]);
            }
            dir=(dir+1)%4;
        }
        ++len;
    }
}

int delNode(vector<int> &delList){
    int sum=0;
    for(auto i:delList){
        sum+=list[i];
        list[i]=-1;
    }
    while(true){
        auto iter=find(list.begin(),list.end(),-1);
        if(iter==list.end()) break;
        list.erase(iter);
    }
    return sum;
}
void resetArray(int size){
    int index=0;
    int start=0;
    int cnt=1;
    int value=list[start];
    vector<int> tempList(size,0);
    list.push_back(4);
    while(int tIndex=0<size&&index<list.size()-1){
        if(list[++index]==value)
            cnt++;
        else{
            tempList[tIndex++]=cnt;
            tempList[tIndex++]=value;
            value=list[index];
            start=index;
            cnt=1;
        }
    }
    list=tempList;
}
int findSerial(){
    int index=0;
    int start=0;
    int cnt=1;
    int value=list[start];
    vector<int> delList;
    list.push_back(4);
    while(index<list.size()-1){
        if(list[++index]==value)
            cnt++;
        else{
            if(cnt>=4){
                for(int i=start;i<start+cnt;i++)
                    delList.push_back(i);
            }
            cnt=1;
            start=index;
            value=list[start];
        }
    }
    list.pop_back();
    return delNode(delList);
}
int main(){
    int m;
    cin>>n>>m;
    int size=n*n-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cin>>map[i][j];
    }
    initIndex();
    int res=0;
    while(m--){
        int d,s;
        cin>>d>>s;
        int cx,cy;
        cx=cy=(n-1)/2;
        vector<int> delList;
        for(int i=0;i<s;i++){
            cx+=dx[convDir[d]];
            cy+=dy[convDir[d]];
            if(list[index[cy][cx]]!=0)
                delList.push_back(index[cy][cx]);
            else break;
        }
        delNode(delList);
        int score=findSerial();
        while(score){
            res+=score;
            score=findSerial();
        }
        resetArray(size);
    }
    cout<<res<<endl;
}