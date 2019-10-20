def solution(A):
    n = len(A)
    m = len(A[0])
    dp = [[''*(m*n)] * m for i in range(n)] 
    dp[n-1][m-1] = str(A[n-1][m-1])
   
    for i in range(m-2,-1,-1):
        dp[n-1][i] = str(A[n-1][i]) + dp[n-1][i+1]
      
    for i in range(n-2,-1,-1):
        dp[i][m-1] = str(A[i][m-1]) + dp[i+1][m-1] 

    for y in range(n-2,-1,-1):
        for x in range(m-2,-1,-1):
            strNum = str(A[y][x])
            if ( dp[y+1][x] >  dp[y][x+1]):
                dp[y][x] =  strNum + dp[y+1][x]
            else :
                dp[y][x]  = strNum + dp[y][x+1]
    return dp[0][0]


solution([[9, 9, 7], [9, 7, 2], [6, 9, 5], [9, 1, 2]])