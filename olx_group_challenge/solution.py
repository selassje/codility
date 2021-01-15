def solution(juice, capacity):
    n = len(juice)
    glasses = [(juice[i], capacity[i]) for i in range(0, n)]
    sorted_glasses = sorted(glasses)
    partial_sums = [0 for i in range(0, n)]
    partial_sums[0] = sorted_glasses[0][0]
    for i in range(1, n ):
        partial_sums[i] = partial_sums[i - 1] + sorted_glasses[i][0] 
        
    def find_in_partial_sum(s, e, target) :
        assert(e >= s)
        if partial_sums[s] > target:
            return s
        if partial_sums[e] <= target:
            return e + 1         
        while e - s != 1:
            mid_index = s + int((e - s) / 2)
            if partial_sums[mid_index] <= target:
                s = mid_index
            else:
                e = mid_index
        assert(partial_sums[s] <= target and partial_sums[e] > target) 
        return s + 1
    
    
    def solve_for_juice(j):
        capacity = sorted_glasses[j][1] 
        space = capacity - sorted_glasses[j][0]
        if partial_sums[j] <= capacity:
            return find_in_partial_sum(j, n - 1, capacity) 
        else:
            return find_in_partial_sum(0, j - 1 , space) + 1
               
    max_flavours = 1
    for j in range(0, n) :
        max_flavours = max(max_flavours, solve_for_juice(j))
        
    return max_flavours
    


print("TC1: ",solution( [10, 2, 1, 1], [10, 3, 2, 2]))
print("TC2: ",solution( [1, 2, 3, 4], [3, 6, 4, 4]))
print("TC3: ",solution( [2, 3 ], [3, 4]))
print("TC4: ",solution( [1,1,5], [6,5,8]))
print("TC5: ",solution([4, 3, 1, 5, 3], [5, 7, 4, 12, 7]))
