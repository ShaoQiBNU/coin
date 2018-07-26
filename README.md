硬币表示问题——动态规划
===================

# 一. 问题

> 有数量不限的硬币，币值为25分、10分、5分和1分，请编写代码计算n分有几种表示法。

# 二. 求解

> 这是典型的动态规划问题，可以这样考虑：当只有1分的硬币时，n从1到n分别有多少种表示方法；当有1分和5分的硬币时，n从1到n分别有多少种表示方法，因此类推，直到将1分、5分、10分和25分的硬币全部使用完。采用数组coins=[1,5,10,25]来表示各种币值，dp[i][j]——前i种币种，总值为j的表示方法数，其中i表示前i种币值，j表示硬币总值。当硬币币值有i种，硬币总值为j的时候，硬币表示方法由两部分组成，一种是不采用第i种币值，总值为j的表示方法数，另一种是采用第i种币值，总值从j-coins[i]变到j的表示方法数，因此状态转移方程为dp[i][j]=dp[i-1]+dp[j]+dp[i][j-coins[i]]。代码如下：

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
