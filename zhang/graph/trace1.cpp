#include <iostream>
#include <vector>
using namespace std;

int move_x[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int move_y[8] = {2, 1, -1, -2, -2, -1, 1, 2};

void Judge(vector<vector<int>> &pan, vector<vector<int>> &flag, vector<vector<int>> &path, int m, int n, int &edge, int count, int &found)
{
    if (found) //设定找到一次就可以退出了
        return;

    if (count >= edge * edge) //当记录次数等于8*8=64次，说明马已经踏过了所有棋盘
    {
        found += 1;
        //把记录的路径保存在path中
        for (int i = 0; i < edge; i++)
        {
            for (int j = 0; j < edge; j++)
                path[i][j] = flag[i][j];
        }
        return;
    }

    if (m > edge - 1 || n > edge - 1 || m < 0 || n < 0 || flag[m][n] != 0) //边界条件，出了边界就退回，悬崖勒马
        return;

    count++;            //满足在边界之内，没有被访问过，计数加1
    flag[m][n] = count; //对应节点记录访问顺序，第几次被访问的

    /*贪心算法,确定下一次的方向*/
    int count_next[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
    for (int i = 0; i < edge; i++)
    {
        int m_next = m + move_x[i];
        int n_next = n + move_y[i];
        if (m_next < edge && n_next < edge && m_next >= 0 && n_next >= 0 && flag[m_next][n_next] == 0)
        {
            count_next[i]++;
            for (int j = 0; j < edge; j++)
            {
                int m_next_next = m_next + move_x[j];
                int n_next_next = n_next + move_y[j];
                if (m_next_next < edge && n_next_next < edge && m_next_next >= 0 && n_next_next >= 0 && flag[m_next_next][n_next_next] == 0)
                    count_next[i]++;
            }
        }
    }

    int opt_direct = 0; //记录下一步的方向
    for (int i = 0; i < edge; i++)
    {
        if (count_next[opt_direct] == -1)
            opt_direct = i;
        if ((count_next[i] < count_next[opt_direct]) && count_next[i] != -1)
        {
            opt_direct = i;
        }
    }

    Judge(pan, flag, path, m + move_x[opt_direct], n + move_y[opt_direct], edge, count, found); //采用递归，进行下一步的搜索

    flag[m][n] = 0; //回溯，对应节点标记清零
}

int main()
{
    int m, n;
    int edge;
    int found = 0;
    cin >> edge >> m >> n;
    vector<vector<int>> pan(edge, vector<int>(edge, 0));
    vector<vector<int>> flag(edge, vector<int>(edge, 0));
    vector<vector<int>> path(edge, vector<int>(edge, 0));

    Judge(pan, flag, path, m, n, edge, 0, found);

    cout << found << endl;

    for (int i = 0; i < edge; i++)
    {
        for (int j = 0; j < edge; j++)
            cout << path[i][j] << " ";
        cout << endl;
    }
    system("pause");
    return 0;
}