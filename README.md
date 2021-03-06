硬币表示问题——动态规划
===================

# 一. 问题

> 有数量不限的硬币，币值为25分、10分、5分和1分，请编写代码计算n分有几种表示法。

# 二. 求解

> 这是典型的动态规划问题，可以这样考虑：当只有1分的硬币时，n从1到n分别有多少种表示方法；当有1分和5分的硬币时，n从1到n分别有多少种表示方法，因此类推，直到将1分、5分、10分和25分的硬币全部使用完。采用数组coins=[1,5,10,25]来表示各种币值，dp[i][j]——前i种币种，总值为j的表示方法数，其中i表示前i种币值，j表示硬币总值。当硬币币值有i种，硬币总值为j的时候，硬币表示方法由两部分组成，一种是不采用第i种币值，总值为j的表示方法数，另一种是采用第i种币值，总值从j-coins[i]变到j的表示方法数，因此状态转移方程为dp[i][j]=dp[i-1][j]+dp[i][j-coins[i]]。代码如下：

```java
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        int[] coins = {1, 5, 10, 25};
        int[][] dp = new int[4][n + 1];

        for (int i = 0; i < 4; i++)
            dp[i][0] = 1; //第0行初始化为1

        for (int j = 1; j <= n; j++)
            dp[0][j] = 1; //第0列初始化为1

        for (int i = 1; i < 4; i++) {
            for (int j = 1; j <= n; j++) {
                
                if (j >= coins[i])
                    dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i]];
                
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }
        
        System.out.println(dp[3][n]);
    }
}

```

> 可进一步对代码进行空间优化，dp改为一维数组，代码如下：

```java

import java.util.Scanner;
public class Main {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        int[] coins = {1, 5, 10, 25};
        int[] dp=new int[n+1];
        dp[0]=1;

        for(int i=0;i<4;i++){
            for(int j=coins[i];j<=n;j++){
                
                dp[j]=dp[j]+dp[j-coins[i]];
            }
        }

        System.out.println(dp[n]);
    }
}
```

# 三. 扩展

## 1. 苹果放置问题

> 把 M 个同样的苹果放在 N 个同样的盘子里，允许有的盘子空着不放，问共有多少种不同的分法？注意：5、1、1 和 1、5、1 是同一种分法，即顺序无关。输入：7 3，输出：8。

> 与硬币问题相似，dp[i][j]表示i个盘子摆放j个苹果，当j>=i时，苹果数量多于盘子个数，分为两种情况，一种是i-1个盘子摆放j个苹果，表明有空盘；另一种是i个盘子，不留空盘，每个盘子放一个苹果，苹果总数从j-i变为j，因此状态转移方程为 dp[i][j]=dp[i-1][j]+dp[i][j-i]。当j<i时，苹果数量少于盘子个数，此时肯定存在空盘，空盘不影响，直接去掉，dp[i][j]=dp[i-1][j]。代码如下：

```C++
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

```

> 可进一步对代码进行空间优化，dp改为一维数组，代码如下：

```C++

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

```

## 2. 学生排列问题

> 有 n 个学生站成一排，每个学生有一个能力值，牛牛想从这 n 个学生中按照顺序选取 k 名学生，要求相邻两个学生的位置编号的差不超过 d，使得这 k 个学生的能力值的乘积最大，你能返回最大的乘积吗？输入一个整数 n (1 <= n <= 50)，表示学生的个数，接下来的一行，包含 n 个整数，按顺序表示每个学生的能力值 ai（-50 <= ai <= 50）。接下来的一行包含两个整数，k 和 d (1 <= k <= 10, 1 <= d <= 50)。输入 3   7 4 7    2 50 ，输出 49。

> 采用动态规划方法，假设学生能力为正，设置dp[k][n]，dp[i][j]表示选择学生数为i，最后一个选择的学生编号为j的情况下的最大乘积，dp[i][j]的值只与dp[i-1]中的各个项有关——最后一个人编号是j的情况下，倒数第二个人的编号只能是j-d,j-d-1,...,j-1，因此求dp[i-1][j-d]~dp[i-1][j-1]的最大值，再乘以a[j]就能得到dp[i][j]，其中dp[i-1]各项是由之前递推而来。

