#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#define INF 999
#define MAX 100

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.07.19

*난이도 : G2
*개인 풀이 시간 : 3hour 
*개인 난이도 : 2/5 
*분류 : 구현+BFS
*풀이 : n진수로 변환하는 과정에서 차례대로 stack에 넣으면 자연스럽게 reverse 배열이 만들어짐.
*느낀점 : (
        문제 자체는 굉장히 까다로운데 난이도를 위해 제한 사항을 많이 뒀다.(예) 동시에 떨어지는 클러스터는 하나, 아랫면이 다른 클러스터 또는 바닥 닿을때 까지
        문제+제한 사항을 모두 코드로 녹여내는 것이 쉽지 않았다. 그리고 문제는 풀었지만 좋은 구조로 푼거 같진 않다.
*/

const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};

struct info
{
    int x, y;
};

char map[MAX + 2][MAX + 2];
queue<int> crushArray;
int row, col;

bool isValid(int x, int y)
{
    return x >= 1 && x <= col && y >= 1 && y <= row;
}

void crush(int y,bool isOdd)
{
    int x = isOdd? 1:col;
    int index=isOdd?1:-1;
    while (map[y][x] != 'x' && x <= col&&x>=1)
    {
        x+=index;
    }
    if (x>col||x<1)
        return;
    map[y][x] = '.';
    
    queue<info> mineral;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!isValid(x, y))
            continue;
        if (map[ny][nx] == 'x')
        {
            mineral.push({nx, ny});
        }
    }
    while (!mineral.empty())
    {
        info curInfo = mineral.front();
        mineral.pop();
        bool isTouch=false;
        bool visited[MAX + 2][MAX + 2]={false};

        queue<info> minQue;
        minQue.push(curInfo);
        visited[curInfo.y][curInfo.x] = true;
        
        while (!minQue.empty())
        {
            info curInfo = minQue.front();
            minQue.pop();
            for (int u = 0; u < 4; u++)
            {
                int nx = curInfo.x + dx[u];
                int ny = curInfo.y + dy[u];
                if (!isValid(nx, ny))
                    continue;
                if (map[ny][nx]=='x'&&ny == row){
                    isTouch = true;
                }
                if (map[ny][nx] == 'x' && !visited[ny][nx])
                {
                    minQue.push({nx, ny});
                    visited[ny][nx] = true;
                }
            }
        }

        if (!isTouch)
        {
            int diff = INF;
            for (int i = 1; i <= col; i++)
            {
                int lastMin=row+1;
                int j;
                for (j = row; j >= 1; j--)
                {
                    if (map[j][i] == 'x' && !visited[j][i]){
                        lastMin = j;
                    }
                    if (visited[j][i])
                        break;
                }
                if(j==0) continue;
                diff = min(diff, lastMin - j);
            }
			diff--;
            
            for (int i = row; i >= 1; i--)
            {
                for (int j = 1; j <= col; j++)
                {
                    if (visited[i][j])
                    {
                        map[i + diff][j] = map[i][j];
                        map[i][j]='.';
                    }
                }
            }
            return;
        }
    }
}

int main()
{
    int i, j;
    cin >> row >> col;
    for (i = 1; i <= row; i++)
    {
        string temp;
        cin >> temp;
        for (j = 1; j <= col; j++)
            map[i][j] = temp[j - 1];
    }
    int num;
    cin >> num;
    for (i = 0; i < num; i++)
    {
        int temp;
        cin >> temp;
        crushArray.push(temp);
    }
    bool isOdd=true;
    while (!crushArray.empty())
    {
        int crushRow = crushArray.front();
        crushArray.pop();
        crush(row+1-crushRow,isOdd);
        isOdd=!isOdd;
    }
    
    for(i=1;i<=row;i++){
    	for(j=1;j<=col;j++){
    		cout<<map[i][j];
    	}
    	cout<<endl;
    }
}