#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <exception>
#include <iomanip>
#include <memory>
#include <sstream>
 
using namespace std;
 
int main(int argc, char** argv)
{
    int n,m;
    while (cin >> m >> n)
    {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1,0));
        dp[0][0] = 1;

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j <= m; ++j)
            {
                if (j >= i) dp[i][j] = dp[i - 1][j] + dp[i][j - i];
                else dp[i][j] = dp[i - 1][j];
            }
        }
 
        cout << dp[n][m] << endl;
    }
 
    return 0;
}


