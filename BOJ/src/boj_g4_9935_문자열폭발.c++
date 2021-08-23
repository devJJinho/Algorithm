#include <iostream>
#include <string>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.06.24

*난이도 : G4
*개인 풀이 시간 : 12hr
*개인 난이도 : 4/5 
*분류 : 문자열, (knuth morris pratt algorithm)
*풀이 : 풀이 1 : knuth morris pratt algorithm 사용, 문자열 삭제를 *으로 바꾸는 것으로 구현, 삭제에선 이득이지만 인덱스 순회에서 너무 비효율적 => 시간초과
       풀이 2 : knuth morris pratt algorithm 사용, 문자열을 실제로 잘랐다. 라이브러리 substr 사용 => 시간초과
       풀이 3 : knuth morris pratt algorithm 사용 포기, answer 배열을 따로 두고 문자 하나씩 추가함. 패턴의 마지막과 같다면 패턴 전체와 매칭 시도-> 맞으면 string.pop_back()수행.

*느낀점 : knuth morris pratt algorithm은 전처리 한번만 하면 두고두고 쓰기 때문에 무조건 효율적이다 생각했지만, 이 알고리즘을 해당 PC에 적용시키는데 애를 먹었다.
        그리고 패턴의 길이가 최대 36이기 때문에 전체 탐색을 해도 사실 무담스럽지 않다.

        나는 string에서 실제 pop을 수행했지만, 답 배열의 길이를 a만큼 잡고, pop() 대신 인덱스만 뒤로 물려서 덮어쓰기를 수행하는 것이 더 효율적이다. 
        가능하면 더 간단한 코드로 더 넓을 조건을 커버하는 알고리즘을 짜는게 더 효율적이라 생각된다.
*/


string a,b;

int main(){
    cin>>a>>b;
    string answer;
    //패턴의 마지막 문자
    char bLast=b[b.size()-1];
    for(int i=0;i<a.size();i++){
        answer.push_back(a[i]);
        //마지막 문자와 같고 사이즈가 패턴보다 길다면
        if(answer.back()==bLast&&answer.size()>=b.size()){
            bool isCorrect=true;
            //패턴 전체와 매칭 시도
            for(int j=answer.size()-2,bIndex=b.size()-2;bIndex>=0;bIndex--,j--){
                if(answer[j]!=b[bIndex]) {
                    isCorrect=false;
                    break;
                }
            }
            //패턴과 매칭이 된다면 pop 수행,
            //index만 뒤로 물리는게 효율적이다. 그렇다면 push 대신 answer[index]=VALUE로 해야될것이다.
            if(isCorrect)
                for(int j=0;j<b.size();j++)
                    answer.pop_back();
        }
    }
    if(!answer.size())
        cout<<"FRULA"<<endl;
    else 
        cout<<answer<<endl;
}

/*

//// 문자 삭제 대신 *으로 변경했음  ////

삭제된 문자가 많은 경우 aIndex를 검토가 필요한 곳으로 내리기 또는 다음 검토할 곳으로 올리기 등에서 성능이 너무 안좋았다.
%%백준 기준으로 50% 채점에서 시간 초과 에러 발생%%


#include <iostream>
#include <string>
#include <vector>
using namespace std;

int failure[37];
string a,b;


%%knuth morris pratt algorithm구현을 위한 전처리%%

void setFail(){
    failure[0]=-1;
    for(int j=1;j<b.size();j++){
        int i=failure[j-1];
        while((b[j]!=b[i+1])&&i>=0)
            i=failure[i];
        if(b[j]==b[i+1])
            failure[j]=i+1;
        else   
            failure[j]=-1;
    }
}

int main(){
    cin>>a>>b;
    setFail();
    int aIndex=0,bIndex=0;
    while(aIndex<a.size()||bIndex==b.size()){
        if(a[aIndex]=='*') {
            aIndex++;
            continue;
        }
        if(bIndex==b.size()){
            int delIndex=aIndex-1;
            for(int cnt=0;cnt<b.size();delIndex--){
                if(a[delIndex]!='*'){
                    a[delIndex]='*';
                    cnt++;
                }
            }
            int bSize=b.size();
            int bcnt=0;
            while(delIndex>=0&&bcnt<=bSize){
                if(a[delIndex]!='*')
                    bcnt++;
                delIndex--;
            }
            aIndex=delIndex<0?0:delIndex;
            bIndex=0;
            continue;
        }
        if(a[aIndex]==b[bIndex]){
            bIndex++;
            aIndex++;
        }
        else if(bIndex==0)
            aIndex++;
        else
            bIndex=failure[bIndex-1]+1;
    }
    bool isPrinted=false;
    for(int i=0;i<a.size();i++){
        if(a[i]!='*') {
            cout<<a[i];
            isPrinted=true;
        }
    }
    if(!isPrinted) cout<<"FRULA"<<endl;
}

*/



/*

//// 문자열을 실제로 잘랐다 ////

string의 substr을 사용해서 실제 배열을 잘랐다.

#include <iostream>
#include <string>
using namespace std;

int failure[37];
string a,b;


void setFail(){
    failure[0]=-1;
    for(int j=1;j<b.size();j++){
        int i=failure[j-1];
        while((b[j]!=b[i+1])&&i>=0)
            i=failure[i];
        if(b[j]==b[i+1])
            failure[j]=i+1;
        else   
            failure[j]=-1;
    }
}

int main(){
    cin>>a>>b;
    setFail();
    int aIndex=0,bIndex=0;
    int bSize=b.size();
    while(aIndex<a.size()||bIndex==bSize){
        if(bIndex==b.size()){
            int start=aIndex-bSize<0?0:aIndex-bSize;
            a=a.substr(0,aIndex-bSize)+a.substr(aIndex);
            aIndex=start-bSize<0?0:start-bSize;
            bIndex=0;
            continue;
        }
        if(a[aIndex]==b[bIndex]){
            bIndex++;
            aIndex++;
        }
        else if(bIndex==0)
            aIndex++;
        else
            bIndex=failure[bIndex-1]+1;
    }
    bool isPrinted=false;
    for(int i=0;i<a.size();i++){
        cout<<a[i];
        isPrinted=true;
    }
    if(!isPrinted) cout<<"FRULA"<<endl;
}

*/

