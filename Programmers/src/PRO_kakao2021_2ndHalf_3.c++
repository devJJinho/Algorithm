#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <unordered_map>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.11

*난이도 : 2/5
*개인 풀이 시간 : 30min
*개인 난이도 : 2/5 
*분류 : 문자열, 자료구조 사용, HASH or MAP, 검색에 유리한 자료구조
*풀이 : 자동차 출차 시스템과 비슷하게 코딩하려고 했다. 
       출차 정보를 다 받고 정렬해서 하는 것이 아니라 한줄이 들어올때 마다 처리했다.
       일단 한 차량 번호에 대해 두번째 차량 정보는 바로 요금을 계산해서 넣었고,
       하루가 마감하고 출차하지 않은 차가 있다면 그때 전체를 순회하며 나음 차를 23:59분 출차로 보고 계산했다.

*느낀점 : 다양한 자료구조의 멤버함수에 대해 공부할 필요가 있다. 막상 쓰려고 하면 어렵다.. 특히 iterator 관련
*/

int calMin(string time){
    int min=0;
    int hour=(time[0]-'0')*10+time[1]-'0';
    min+=hour*60;
    min+=(time[3]-'0')*10+time[4]-'0';
    return min;
}

int calFee(vector<int> &fees,int min){
    int fee=fees[1];
    min-=fees[0];
    if(min>0){
        int chunk=min/fees[2];
        if(min%fees[2]) ++chunk;
        fee+=chunk*fees[3];
    }
    return fee;
}
vector<int> solution(vector<int> fees, vector<string> records) {
    unordered_map<int,string> carWithTime;
    map<int,int> feesOnCar;
    for(auto st:records){
        stringstream ss;
        ss.str(st);
        string time,plate,action;
        ss>>time>>plate>>action;
        int nPlate=stoi(plate);
        if(carWithTime.find(nPlate)==carWithTime.end())
            carWithTime[nPlate]=time;
        else{
            string from=carWithTime[nPlate];
            int charged=calMin(time)-calMin(from);
            carWithTime.erase(nPlate);
            auto iter=feesOnCar.find(nPlate);
            if(iter==feesOnCar.end())
                feesOnCar.insert({nPlate,charged});
            else
                (*iter).second+=charged;
        }
    }
    for(auto st:carWithTime){
        int nPlate=st.first;
        string from=st.second;
        int charged=calMin("23:59")-calMin(from);
        auto iter=feesOnCar.find(nPlate);
            if(iter==feesOnCar.end())
                feesOnCar.insert({nPlate,charged});
            else
                (*iter).second+=charged;
    }
    vector<int> answer;
    for(auto a:feesOnCar){
        answer.push_back(calFee(fees,a.second));
    }
    return answer;
}