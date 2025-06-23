#find all possible palindromic partitions of a string[]
class Solution:
    def palinParts(self, s):
        result = []

        # Helper function to check if a substring is a palindrome
        def is_palindrome(start, end):
            while start < end:
                if s[start] != s[end]:
                    return False
                start += 1
                end -= 1
            return True

        # Backtracking function to explore all palindromic partitions
        def backtrack(start, path):
            if start == len(s):
                result.append(path[:])  # Append a copy of the current path
                return
            for end in range(start, len(s)):
                if is_palindrome(start, end):
                    path.append(s[start:end + 1])
                    backtrack(end + 1, path)
                    path.pop()  # Backtrack

        backtrack(0, [])
        return result

# ---------- Testing the Solution ----------

if __name__ == "__main__":
    sol = Solution()
    
    # Test case 1
    s1 = "geeks"
    print("Input:", s1)
    print("Output:", sol.palinParts(s1))
    # Expected: [['g', 'e', 'e', 'k', 's'], ['g', 'ee', 'k', 's']]

    # Test case 2
    s2 = "abcba"
    print("\nInput:", s2)
    print("Output:", sol.palinParts(s2))
    # Expected: [['a', 'b', 'c', 'b', 'a'], ['a', 'bcb', 'a'], ['abcba']]

    # Test case 3
    s3 = "aaa"
    print("\nInput:", s3)
    print("Output:", sol.palinParts(s3))
    # Expected: [['a','a','a'], ['a','aa'], ['aa','a'], ['aaa']]

    # Test case 4
    s4 = ""
    print("\nInput:", s4)
    print("Output:", sol.palinParts(s4))
    # Expected: [[]]

