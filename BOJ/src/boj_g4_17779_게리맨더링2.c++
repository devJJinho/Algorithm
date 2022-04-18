#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#define ABS(a) ((a) < 0 ? -(a) : (a))
#define MAX 20
#define INF 40001
using namespace std;

/*

@author  :  Jinho Jeong
@date    :  2022.04.18

*난이도 : G4
*개인 풀이 시간 : 2 hour 
*개인 난이도 : 3/5 
*분류 : 구현, 시뮬, 배열, 수학
*풀이 : 
*느낀점 : 

*/

int N;
int map[MAX + 1][MAX + 1];
int minValue;
void cal(int x, int y, int d1, int d2){
    if(y + d1 + d2 > N || x - d1 < 1 || x + d2 > N) return;
    vector<int> sum = {0,0,0,0,0};
    for(int r = 1 ; r <= N ; r++){
        for(int c = 1 ; c <= N ; c++){
            // 5번째 구역 정하는 코드
            // x 범위에 들어오면
        	if(c >= x - d1 && c <= x + d2){
                // x에 해당하는 y 범위 구하기
                // 중심으로부터 얼마나 떨어져있는지를 활용해 구함
        		int upperY = y + d1 + d2 - ABS(c - (x - d1 + d2));
        		int lowerY = y + ABS(c - x);
                // 만약 Y 범위까지 만족하면
        		if(r >= lowerY && r <= upperY) {
                    // 5번째 구역에 더하고 continue;
        			sum[4] += map[r][c];
        			continue;
        		}
        	}
            // 5번째가 아니라면 1~4 구역에 나누기
            if(r < y + d1 && c <= x)
                sum[0] += map[r][c];
            else if(r <= y + d2 && x < c)
                sum[1] += map[r][c];
            else if(y + d1 <= r && c < x - d1 + d2)
                sum[2] += map[r][c];
            else if(y + d2 < r && x - d1 + d2 <= c)
                sum[3] += map[r][c];
        }
    }
    sort(sum.begin(), sum.end());
    //정렬 후 최대 - 최소 값 구하기
    minValue = min(minValue, sum[4] - sum[0]);
}

int main(){
    cin >> N;
    minValue = INF;
    for(int i = 1 ; i <= N ; i++){
        for(int j = 1 ; j <= N ; j++){
            scanf("%d" , &map[i][j]);
        }
    }
    for(int i = 1 ; i <= N ; i++){
        for(int j = 1 ; j <= N ; j++){
            for(int t = 1 ; t < N ; t++){
                for(int k = 1 ; k < N ; k++){
                    cal(i , j , t, k);
                }
            }
        }
    }
    cout << minValue << endl;
}