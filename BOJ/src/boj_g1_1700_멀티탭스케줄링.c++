#include <iostream>
#include <unordered_set>
#define MAX 100
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.04.23

*난이도 : G1
*개인 풀이 시간 : 1hour 
*개인 난이도 : 3/5 
*분류 : 그리디 , OS 알고리즘(OPT => 미래를 알고있단 가정하게 최적의 페이지 교체 방법)
*풀이 : 
      1. 콘센트에 여유가 있으면 바로 연결하기
      2. 만약 콘센트가 가득 찼다면 무조건 하나를 뽑아야함. 이때의 규칙이 메인
      3. 현재 콘센트에 있는 전자기기 중에서 미래에 더는 안쓰일 것을 뽑는게 가장 최고의 방법
      4. 만약 3의 그런한 것이 없다면 이때 가장 먼 미래에서 다시 쓰이는 것을 뽑는 것이 최선의 방법

*느낀점 : 
       
*/

unordered_set<int> outlet;
int cnt[MAX + 1];
int map[MAX + 1];
int N , K;
int unplugCnt;

bool plug(int i){
    //만약 플러그에 자리가 있다면 삽입하고 
    //cnt 감소
    if(outlet.size() < N){
        outlet.insert(map[i]);
        cnt[map[i]]--;
        return true;
    }
    return false;
}

int main(){
    cin >> N >> K;
    for(int i = 0 ; i < K ; i++){
        scanf("%d" , &map[i]);
        //cnt를 증가한 이유는 전체 기간에 대해 전자기기 인덱스 map[i]가 몇번 사용되는지 카운트함
        //내가 콘센트에 들어가면서 그 값을 감소시킨다면 해당 전자기기에 미래에 쓰일지 안쓰일 지 알 수 있음
        //예를들어 4번 전자기기가 총 5번쓰이는데 현 시점에 1만 남았다면 미래에 한번 더 쓰인다는 뜻, 만약 0이라면 다신 쓰이지 않기 때문에 플러그에서 뽑을 수 있음
        cnt[map[i]]++;
    }
    for(int i = 0 ; i < K ; i++){
        //만약 현재 플러그에 있다면? 넘어가기
        if(outlet.find(map[i]) != outlet.end()){
            cnt[map[i]]--;
            continue;
        }
        //자리 있으면 넣고 다음 전자기기로
        if(plug(i)) continue;
        //만약 N이 하나, 즉 콘센트 자리가 하나라면 같은 것이 나오지 않는 이상(그런 경우라면 위의 If 문에서 걸러졌음) 현재 것을 뽑고 새로 꼽아야함
        if(N == 1){
            outlet.clear();
            unplugCnt++;
            plug(i);
            continue;
        }
        //만약 현재 콘센트에 있는 것 중에 미래에 쓰이지 않는게 있다면 뽑기
        for(int a : outlet){
            if(cnt[a] == 0){
                outlet.erase(a);
                unplugCnt++;
                break;
            }
        }
        //여유가 있으면 넣고 다음 기기로
        if(plug(i)) continue;
        bool isFind = false;
        unordered_set<int> temp;
        for(int j = i ; j < K && !isFind ; j++){
            if(outlet.find(map[j]) != outlet.end()){
                temp.insert(map[j]);
                //Temp는 비어있고, 현재 콘센트에 있는 전자기기는 무조건 미래에 한번 더 쓰임(만약 그렇지 않다면 로직상 위에서 걸러졌음)
                //때문에 Temp의 사이즈는 무조건 현재 콘센트(outlet)의 사이즈와 같아지는 순간이 옴
                //사이즈로 비교한 것은 set은 중복이 자료구조 특성상 없기 때문, 즉 사이즈가 5라면 서로 다른 5개가 들어있음
                if(temp.size() == outlet.size() - 1){
                    //만약 딱 하나 차이가 난다 => 딱 하나 차이 나는 것이 가장 마지막에 다시 사용 되는 것. 그것을 찾아야함
                    for(int a : outlet){
                        //사이즈가 하나 작은 temP에 없는 것을 발견하면 그것을 콘센트에서 제거
                        if(temp.find(a) == temp.end()){
                            outlet.erase(a);
                            unplugCnt++;
                            isFind = true;
                            break;
                        }
                    }
                }
            }
        }
        //위 상황은 무조건 일어나기 때문에 일어났다는 전제하에 plug 진행
        plug(i);
    }
    cout << unplugCnt << endl;
}