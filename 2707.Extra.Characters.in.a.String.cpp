#include "leetcode.h"

#include <unordered_set>

/*
2707. Extra Characters in a String
You are given a 0-indexed string s and a dictionary of words dictionary. You have to break s into one or more non-overlapping substrings such that each substring is present in dictionary. There may be some extra characters in s which are not present in any of the substrings.

Return the minimum number of extra characters left over if you break up s optimally.

 

Example 1:

Input: s = "leetscode", dictionary = ["leet","code","leetcode"]
Output: 1
Explanation: We can break s in two substrings: "leet" from index 0 to 3 and "code" from index 5 to 8. There is only 1 unused character (at index 4), so we return 1.

Example 2:

Input: s = "sayhelloworld", dictionary = ["hello","world"]
Output: 3
Explanation: We can break s in two substrings: "hello" from index 3 to 7 and "world" from index 8 to 12. The characters at indices 0, 1, 2 are not used in any substring and thus are considered as extra characters. Hence, we return 3.
 

Constraints:

1 <= s.length <= 50
1 <= dictionary.length <= 50
1 <= dictionary[i].length <= 50
dictionary[i] and s consists of only lowercase English letters
dictionary contains distinct words
*/

class Solution {
public:
    int minExtraChar(const std::string& s, const std::vector<std::string>& dictionary)
    {
        return minExtraChar2(s, dictionary);

        std::unordered_set<std::string> hashedDict;
        for (auto& word : dictionary)
        {
            hashedDict.insert(word);
        }

        std::vector<int> ans(s.size() + 1, 0);
        for (uint64_t i = 0; i < s.size(); ++i)
        {
            ans[i + 1] = ans[i] + 1;
            for (uint64_t j = 0; j <= i; ++j)
            {
                std::string sub = s.substr(j, i - j + 1);
                auto iter = hashedDict.find(sub);
                if (iter != hashedDict.end())
                {
                    ans[i + 1] = std::min(ans[i + 1], ans[j]);
                }
            }
        }

        return ans[s.size()];
    }

    int minExtraChar2(const std::string& s, const std::vector<std::string>& dictionary)
    {
        int n = s.size();
        std::vector<int> dp(n + 1, 0);

        std::vector<std::vector<int>> possiblePositions(n);
        for (const auto& word : dictionary)
        {
            for (std::size_t i = 0; s[i] != '\0'; ++i)
            {
                i = s.find(word, i);
                if (i == std::string::npos)
                {
                    break;
                }

                possiblePositions[i].push_back(i + word.size());
            }
        }

        dp[n] = 0;
        for (int i = n - 1; i >= 0; --i)
        {
            dp[i] = dp[i + 1] + 1;
            for (auto j : possiblePositions[i])
            {
                dp[i] = std::min(dp[i], dp[j]);
            }
        }

        return dp[0];
    }
};

TEST(ExtraChar, simple)
{
    Solution solution;
    EXPECT_EQ(3, solution.minExtraChar("sayhelloworld", {"hello", "world"}));
    EXPECT_EQ(1, solution.minExtraChar("leetscode", {"leet", "code", "leetcode"}));
    EXPECT_EQ(7, solution.minExtraChar("dwmodizxvvbosxxw", {"ox","lb","diz","gu","v","ksv","o","nuq","r","txhe","e","wmo","cehy","tskz","ds","kzbu"}));
}

DEFINE_MAIN
