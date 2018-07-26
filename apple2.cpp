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
        vector<int> dp(m + 1,0);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = i; j <= m; ++j)
            {
                dp[j] = dp[j] + dp[j - i];
            }
        }
 
        cout << dp[m] << endl;
    }
 
    return 0;
}
