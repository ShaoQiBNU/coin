def apple_element(m,n):
    
    if n==0:
        return 0
    
    if m==0:
        return 1

    if m<n:
        return apple_element(m,m)
    
    else:
        return apple_element(m,n-1)+apple_element(m-n,n)

def apple_element2(m,n):
    dp=[0]*(m+1)
    dp[0]=1

    for i in range(1,n+1):
        for j in range(i,m+1):
            dp[j]=dp[j]+dp[j-i]
    return dp[m]


if __name__ == '__main__':
    m=350
    n=30
    
    #res=apple_element(m,n)
    #print(res)
    
    res=apple_element2(m,n)
    print(res)
