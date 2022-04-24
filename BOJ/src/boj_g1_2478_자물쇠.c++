#include <iostream>
#include <vector>
#define SWAP(a,b,t) ((t) = (a) , (a) = (b) , (b) = (t))
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.04.16

*난이도 : G1
*개인 풀이 시간 : 2hour 
*개인 난이도 : 2/5 
*분류 : 브루트포스 , 애드훅 , 시뮬
*풀이 : 

*느낀점 : 
*/

int N;
vector<int> dq;
int resP, resQ, index1, index3;

bool antiCheck(int p, int q){
    //연속되는 숫자인지 체크
    //범위의 시작의 앞(front - 1)과 범위 끝의 뒤(back + 1)부터 시작해서 1씩 증가하고 1씩 감소하는지 체크 이것을 앞뒤 좌표가 크로스 하기 전까지 진행
	int front = dq[(p - 1 + N) % N]  , back = dq[(q + 1) % N];
    while(p <= q){
    	front = (front + 1) % N;
    	back = (back -1 + N) % N;
        //하나씩 증가하지 않으면 return false;
    	if(front != dq[q] || back != dq[p]) return false;
        p++; q--;
    }
    return true;
}

bool func(){ 
    for(int p = 0 ; p < N ; p++){
        for(int q = p + 1 ; q < N ; q++){
            //브루트포스로 모든 경우 테스트
            if(antiCheck(p ,q)){
            	resP = p;
            	resQ = q;
                //swap 범위에 p가 포함되어 있으면 이땐 q가 맨 앞
                //맨앞 좌표가 첫번째에 몇번 shift 했냐를 결정하기 떄문에 필요함
            	int front = p == 0 ? dq[q] : dq[0];
                if(front == 0) continue;
            	index1 = front;
            	return true;
            }
        }
    }
    return false;
}

int main(){
    cin >> N;
    dq.resize(N);
    int idx = 0;
    int a;
    for(int i = 0 ; i < N ; i++){
        scanf("%d", &a);
        dq[idx++] = a - 1;
    }
    for(int i = 1 ; i < N ; i++){
    	int back = dq[N - 1];
        //하나씩 밀면서 브루트포스
		for(int  j = N - 1 ; j > 0 ; j--)
			dq[j] = dq[j - 1];
		dq[0] = back; 
        if(func()){
            index3 = i;
            break;
        }
    }
    cout << index1 << '\n';
    cout << resP + 1 << " " << resQ + 1 <<'\n';
    cout << index3 << '\n';
}