> 现在考虑学生能力为负的情况，由于负负得正，所以不仅需要保存当前状态下的最大值，还要保存最小值，这样遇到负值时，用最小值乘就可以得到真正的最大值。所以dp数组要设置为两个——dpmax和dpmin。

> 最后是边界的问题，由于是求乘积，所以在边界状态“选0个人”的情况下，数组值为1；其次，对于任意的i——选择i个学生，j——最后一个学生的编号至少为i。代码如下：

```C++
#include <iostream>
#include <algorithm>
using namespace std;
 
int n, k, d, a[50];
long long dmax[11][51], dmin[11][51];
 
int main()
{
	//	初始化边界
	fill(dmax[0], dmax[1], 1);
	fill(dmin[0], dmin[1], 1);
 
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	cin >> k >> d;
 
	for (int i = 1; i <= k; ++i)
		for (int j = i; j <= n; ++j) {	//	在选取i个人的情况下，j至少为i
			int s = max(i - 1, j - d);	//	同理s虽然从j - d开始枚举，但至少应为i - 1
			long long cmin = dmin[i - 1][s], cmax = dmax[i - 1][s];
 
			for (; s < j; ++s) {
				cmax = max(cmax, dmax[i - 1][s]);
				cmin = min(cmin, dmin[i - 1][s]);
			}
			//	状态转移方程
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

```


## 3. 硬币最少问题

> 假设有 1 元，3 元，5 元的硬币若干（无限），现在需要凑出 11 元，问如何组合才能使硬币的数量最少？

> dp[j]表示凑够j元所需要的最少硬币数，显然dp[0]=0，dp[1]=1，dp[2]=min(dp[2-2]+1,dp[2-1]+1)=1，这里以dp[2]为例，做个简单的分析，如果需要2块钱，那么可以将这个问题分解成更小的子问题来求解，即可以在dp[1]的基础上在拿1个硬币就可以凑到2块钱，或者是在dp[2-2]的基础上再拿一个2元的硬币即可达到要求，很容易得到状态转移方程为dp[j]=min(dp[j-coins[i]]+1)。代码如下：

```python
def coin_element(n,coins):

    dp=[0]*(n+1)

    for i in range(1,n+1):
        dp[i]=i
        for j in coins:
            if i-j>=0:
                dp[i]=min(dp[i],dp[i-j])+1
    return dp[n]


if __name__ == '__main__':
    n=11
    coins=[1,3,5]
    res=coin_element(n,coins)
    print(res)
```

## 4. 歌单组合问题

> 小Q有X首长度为A的不同的歌和Y首长度为B的不同的歌，现在小Q想用这些歌组成一个总长度正好为K的歌单，每首歌最多只能在歌单中出现一次，在不考虑歌单内歌曲的先后顺序的情况下，请问有多少种组成歌单的方法。

```shell
输入描述:
每个输入包含一个测试用例。
每个测试用例的第一行包含一个整数，表示歌单的总长度K(1<=K<=1000)。
接下来的一行包含四个正整数，分别表示歌的第一种长度A(A<=10)和数量X(X<=100)以及歌的第二种长度B(B<=10)和数量Y(Y<=100)。保证A不等于B。

输出描述:
输出一个整数,表示组成歌单的方法取模。因为答案可能会很大,输出对1000000007取模的结果。

输入例子1:
5
2 3 3 3

输出例子1:
9
```

> 将两种长度的歌的数量进行遍历，如果满足总长度为K，计算该数量的组合<a href="https://www.codecogs.com/eqnedit.php?latex=C_{n}^{m}" target="_blank"><img src="https://latex.codecogs.com/svg.latex?C_{n}^{m}" title="C_{n}^{m}" /></a>下共有多少种不同歌曲的组合方式，所以本题的关键是实现组合函数：<a href="https://www.codecogs.com/eqnedit.php?latex=C_{n}^{m}=\frac{n!}{m!*(n-m)!}" target="_blank"><img src="https://latex.codecogs.com/svg.latex?C_{n}^{m}=\frac{n!}{m!*(n-m)!}" title="C_{n}^{m}=\frac{n!}{m!*(n-m)!}" /></a> 。一般来说，时间复杂度是阶乘级O(n!)的函数是不可用的，这里需要用到杨辉三角，组合的递推公式为：<a href="https://www.codecogs.com/eqnedit.php?latex=C_{n}^{m}=C_{n-1}^{m}&space;&plus;&space;C_{n-1}^{m-1}" target="_blank"><img src="https://latex.codecogs.com/svg.latex?C_{n}^{m}=C_{n-1}^{m}&space;&plus;&space;C_{n-1}^{m-1}" title="C_{n}^{m}=C_{n-1}^{m} + C_{n-1}^{m-1}" /></a>。杨辉三角与组合之间的关系如图所示：

