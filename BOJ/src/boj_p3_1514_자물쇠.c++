#include <iostream>
#include <string>
#define MAX 100
using namespace std;
//시작이 다르면? 똑같이 i번재를 회전한다 해도 i-1이 다르게 회전해있으면 결과를 다르다. 하지만 앞에 맞춰져있다면>
//i번째에 
//3개씩 잘라서 생각한다면?
//그것마저 1개~3개 각각
//한 회전당 3점?
dp[i][1]=i번째를 디스크 하나씩 회전했을때 필요한 회전수
dp[i][1]=
bool dp[MAX][MAX][MAX];

int main(){
    int n;
    int ori[MAX+1],goal[MAX+1];
    string a,b;
    cin>>n;
    cin>>a>>b;
    for(int i=0;<n;i++){
        ori[i]=a[i]-'0';
        goal[i]=b[i]-'0';
    }
    
    for(int index=0;index<n;index++){
        //disc 수
        for(int i=1;i<=3;i++){
            //몇칸 회전
            for(int k=1;k<=3;k++){

            }
        }
    }
}