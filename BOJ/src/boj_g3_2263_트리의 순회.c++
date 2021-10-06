#include <iostream>
#define MAX 100001
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.10.06

*난이도 : G3
*개인 풀이 시간 : 1hr
*개인 난이도 : 2/5 
*분류 : 분할 정복, 재귀
*풀이 : post오더의 끝은 항상 루트이다.
       이 루트 값을 가지고 post오더에서 찾으면 그 값을 기준으로 좌측은 좌측 자식, 우측은 우측 자식이 된다.
       이렇게 나눈 뒤에 각 자식별로 재귀함수를 실행하면 된다. 그리고 각 단계마다 루트 값을 출력하면 됨

*느낀점 : 포스트오더의 특징은 파악했으나 이것을 인오더와 엮어서 재귀를 풀 생각은 못했다. 
         풀이를 참고해서 풀었음.

*/

int post[MAX];
int inOrder[MAX];
int index[MAX];
int n;

void preOrder(int postBegin,int postEnd,int inBegin,int inEnd){
    if(postBegin>postEnd||inBegin>inEnd) return;
    int root=post[postEnd];
    int rootIndex=index[post[postEnd]];
    int leftCnt=rootIndex-inBegin;
    cout<<root<<" ";
    preOrder(postBegin,postBegin+leftCnt-1,inBegin,rootIndex-1);
    preOrder(postBegin+leftCnt,postEnd-1,rootIndex+1,inEnd);
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>inOrder[i];
        index[inOrder[i]]=i;
    }
    for(int i=0;i<n;i++)
        cin>>post[i];
    preOrder(0,n-1,0,n-1);
    return 0;
}