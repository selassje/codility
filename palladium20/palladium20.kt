import kotlin.math.*

fun solution(H: IntArray): Int {
    val N = H.size
    val maxH = H.max()!!
    val lastMaxH = H.lastIndexOf(maxH)
    val firstMaxH = H.indexOf(maxH)
   
    var result = N * maxH
   
    if ( firstMaxH != 0 ) {
        val sliceBeforeFirst = H.slice(IntRange(0,firstMaxH - 1))
        val maxBeforeFirst = sliceBeforeFirst.max()!!
        val countBeforeFirst = sliceBeforeFirst.size
        val possibleMin = countBeforeFirst * maxBeforeFirst + (N - countBeforeFirst) * maxH
        result = min(result,possibleMin)
    }
               
    if ( lastMaxH != N - 1 ) {
        val sliceAfterLast = H.slice(IntRange(lastMaxH + 1 ,N - 1))
        val maxAfterLast = sliceAfterLast.max()!!
        val countAfterLast = sliceAfterLast.size
        val possibleMin = countAfterLast * maxAfterLast + (N - countAfterLast) * maxH
        result = min(result,possibleMin)
    }
   return result
}

fun solution2(H: IntArray): Int {
    val N = H.size
    val maxH = H.max()!!
    var maximumsInPrefixes = IntArray(N)
    var maximumsInPostfixes = IntArray(N)
    
    var max = H.first()
    for ((k, h) in H.withIndex()) {
        max = max(max, h)
        maximumsInPrefixes[k] = max
    }
   
    max = H.last()
    for ((k, h) in H.reversed().withIndex()) {
        max = max(max, h)
        maximumsInPostfixes[k] = max
    }
   
    var min = N * maxH
    for (i in 0 .. N - 2) {
        val possibleMin = (i+1) * maximumsInPrefixes[i] + (N - i - 1) * maximumsInPostfixes[N - 2 - i]
        min = min(min,possibleMin)
    }
   return min
}


fun main() {
    println("Hello World")
}