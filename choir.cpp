#include <iostream>
#include <algorithm>
using namespace std;
 
int n, k, d, a[50];
long long dmax[11][51], dmin[11][51];
 
int main()
{
    //  初始化边界
    fill(dmax[0], dmax[1], 1);
    fill(dmin[0], dmin[1], 1);
 
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    cin >> k >> d;
 
    for (int i = 1; i <= k; ++i)
        for (int j = i; j <= n; ++j) {  //  在选取i个人的情况下，j至少为i
            int s = max(i - 1, j - d);  //  同理s虽然从j - d开始枚举，但至少应为i - 1
            long long cmin = dmin[i - 1][s], cmax = dmax[i - 1][s];
 
            for (; s < j; ++s) {
                cmax = max(cmax, dmax[i - 1][s]);
                cmin = min(cmin, dmin[i - 1][s]);
            }
            //  状态转移方程
            if (a[j] < 0) {
                dmax[i][j] = cmin*a[j];
                dmin[i][j] = cmax*a[j];
            }
            else {
                dmax[i][j] = cmax*a[j];
                dmin[i][j] = cmin*a[j];
            }
        }
 
    // 遍历所有的最大值，其中的最大值即为最终答案
    long long ans = dmax[k][k];
    for (int i = k + 1; i <= n; ++i)
        ans = max(ans, dmax[k][i]);
    cout << ans << endl;
    return 0;
}