![image](https://github.com/ShaoQiBNU/coin/blob/master/1.png)

> 从上图可见，杨辉三角保存着所有组合数。所以，只要把部分杨辉三角保存起来，求解组合直接查表。对应的C[m][n]就是<a href="https://www.codecogs.com/eqnedit.php?latex=C_{n}^{m}" target="_blank"><img src="https://latex.codecogs.com/svg.latex?C_{n}^{m}" title="C_{n}^{m}" /></a>。 代码如下：

```C++
#include <bits/stdc++.h>
using namespace std;
long long c[101][101]; // 保存杨辉三角
const int mod = 1000000007;

void init(int size) {
  c[0][0] = 1;
  for (int i = 1; i != size; i++) {
    c[i][0] = 1;
    for (int j = 1; j != i+1; j++){
      // 杨辉三角规则：当前值是上一行的两个肩上的值之和
      c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
    }
  }
}
int main() {
    // 构建杨辉三角
    init(101);
    // 获取输入参数
    int k = 0;// 歌单总长度
    scanf("%d",&k);
    int a = 0; // 第一种歌曲长度
    int x = 0; // 第一种歌曲数量
    int b = 0; // 第二种歌曲长度
    int y = 0; // 第二种歌曲数量
    scanf("%d%d%d%d",&a,&x,&b,&y);
    
    int res=0;
    // 遍历第一种歌曲数量可选用的数目0~x
    for (int i = 0; i <= x; i++) {
        int sum_a = i*a; // 第一种歌曲长度和
        int sum_b = k-i*a; // 第二种歌曲长度和
        if (sum_a <= k // 选取的第一种歌曲长度和不超过歌单总长度
            && sum_b%b == 0 // 除去第一种歌曲长度和，剩余长度必须是第二种歌曲长度的整数倍
            && sum_b/b <= y // 第二种歌曲数目不能超过歌曲总数
           ){
           // 组成歌单数目
           int count = (c[x][i] * c[y][sum_b/b]) % mod;
           res = (res + count) % mod; // 因为可能不止一种方式，多种方式数目累加。
        }
    }
    printf("%d\n", res);
  return 0;
}
```


# 四. 辨析

> 有个小孩正在上楼梯，楼梯有n阶台阶，小孩一次可以上1阶、2阶、3阶。请实现一个方法，计算小孩有多少种上楼的方式。为了防止溢出，请将结果Mod 1000000007。给定一个正整数int n，请返回一个数，代表上楼的方式数。保证n小于等于100000。测试样例：1  返回：1。

> 此题求解依旧采用动态规划，最后一步可能是从第n-1阶往上走1阶、从第n-2阶往上走2阶或从第n-3阶往上走3阶。因此，抵达最后一阶的走法，抵达这最后三阶的方式的综合。代码如下：

```python
def stair_element(n):
    dp=[0]*(n+4)
    dp[0]=1
    dp[1]=1
    dp[2]=2
    dp[3]=4
    for i in range(4,n+1):
        for j in range(1,4):
            if (i-j)>0:
                dp[i]=(dp[i]+dp[i-j])%1000000007
    return dp[n]

if __name__ == '__main__':
    n=1
    res=stair_element(n)
    print(res)
```

> 注意，此题与上面的硬币表示问题有所区别，对于硬币表示问题，关心的是各个硬币的数量，不关心顺序的问题，而对于上楼梯，不仅涉及1,2,3阶的数量问题，还涉及顺序问题，因此上面硬币表示不能采用和上楼梯一样的动态转移方程求解。

