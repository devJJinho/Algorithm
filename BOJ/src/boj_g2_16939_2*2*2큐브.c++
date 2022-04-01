#include <iostream>

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.04.01

*난이도 : G2
*개인 풀이 시간 : 1hour 
*개인 난이도 : 2/5
*분류 : 구현, 시뮬, 삼성문제
*풀이 : 회전할때 돌리는 면과, 마주치는 면을 ref할 수 있게 저장하고 그것을 활용하여 돌림

*느낀점 : 
        
*/

struct INFO{
    int x,y,dir;
};
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

class CUBE{
    int cube[6][2][2];
    //[회전축][회전축을 중심으로 돌렸을 때 같이 돌아가는 면]
    const int ref[6][4]={
        {3,1,4,5},
        {0,3,2,4},
        {3,1,4,5},
        {0,1,2,5},
        {0,1,2,5},
        {0,3,2,4}
    };
    //면끼리 마주치는 좌표와 방향
    //[회전 축][돌아가는 면]
    INFO point[6][6]={
        {{0,0,0},{0,0,3},{0,0,0},{0,0,3},{0,0,3},{0,0,3}},
        {{1,1,2},{0,0,0},{0,0,3},{1,0,1},{0,1,0},{0,0,0}},
        {{0,0,0},{0,1,3},{0,0,0},{0,1,3},{0,1,3},{0,1,3}},
        {{0,0,1},{0,0,1},{0,0,1},{0,0,0},{0,0,0},{1,1,0}},
        {{1,0,1},{1,0,1},{1,0,1},{0,0,0},{0,0,0},{0,1,0}},
        {{0,0,3},{0,0,0},{1,1,2},{0,1,0},{1,0,1},{0,0,0}},

    };
public:
    CUBE(){
        for(int i=0;i<6;i++){
            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    cin>>cube[i][j][k];
                }
            }
        }
    }
    void getRow(int *arr, int axis,int idx){
        INFO info=point[axis][idx];
        int x=info.x;
        int y=info.y;
        int dir=info.dir;
        for(int cnt=0;cnt<2;cnt++){
            int nx=x+dx[dir]*cnt;
            int ny=y+dy[dir]*cnt;
            arr[cnt]=cube[idx][ny][nx];
        }
    }

    void writeRow(int *arr,int axis, int idx){
        INFO info=point[axis][idx];
        int x=info.x;
        int y=info.y;
        int dir=info.dir;
        for(int cnt=0;cnt<2;cnt++){
            int nx=x+dx[dir]*cnt;
            int ny=y+dy[dir]*cnt;
            cube[idx][ny][nx]=arr[cnt];
        }
    }
    //이미 한번 돌아갔기 때문에 추가로 2번만 더 돌려줌
    void antiRotate(int axis){
        for(int i=0;i<2;i++){
            rotate(axis);
        }
    }
    void rotate(int axis){
        //[3]번째 담아두기
        int arr[2];
        //[3]에는 [2]를, [2]에는 [1]을 담는 식으로 복사
        getRow(arr,axis,ref[axis][3]);
        for(int i=3;i>=1;i--){
            int temp[2];
            getRow(temp,axis,ref[axis][i-1]);
            writeRow(temp,axis,ref[axis][i]);
        }
        //[0]에 있던 값은 [1]로 이미 복사되었음
        //위 포문 결과 {0,1,2,3} => {0,0,1,2}
        //때문에 [0]자리에 미리 복사해둔 [3]번 복사
        writeRow(arr,axis,ref[axis][0]);
    }
    
    bool check(){
        //6면이 모두 같은지?
        for(int i=0;i<6;i++){
            bool isSame=true;
            int pre=cube[i][0][0];
            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    if(cube[i][j][k]!=pre){
                        isSame=false;
                        break;
                    }
                }
            }
            //하나라도 다르면 바로 return false
            if(!isSame) return false;
        }
        return true;
    }

    bool checkSix(){
        //6면 모두 체크
        for(int i=0;i<6;i++){
            rotate(i);
            if(check()) return true;
            antiRotate(i);
            if(check()) return true;
            //원상복구를 위해 한번 더 회전
            rotate(i);
        }
        return false;
    }
};

int main(){
    CUBE cube;
    cout<<cube.checkSix()<<endl;
}