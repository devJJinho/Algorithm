#include <iostream>
#define SWAP(a,b,t) ((t)=(a),(a)=(b),(b)=(t))
#define MAX 1<<7
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.04.08

*난이도 : G3
*개인 풀이 시간 : 1hour 
*개인 난이도 : 2/5 
*분류 : 구현, 시뮬, 배열 회전
*풀이 : 일부는 복사, 일부는 SWAP으로 구현함
*느낀점 : 
*/

int map[MAX][MAX];
int temp[MAX][MAX];
int N,R,NN;

void copyMap(){
    for(int i = 0 ; i < NN ; i++){
        for(int j = 0 ; j < NN ; j++){
            temp[i][j] = map[i][j];
        }
    }
}
void func1(int L){
    L=1<<L;
    int cnt = NN/L;
    int swapTemp;
    for(int i = 0 ; i < cnt ; i++){
        for(int j = 0 ; j < cnt ; j++){
            int bx = L*j;
            int by = L*i;
            for(int t = 0 ; t < L/2 ; t++){
                for(int k = 0 ; k < L ; k++){
                    SWAP(map[by + t][bx + k],map[L*(i+1)-1-t][bx + k],swapTemp);
                }
            }
        }
    }
}
void func2(int L){
    L=1<<L;
    int cnt = NN/L;
    int swapTemp;
    for(int i = 0 ; i < cnt ; i++){
        for(int j = 0 ; j < cnt ; j++){
            int bx = L*j;
            int by = L*i;
            for(int t = 0 ; t < L ; t++){
                for(int k = 0 ; k < L/2 ; k++){
                    SWAP(map[by + t][bx + k],map[by + t][L*(j+1)-1-k],swapTemp);
                }
            }
        }
    }
}
void func3(int L){
    L=1<<L;
    int cnt = NN/L;
    copyMap();
    for(int i = 0 ; i < cnt ; i++){
        for(int j = 0 ; j < cnt ; j++){
            int bx = L*j;
            int by = L*i;
            for(int t = 0 ; t < L ; t++){
                for(int k = 0 ; k < L ; k++){
                    map[by + t][bx + k] = temp[L*(i+1)-1-k][bx + t];
                }
            }
        }
    }
}
void func4(int L){
    L=1<<L;
    int cnt = NN/L;
    copyMap();
    for(int i = 0 ; i < cnt ; i++){
        for(int j = 0 ; j < cnt ; j++){
            int bx = L*j;
            int by = L*i;
            for(int t = 0 ; t < L ; t++){
                for(int k = 0 ; k < L ; k++){
                    map[by + t][bx + k] = temp[by + k][L*(j+1)-1-t];
                }
            }
        }
    }
}
void func5(int L){
    L=1<<L;
    int cnt = NN/L;
    int swapTemp;
    for(int i = 0 ; i < cnt/2 ; i++){
        for(int j = 0 ; j < cnt ; j++){
            int bx = L*j;
            int by = L*i;
            int nbx = L*j;
            int nby = L*(cnt-1-i);
            for(int t = 0 ; t < L ; t++){
                for(int k = 0 ; k < L ; k++){
                    SWAP(map[by + t][bx + k],map[nby + t][nbx + k],swapTemp);
                }
            }
        }
    }
}

void func6(int L){
    L=1<<L;
    int cnt = NN/L;
    int swapTemp;
    for(int i = 0 ; i < cnt ; i++){
        for(int j = 0 ; j < cnt/2 ; j++){
            int bx = L*j;
            int by = L*i;
            int nbx = L*(cnt-1-j);
            int nby = L*i;
            for(int t = 0 ; t < L ; t++){
                for(int k = 0 ; k < L ; k++){
                    SWAP(map[by + t][bx + k],map[nby + t][nbx + k],swapTemp);
                }
            }
        }
    }
}

void func7(int L){
    L=1<<L;
    int cnt = NN/L;
    copyMap();
    for(int i = 0 ; i < cnt ; i++){
        for(int j = 0 ; j < cnt ; j++){
            int bx = L*j;
            int by = L*i;
        	int nbx = by;
            int nby = L*(cnt-1-j);
            for(int t = 0 ; t < L ; t++){
                for(int k = 0 ; k < L ; k++){
                    map[by + t][bx + k]=temp[nby + t][nbx + k];
                }
            }
        }
    }
}
void func8(int L){
    L=1<<L;
    int cnt = NN/L;
    copyMap();
    for(int i = 0 ; i < cnt ; i++){
        for(int j = 0 ; j < cnt ; j++){
            int bx = L*j;
            int by = L*i;
            int nbx = L*(cnt-1-i);
            int nby = bx;
            for(int t = 0 ; t < L ; t++){
                for(int k = 0 ; k < L ; k++){
                    map[by + t][bx + k] = temp[nby + t][nbx + k];
                }
            }
        }
    }
}

int main(){
    cin>>N>>R;
    NN=1<<N;
    for(int i = 0 ; i < NN ; i++){
        for(int j = 0 ; j < NN ; j++){
            scanf("%d",&map[i][j]);
        }
    }
    int k,l;
    while(R--){
        scanf("%d %d",&k,&l);
        switch(k){
            case 1: func1(l); break;
            case 2: func2(l); break;
            case 3: func3(l); break;
            case 4: func4(l); break;
            case 5: func5(l); break;
            case 6: func6(l); break;
            case 7: func7(l); break;
            case 8: func8(l); break;
        }
    }
    for(int i = 0 ; i < NN ; i++){
        for(int j = 0 ; j < NN ; j++){
            printf("%d ",map[i][j]);
        }
        printf("\n");
    }
    return 0;
}