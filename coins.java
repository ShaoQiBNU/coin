
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