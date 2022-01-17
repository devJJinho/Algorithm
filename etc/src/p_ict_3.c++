#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#define MAX 20
using namespace std;

struct info{
    int size,num;
    bool operator<(const info &b)const{
        return size<b.size;
    }
};

bool isChecked[MAX+1][MAX+1];

int n=7;
int m=8;

pair<int,int> findPoint(int xPoint,int yPoint,int boxSize){
    for(int y=yPoint;y>=0;y--){
        int x=yPoint==y?xPoint:0;
        for(;x<n;x++){
            bool isAvailable=true;
            for(int i=0;i<boxSize&&isAvailable;i++){
                for(int j=0;j<boxSize;j++){
                    int nx=x+j;
                    int ny=y-i;
                    if((nx>=n||ny<0)||isChecked[ny][nx]){
                        isAvailable=false;
                        break;
                    }
                }
            }
            if(isAvailable){
                return {x,y};
            }
        }
    }
    return {n,m};
}

vector<tuple<int,int,int>> solution(int n, int m, vector<info> rectangle){
    vector<tuple<int,int,int>> answer;
    sort(rectangle.begin(),rectangle.end());
    int xPoint=0;
    int yPoint=m-1;
    
    for(info box:rectangle){
        for(int cnt=0;cnt<box.num;cnt++){
            pair<int,int> nextPoint=findPoint(xPoint,yPoint,box.size);
            if(nextPoint==make_pair(n,m)) return answer;
            xPoint=nextPoint.first;
            yPoint=nextPoint.second;
            answer.push_back({xPoint,m-1-yPoint,box.size});
            int i,j;
            for(i=0;i<box.size;i++){
                for(j=0;j<box.size;j++){
                    isChecked[yPoint-i][xPoint+j]=true;
                }
            }
        }
    }
    return answer;
}
    
int main(){
   
    vector<info> rectangle={{3,2}, {1,4}, {4,2}};
    auto res=solution(n,m,rectangle);
    for(tuple temp:res){
        cout<<"["<<get<0>(temp) <<","<<get<1>(temp) <<","<<get<2>(temp)<<"]"<<endl;
    }
}