#include <iostream>
#define MAX 20

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.07.30

*난이도 : G2
*개인 풀이 시간 : 3hour 
*개인 난이도 : 3/5 
*분류 : 구현+DFS
*풀이 : 재귀로 풀었다. 배열 관리는 '동적 할당+배열 포인터 전달'을 사용했다.
*느낀점 : (
        잘한점:
            *바로 재귀를 사용한 점
            *복잡한 설계였지만 비교적 수월하게 구현한 점
            *삼중포인터를 잘 이해하고 사용한 점.
        못한점:
            *굉장히 복잡하게 풀었다.
            *디버깅에 상당한 시간을 들였다. 코테 환경이었다면 반례가 부족해 디버깅에 실패했을 것이다.
            *상하좌우로 기울이는 동작을 나름 for문의 시작점,index를 구분함으로써 간단히 하려고 했지만,, 가장 좋은 방법으론 up()만 구현하고 배열을 90도씩 회전하는 방식이 있었다.
            *memcopy를 사용하지 않음.
            *구조체 내에 배열을 선언하고 멤버 함수로 회전, up를 구현할 수 도 있었다. 
    )
*/

struct info{
    int value;
    bool isComb;
};

struct index{
    bool x,y;
};

//상하좌우 기울임에 따라 배열 탐색 방식을 조절하기 위해 사용함(연속된 수 3개에 대응하기 위해)
index moveMap[]={
    {true,true},
    {true,false},
    {true,true},
    {false,true}
};

//상하좌우
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

int square;

bool isInside(int x,int y){
    return x<square&&x>=0&&y>=0&&y<square;
}

/*
2차원 배열의 copy
꼭 외부에서 newMap 포인터를 선언하고 전달해야된다.
함수 내에서 newMap 포인터를 선언하고 return하면 생명주기가 끝나기 때문에 외부에서 확인 할 수 없음.
*/
void copyMap(info ***curMap,info ***newMap){
    *newMap=new info*[square];
    for(int i=0;i<square;i++){
        (*newMap)[i]=new info[square];
        for(int j=0;j<square;j++){
            (*newMap)[i][j].value=(*curMap)[i][j].value;
            (*newMap)[i][j].isComb=false;
        }
    }
}

int findMax(info ***board){
    int max=0;
    for(int i=0;i<square;i++){
        for(int j=0;j<square;j++){
            int value=(*board)[i][j].value;
            if(value){
                if(value>max) max=value;
            }
        }
    }
    return max;
}

int recul_move(info ***curMap,int cnt){
    int maxValue=0;
    if(cnt<=5){
        for(int dir=0;dir<4;dir++){
        	info **newMap;
        	copyMap(curMap,&newMap);
            //상화좌우 움직임에 따라 map 순회 시작점을 다들게 함.
            int i=moveMap[dir].y?0:square-1;
            int iIndex=moveMap[dir].y?1:-1;
            for(;i<square&&i>=0;i+=iIndex){
                int j=moveMap[dir].x?0:square-1;
                int jIndex=moveMap[dir].x?1:-1;
                for(;j<square&&j>=0;j+=jIndex){
                    if((newMap)[i][j].value){
                        int x=j;
                        int nx=j;
                        int y=i;
                        int ny=i;
                        bool isCombine=false;
                        while(true){
                            nx+=dx[dir];
                            ny+=dy[dir];
                            if(!isInside(nx,ny)) {
                                break;
                                }
                            //합칠 수 있다면 x,y 값을 nx,ny 값으로 업데이트 하고 break;
                            else if((newMap)[ny][nx].value==(newMap)[i][j].value&&!(newMap)[ny][nx].isComb&&!(newMap)[i][j].isComb){
                                x=nx;
                                y=ny;
                                isCombine=true;
                                break;
                            }
                            //합칠 수 없는 블럭을 만난경우 그냥 break; x,y 값은 직전 값을 가지고 있다.
                            else if((newMap)[ny][nx].value) break;
                            x=nx;
                            y=ny;
                        }
                        //기울임을 통해 블럭이 움직였다면 이동
                        if(x!=j||y!=i){
	                        (newMap)[y][x].value+=(newMap)[i][j].value;
                            //합쳐진거라면 isComb를 true, 그냥 이동만 했다면 false;
	                        newMap[y][x].isComb=isCombine?true:false;
	                        (newMap)[i][j].value=0;
	                        newMap[i][j].isComb=false;
                        }
                    }
                }
            }
            //각 방향별로 최대값을 모아본다.
            maxValue=max(maxValue,recul_move(&newMap,cnt+1));
        }
        //4방향을 다 보고는 그 중 최대값을 return;
        return maxValue;
    }
    else{
        //기울인 횟수가 5회 이상이라면 map의 최대값만 return
        return findMax(curMap);
    }
}

int main(){
    int i,j;
    cin>>square;
    info **map=new info*[square];
    for(i=0;i<square;i++){
        map[i]=new info[square];
        for(j=0;j<square;j++){
            int value;
            cin>>value;
            map[i][j]={value,false};
        }
    }
    int max=recul_move(&map,1);
    cout<<max;
    return 0;
}




/*


Reference Code:

#include<stdio.h>
#include<memory.h>

int ans, N, i, j;
struct board{
	int t[20][20];
	void r90(){
		int t2[20][20];
		for(i = 0; i < N; i++){
			for(j = 0; j < N; j++){
				t2[i][j] = t[N-j-1][i];
			}
		}
		memcpy(t, t2, sizeof(t));
	}
	void up(){
		int t2[20][20];
		for(i = 0; i < N; i++){
			int c = -1, d = 0;
			for(j = 0; j < N; j++){
				if( t[i][j] == 0 );
				else if( d && t[i][j] == t2[i][c] ) t2[i][c] *= 2, d = 0;
				else t2[i][++c] = t[i][j], d = 1;
			}
			for(c++; c < N; c++) t2[i][c] = 0;
		}
		memcpy(t, t2, sizeof(t));
	}
	void max_value(){
		for(i = 0; i < N; i++){
			for(j = 0; j < N; j++){
				if( ans < t[i][j] ) ans = t[i][j];
			}
		}
	}
};

void dfs(board c, int l)
{
	if( l >= 5 ){
		c.max_value();
		return;
	}
	for(int i = 0; i < 4; i++){
		board d = c;
		d.up();
		dfs(d, l+1);
		c.r90();
	}
}

int main()
{
	board c;
	scanf("%d", &N);
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++) scanf("%d", c.t[i] + j);
	}dfs(c, 0);
	printf("%d\n", ans);
}


*/