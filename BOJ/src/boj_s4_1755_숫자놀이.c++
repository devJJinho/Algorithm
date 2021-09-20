#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

/*
 
@author  :  Jinho Jeong
@date    :  2021.09.20

*난이도 : Silver 4
*개인 풀이 시간 : 30min
*개인 난이도 : 2/5
*분류 : 모듈러 연산, string
*풀이 : 최상위 자리수부터 하나씩 내려오는게 맞지만, 나누는 수 정하기가 쉽지 않아서 밑에서 부터 %10, /10을 하며 올라왔다.
       밑에서부터 한 만큼 string의 앞에 새로운 것을 삽입했어야 했는데, 스트링은 push_front()가 없었기 때문에 .append(자리수,붙일 문구)를 사용했다.
*느낀점 : 간단한 문제지만 한번 막히니까 꽤나 많은 시간이 필요했다. 라이브러리 활용을 잘 해야겠다.
        
*/

vector<string> c={"z","o","tw","th","fo","fi","si","se","e","n"};
vector<pair<string,int>> arr;
int main(){
    int m,n;
    cin>>m>>n;
    for(int i=m;i<=n;i++){
        string temp="";
        int index=i;
        while(index){
            if(index<10) {
                temp.insert(0,c[index]);
                break;
            }
            temp.insert(0,c[index%10]);
            index=index/10;
        }
        arr.push_back({temp,i});
    }
    sort(arr.begin(),arr.end());
    for(int i=0,cnt=1;i<arr.size();i++,cnt++){
        cout<<arr[i].second<<" ";
        if(cnt%10==0) cout<<endl;
    }
}