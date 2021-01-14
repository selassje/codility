
def getStr(x,y,A,dp) :
    n = len(A)
    m = len(A[0])
    result = list(' ' *(n+m))
    i = 0
    while x != -1:
        result[i] = chr(A[y][x] + ord('0'))
        x, y = dp[y][x]
        i = i + 1
    return ''.join(result)

def cmpStr(x1,y1,x2,y2,A,dp) :
    x1_org,y1_org = x1,y1
    x2_org,y2_org = x2,y2
    while x1 != -1:
        #print(x1,y1,x2,y2)
        if A[y1][x1] > A[y2][x2]:
            return (x1_org,y1_org)
        if A[y1][x1] < A[y2][x2]:
            return (x2_org,y2_org)
        x1, y1 = dp[y1][x1]
        x2, y2 = dp[y2][x2]
    return (x1_org,y1_org)

def solution(A):
    n = len(A)
    m = len(A[0])
    dp = [[(-1,-1)] * m for i in range(n)]
    #print(dp) 
    #sdp[n-1][m-1] = (-1,-1)
   
    for i in range(m-2,-1,-1):
        dp[n-1][i] = (i+1,n-1)
      
    for i in range(n-2,-1,-1):
        dp[i][m-1] = (m-1,i + 1) 

    for y in range(n-2,-1,-1):
        for x in range(m-2,-1,-1):
        #    print("enter " + str(x) + " " + str(y))
            dp[y][x] =  cmpStr(*(x+1,y),*(x,y+1), A, dp)
           
    return getStr(*(0,0),A,dp)


print(solution([[9, 9, 7], [9, 7, 2], [6, 9, 5], [9, 1, 2]]))