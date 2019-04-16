#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int N = 9;
int sol[N][N];              // Solution to the sudoku provided
vector<int> range[N][N];
int Init[N][N];

void initialize(/*vector<int> range[N][N]*/)
{
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; j++)
        {
            sol[i][j]=-1;
            if(Init[i][j] == 9)
            	for(int k = 0; k < N; k++)
                	range[i][j].push_back(k);
            else {
                range[i][j].push_back(Init[i][j]);
                sol[i][j] = Init[i][j];
            }
        }
}

bool Revise(int i, int j, int val/*, vector<int> range[N][N]*/)
{
    for(int r = 0; r < range[i][j].size(); r++)
    {
        if(range[i][j][r] == val)
        {
            range[i][j].erase(range[i][j].begin()+r);
            return true;
        }
    }
    return false;
}

bool valid(int i, int j, int val)          // Check all arc consistencies
{
    for(int k = 0; k < N; k++)
    {
        if((k!=j && sol[i][k] == val) || (k!=i && sol[k][j] == val)) return false;
    }
    int block_x = i/3, block_y = j/3;
    for(int len_x = 0; len_x < 3; len_x++)
    {
        for(int len_y = 0; len_y < 3; len_y++)
        {
            int x = block_x*3 + len_x;
            int y = block_y*3 + len_y;
            if(x==i && y==j) continue;
            if(sol[x][y] == val) return false;
        }
    }
    return true;
}
/*
int next(int i)
{
    return (i+1)%N;
}
*/
void print()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++) cout << sol[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

bool solve(int i, int j/*, vector<int> range[N][N]*/)
{
    //print();
    //cout << i << " " << j << endl;
    //print();
    if(i == N || j == N) {
        return true;
    }
    sol[i][j] = -1;
    vector<int> temp(range[i][j]);
    int v = 0;
    while(range[i][j].size() > 0)
    {
        int val = range[i][j][0];		
        if(valid(i,j,val))
        {
            bool col[N], row[N];
            
            // Reduce the domain
            for(int k = 0; k < N; k++)
            {
                if(k!=i)
                col[k] = Revise(k,j,val/*,range*/);
                if(k!=j)
                row[k] = Revise(i,k,val/*,range*/);
            }
            bool block[3][3];
            int block_x = i/3, block_y = j/3;
            for(int len_x = 0; len_x < 3; len_x++)
            {
                for(int len_y = 0; len_y < 3; len_y++)
                {
                    int x = block_x*3 + len_x;
                    int y = block_y*3 + len_y;
                    if(x==i && y==j) continue;
                    block[len_x][len_y] = Revise(x,y,val/*,range*/);
                }
            }

            sol[i][j] = val;
            int nxt_i = i;
            int nxt_j = j+1;
            if(nxt_j==N)
            {
                nxt_j = 0;
                ++nxt_i;
            }
            if(solve(nxt_i, nxt_j/*, range*/)) return true;             // If you found a solution then voila return it!
            else range[i][j].erase(range[i][j].begin());

            // Rectify your mistakes
            for(int k = 0; k < N; k++)
            {
                if(k != i && col[k])
                {
                    range[k][j].push_back(val);
                }
                if(k != j && row[k])
                {
                    range[i][k].push_back(val);
                }
            }
            for(int len_x = 0; len_x < 3; len_x++)
            {
                for(int len_y = 0; len_y < 3; len_y++)
                {
                    if(block[len_x][len_y])
                    {
                        int x = block_x*3 + len_x;
                        int y = block_y*3 + len_y;
                        if(x==i && y==j) continue;
                        range[x][y].push_back(val);
                    }
                }
            }
        }
        else
        {
            range[i][j].erase(range[i][j].begin());
            //cout << "Exiting at " << i << " " << j << endl;
            //cout << "test " << i << " " << j << " " << val << endl;
        }
    }
    range[i][j] = temp;
    sol[i][j] = -1;
    return false;
}


int main()
{
    //vector<int> range[N][N];
    cout << "Input the initial 9x9 grid" << endl;
    cout << "Convention 0-8 for valid number in grid and 9 if not known value" << endl;
    for(int i = 0; i < N; i++)
        cout << i+1 << " ";
    cout << endl;
    for(int i = 0; i < N; i++)
        cout << "= ";
    cout << endl;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
        {
            cin >> Init[i][j];
            //Init[i][j] = 9;
        }
    initialize();
    
    cout << endl;
    if(solve(0,0))
    {
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
                cout << sol[i][j] << " ";
            cout << endl;
        }
    }
    else
    {
        cout << "No solution possible\n";
    }
    return 0;
}
