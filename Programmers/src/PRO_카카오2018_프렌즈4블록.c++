#include <string>
#include <vector>

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.07.06

*난이도 : Level 2
*개인 풀이 시간 : 2hr 
*개인 난이도 : 2/5
*분류 : 시뮬레이션
*풀이 : 2x2칸이 같은 캐릭터로 구성되어 있는 칸을 모두 찾으면 된다. 
       처음엔 스택 사용을 고려했는데 칸이 2x2로 고정되어 있어서 그럴 필요가 없었음.
*느낀점 : 실수를 줄이는 것이 중요함.
        처음부터 너무 어렵게 생각하지 말고 간단하게 생각해보자. -> 꼭 필요한 요소만 추려내기
        동적으로 boolean 배열을 생성하면 초기화를 해야된다. -> 애매하면 다 찍어보기
*/

const int dx[]={0,1,1};
const int dy[]={1,0,1};

bool isInside(int x,int y,int m,int n){
    return x>=0&&y>=0&&x<n&&y<m;
}

int solution(int m, int n, vector<string> board) {
    while(true){
        bool isBreaked=false;
        bool isChecked[m][n];
        
        //불리언 배열 초기화하기. 
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                isChecked[i][j]=false;
        
        for(int i=0;i<m-1;i++){
            for(int j=0;j<n-1;j++){
                if(board[i][j]=='*') continue;
                char curImoji=board[i][j];
                bool isAllSame=true;
                for(int k=0;k<3;k++){
                    int postX=j+dx[k];
                    int postY=i+dy[k];
                    if(board[postY][postX]!=curImoji){
                        isAllSame=false;
                        break;
                    }
                }
                //4개의 칸이 모두 같은 캐릭터인 경우
                if(isAllSame){
                    isBreaked=true;
                    isChecked[i][j]=true;
                    for(int k=0;k<3;k++){
                        int postX=j+dx[k];
                        int postY=i+dy[k];
                        isChecked[postY][postX]=true;
                    }
                }
            }
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(isChecked[i][j])
                    board[i][j]='*';
            }
        }
        //캐릭터 아래로 떨어지기
         for(int i=m-2;i>=0;i--){
            for(int j=0;j<n;j++){
                if(board[i][j]!='*'){
                    int index=i;
                    while(index+1<m){
                        if(board[index+1][j]=='*')
                            ++index;
                        else break;
                    }
                    if(index!=i){
                        board[index][j]=board[i][j];
                        board[i][j]='*';
                    }   
                }
            }
        }
        if(!isBreaked) break;
    }
    int cnt=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(board[i][j]=='*')cnt++;
        }
    }
    
    return cnt;
}