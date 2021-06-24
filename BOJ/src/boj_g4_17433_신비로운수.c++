#include <vector>
#include <iostream>

#define abs(a) (((a)<(0))?-(a):(a))

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.06.24

*난이도 : G4
*개인 풀이 시간 : 4hr 
*개인 난이도 : 3/5 
*분류 : 수학적 공식, 최대공약수(GCD)
*풀이 : M으로 나눴을 때 각각은 나머지가 있지만 같은 나머지기 때문에 뺐을때 M으로 나누어떨어진다.
       따라서  각 수 사이의 차들의 최대공약수가 가능한 M의 최대값이다.
*느낀점 : 수학적 공식을 생각하기까지 많은 시간이 걸렸다. 
        시험장에서 이런 문제를 만났을 때 바로 생각해낼 수 있을지 걱정이다. 
        유사한 경험을 통해 유도까지 시간을 줄이는 것이 중요해보인다.

        1. 패턴이 있는지
        2. 전처리 필요한지
        (제한사항을 보고 Brute force로 할 문제인지 아닌지 판단을 한다.)
*/

//최대공약수 구하기
int gcd(int a,int b){
    int temp;
    if(a<b){
        temp=a;
        a=b;
        b=temp;
    }
    int n;
    //b==0일 때 a값을 gcd로 본다. 즉 a%b==0일때 b값.
    while(b!=0){
        n=a%b;
        a=b;
        b=n;
    }
    return a;
}

int main(){
    int num;
    cin>>num;
    while(num--){
        int len;
        int cnt=0;
        vector<int> arr;
        vector<int> gap;
        cin>>len;
        for(int i=0;i<len;i++){
            int temp;
            cin>>temp;
            arr.push_back(temp);
        }
        for(int i=1;i<len;i++){
            //차이가 0인 경우는 넣지 않겠다
            if(arr[i]==arr[i-1]){
                cnt++;
                continue;
            }
            gap.push_back(abs(arr[i]-arr[i-1]));
        }
        if(cnt==len-1){
            cout<<"INFINITY"<<endl;
            continue;
        }
        int answer=gap[0];
        for(int i=1;i<gap.size();i++){
            answer=gcd(answer,gap[i]);
        }
        cout<<answer<<endl;
    }
}