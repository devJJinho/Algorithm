#include <iostream>
#include <string.h>
#define SWAP(a,b,t) ((t)=(a),(a)=(b),(b)=(t))
#define MAX 20
using namespace std;

pair<bool,int> map[6][MAX][MAX];
const int dx[] = {0,0,-1,1};
const int dy[] = {-1,1,0,0};
int maxValue;
int N;

void merge(int depth){
	pair<bool,int> tt;
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            while(!map[depth][i][j].first){
	            int k = i + 1;
	            for(; k < N ; k++){
	            	if(map[depth][k][j].second > 0) break;
	            }
	            if(k < N){
	            	if(map[depth][i][j].second == 0){
	            		SWAP(map[depth][i][j],map[depth][k][j],tt);
	            	}
	            	else if(map[depth][k][j].first == false && map[depth][k][j].second == map[depth][i][j].second){
	        			map[depth][i][j].second += map[depth][k][j].second;
	            		map[depth][i][j].first = true;
	            		map[depth][k][j] = {false,0};
	            	}
	            	else break;
	            }
	            else break;
            }
        }
    }
}

void recul(int depth){
    if(depth >= 6){
        for(int i = 0 ; i < N ; i++){
            for(int j = 0 ; j < N ; j++){
                if(map[5][i][j].second > maxValue) maxValue = map[5][i][j].second;
            }
        }
        return;
    }
    pair<bool,int> t[N][N];
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            t[i][j] = map[depth-1][i][j];
            t[i][j].first = false;
        }
    }
    for(int dir = 0 ; dir < 4 ; dir++){
    	for(int i = 0 ; i < N ; i++){
        	for(int j = 0 ; j < N ; j++){
            	map[depth][i][j] = t[i][j];
        	}
    	}
        merge(depth);
        recul(depth + 1);
        if(dir == 3) break;
    	pair<bool,int> temp[N][N];
    	for(int i = 0 ; i < N ; i++){
        	for(int j = 0 ; j < N ; j++){
            	temp[i][j] = t[i][j];
        	}
    	} 
    	for(int i = 0 ; i < N ; i++){
        	for(int j = 0 ; j < N ; j++){
            	t[i][j] = temp[N-1-j][i];
        	}
    	}
    }
}
int main(){
    cin >> N;
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            scanf("%d", &map[0][i][j].second);
        }
    }
    recul(1);
    cout<<maxValue<<endl;
}