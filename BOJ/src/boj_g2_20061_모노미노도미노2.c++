#include <iostream>
#include <vector>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.23

*난이도 : G2
*개인 풀이 시간 : 1.5Hour 
*개인 난이도 : 2/5 
*분류 : 시뮬, 삼성문제, 구현, 배열
*풀이 : 파란색 블럭과 초록색 블럭을 통합해 하나의 클래스로 구현하고, 각각 주어지는 x,y좌표만 다르게 함.

*느낀점 :
*/


class BLOCK{
    bool map[4][6];
    int point;
public:
    BLOCK(){
        for(int i=0;i<4;i++){
            for(int j=0;j<6;j++){
                map[i][j]=0;
            }
        }
        point=0;
    }
    void move(vector<pair<int,int>> ls){
        bool hasEnd=false;
        //1에서 시작하는 이유는 x-1좌표에 둘 예정이기 때문
        for(int x=1;x<=6&&!hasEnd;x++){
            for(auto p:ls){
                int nx=p.first+x;
                //ls에 있는 어느 좌표 중 하나라도 벽이거나 다른 블럭을 만나면 break;
                if(map[p.second][nx]||x==6){
                    hasEnd=true;
                    break;
                }
            }
            if(hasEnd){
                //break 됐다면 그 열에는 다른 열이 있기 때문에 그 직전 열에 둔다
                for(auto p:ls){
                    map[p.second][p.first+x-1]=true;
                }
            }
        }
    }

    void checkBlock(){
        for(int j=5;j>=0;j--){
            bool full=true;
            for(int i=0;i<4;i++){
                if(!map[i][j]){
                    full=false;
                    break;
                }
            }
            //4개 모두 블럭이 있어야 full이 true임
            if(full){
                //shift하면 현재 J위치에 j-1열이 들어오기 때문에 현재 위치를 지켜야함
                //for문의 j--에 대응하기 위해 j++수행
                shift(j++);
                point++;
            }
        }
        // 0,1 열 체크, 그 중 1번째 열만 체크함. 이유는 0,1번째 열은 항상 비어있고 블럭이 쌓여도 1 -> 0 순으로 쌓임
        // 1번째 열을 체크해서 한칸 밀고 다시 1번째를 체크하면 결국은 0번째도 체크하는 격
        for(int i=0;i<4;i++){
            if(map[i][1]){
                shift(5);
                //처음부터 다시 보기 위해 i=-1, 역시 i++에 대응하기 위해
                i=-1;
            }
        }
    }

    //target열을 삭제함.
    void shift(int target){
        for(int i=0;i<4;i++){
            //target열부터 1번째 열까지 직전 열을 복사
            for(int j=target;j>0;j--){
                map[i][j]=map[i][j-1];
            }
        }
        //빈 열이 들어와야하기 때문에 마지막에 비움
        for(int i=0;i<4;i++)
            map[i][0]=0;
    }

    int getPoint(){
        return point;
    }
    int getBlock(){
        int cnt=0;
        for(int i=0;i<4;i++){
            for(int j=0;j<6;j++)
                if(map[i][j]) cnt++;
        }
        return cnt;
    }
};

int main(){
    BLOCK blue;
    BLOCK green;
    int N;
    cin>>N;
    int type,y,x;
    while(N--){
        vector<pair<int,int>> bp;
        vector<pair<int,int>> gp;
        scanf("%d %d %d",&type,&y,&x);
        switch(type){
            //기본적으로 파란색과 초록색은 x,y 좌표가 반대
            //그리고 주어진 좌표로 바로 블럭 내에 이동을 시킬 수 있게
            //x 또는 y 좌표를 0과 -1로 초기화함
            case 1:bp={{0,y}}; gp={{0,x}}; break;
            case 2:bp={{0,y},{-1,y}}; gp={{0,x},{0,x+1}}; break;
            default : bp={{0,y},{0,y+1}}; gp={{0,x},{-1,x}};
        }
        blue.move(bp);
        blue.checkBlock();
        green.move(gp);
        green.checkBlock();
    }
    cout<<blue.getPoint()+green.getPoint()<<endl;
    cout<<blue.getBlock()+green.getBlock()<<endl;
}