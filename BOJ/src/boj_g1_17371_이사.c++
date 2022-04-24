#include <iostream>
#include <cmath>
#define INF 900000
#define MAX 1000
using namespace std;


/*
@author  :  Jinho Jeong
@date    :  2022.04.24

*난이도 : G1
*개인 풀이 시간 : 0.5hour 
*개인 난이도 : 2/5 
*분류 : 수학, 애드훅
*풀이 : 집의 위치와 편의시설 위치가 겹치지 않아야 한다는 조항이 없었음
       때문에 편의시설 위치에 집을 두면 가장 가까운 곳의 거리는 0, 따라서 가장 먼 거리의 편의시설 / 2가 (가장 먼 거리,가장 가까운 거리)의 평균
*느낀점 : 
       
*/


int N;
pair<int,int> ptr[MAX];

double getDist(int a, int b){
    return sqrt(pow(ptr[a].first - ptr[b].first , 2) + pow(ptr[a].second - ptr[b].second , 2));
}
int main(){
    cin >> N;
    int x , y;
    for(int i = 0 ; i < N ; i++){
    	cin >> x >> y;
        ptr[i] = {x , y};
    }
    double minValue = INF;
    int minX, minY;
    for(int i = 0 ; i < N ; i++){
        //가장 먼 거리도 0인 경우가 있기 대문에 -1로 초기화 해야 0일 때 한번 업데이트 되고 그때의 좌표가 들어감
    	double maxValue = -1;
    	int tx , ty;
        //가장 먼 거리의 가게를 찾음
        //양방향이기 때문에 J시작은 i+1에서
        for(int j = 0 ; j < N ; j++){
            double ret = getDist(i , j);
            if(maxValue < ret){
                maxValue = ret;
                tx = ptr[i].first;
                ty = ptr[i].second;
            }
        }
        //찾은 최대값이 작을 때, 즉 최대값의 최소를 찾는 과정
        if(minValue > maxValue){
        	minValue = maxValue;
        	minX = tx;
        	minY = ty;
        }
    }
    //그때의 좌표를 출력
    cout << minX << " " << minY << endl;
}