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
