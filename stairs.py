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
