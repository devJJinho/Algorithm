#include <string>
#include <vector>

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.04

*난이도 : Level 3
*개인 풀이 시간 : 20min 
*개인 난이도 : 3/5 
*분류 : 플로이드 와샬 (변형)
*풀이 :  -플로이드 와샬 알고리즘을 사용했지만 distance의 가중치가 없고 승패만 알면 되기 때문에 bool 배열을 사용했다.
         가중치 업데이트도 <승>의 업데이트로 정의했다.
        -순위가 명확한 선수의 정의 : 어떤 선수가 모든 선수와 <승> 관계로 이어져 있는 경우 순위가 명확하다고 할 수 있다.
        -예를 들어 4번 선수가 1,2,3번 선수의 <승> 관계에 포함되어 있고(1,2,3이 각각 3번을 이김) 4번 선수가 5,6번 선수를 이긴 경우
         4번 앞으로 3명, 뒤로 2명이 있는게 명확하기 때문에 4등이라고 할 수 있다.

        
*느낀점 : <승> 관계가 있다면 <패> 관계도 동시에 존재한다. 때문에 풀이 과정에서 <패>에 대한 처리도 해야되는가 고민했지만 단방향 그래프라 생각하고 풀이했다.
*/

int solution(int n, vector<vector<int>> results) {
    bool fight[101][101]={false};
    for(int i=0;i<results.size();i++){
        fight[results[i][0]][results[i][1]]=true;
    }
       
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                //i가 j를 이겼는가? 이것은 i가 k를 이기고(AND), K가 j를 이긴 경우에 그러하다.
                fight[i][j]=fight[i][j]||(fight[i][k]&&fight[k][j]);
            }
        }
    }
    int answer = 0;
    for(int p=1;p<=n;p++){
        int cnt=0;
        for(int i=1;i<=n;i++){
            //i를 이긴 사람의 수
            if(fight[i][p]) cnt++;
            //i가 이긴 사람의 수
            if(fight[p][i]) cnt++;
        }
        //본인을 제외한 모든 인원과 <승> 관계가 있으면 순위가 명확함
        if(cnt==n-1) answer++;
    }
    return answer;
}