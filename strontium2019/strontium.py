import sys


class CharStat:
    def __init__(self):
        self.middle = 0
        self.left_different = 0
        self.right_different = 0
        self.left_same = [(0, 0), (0, 0)]
        self.right_same = [(0, 0), (0, 0)]


bestInWords = {}
charStats = {}


def check_word(word, index):
    first_len = 1
    first_c = word[0]
    last_c = word[0]
    i = 1
    last_i = 0
    while i < len(word):
        if last_c != word[i]:
            sub_len = i - last_i
            bestInWords[last_c] = max(bestInWords[last_c], sub_len)
            if last_i == 0:
                first_len = sub_len
            last_c = word[i]
            last_i = i
        i += 1
    last_len = i - last_i
    bestInWords[last_c] = max(bestInWords[last_c], last_len)
    if last_len == len(word):
        charStats[last_c].middle += last_len
    elif first_c != last_c:
        charStats[first_c].left_different = max(charStats[first_c].left_different, first_len)
        charStats[last_c].right_different = max(charStats[last_c].right_different, last_len)
    else:
        charStats[first_c].left_same.append((index, first_len))
        charStats[first_c].left_same.sort(key=lambda x: x[1], reverse=True)
        charStats[first_c].left_same.pop()
        charStats[first_c].right_same.append((index, last_len))
        charStats[first_c].right_same.sort(key=lambda x: x[1], reverse=True)
        charStats[first_c].right_same.pop()


def solution(words):
    for c in range(ord('a'), ord('z') + 1):
        bestInWords[chr(c)] = 0
        charStats[chr(c)] = CharStat()
    result = -sys.maxsize
    for index, w in enumerate(words):
        check_word(w, index)
    for c in range(ord('a'), ord('z') + 1):
        l_max, r_max, middle = charStats[chr(c)].left_different, \
                               charStats[chr(c)].right_different, \
                               charStats[chr(c)].middle

        l_max_i, l_max_v = charStats[chr(c)].left_same[0]
        r_max_i, r_max_v = charStats[chr(c)].right_same[0]
        if l_max_i != r_max_i:
            max_substring = max(l_max_v, l_max) + \
                            max(r_max_v, r_max)
        else:
            l_snd_i, l_snd_v = charStats[chr(c)].left_same[1]
            r_snd_i, r_snd_v = charStats[chr(c)].right_same[1]
            max_comb_1 = max(l_max_v, l_max) + max(r_snd_v, r_max)
            max_comb_2 = max(l_snd_v, l_max) + max(r_max_v, r_max)
            max_substring = max(max_comb_1, max_comb_2)
        max_substring += middle
        result = max(result, max_substring, bestInWords[chr(c)])
    return result


print(solution(["aabb", "aaaa", "bbab"]))
print(solution(["xxbxx", "xbx", "x"]))
print(solution(["dd", "bb", "cc", "dd"]))
print(solution(['bba', 'abb']))
print(solution(['ptzt', 'pztttp', 'pztztpp', 'ppt']))
