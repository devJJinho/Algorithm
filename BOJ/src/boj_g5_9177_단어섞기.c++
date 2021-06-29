#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int num;
    while(num--){
        string a,b,testCase;
        int aIndex,bIndex;
        aIndex=bIndex=0;

        cin>>a>>b>>testCase;

        for(int i=0;i<testCase.length();i++){
            if(a[aIndex]==testCase[i]||b[bIndex]
            //순서 보장이 안됨
            //재귀를 쓸까?
        }
    }
}