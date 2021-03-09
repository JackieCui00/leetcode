#include "leetcode.h"
#include <bits/c++config.h>
#include <ostream>

/*
 * 139. Word Break
 *
 * https://leetcode-cn.com/problems/word-break/
 *
 * Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.
 *
 * Note that the same word in the dictionary may be reused multiple times in the segmentation.
 *
 *
 * Example 1:
 *
 * Input: s = "leetcode", wordDict = ["leet","code"]
 * Output: true
 * Explanation: Return true because "leetcode" can be segmented as "leet code".
 *
 *
 * Example 2:
 *
 * Input: s = "applepenapple", wordDict = ["apple","pen"]
 * Output: true
 * Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
 * Note that you are allowed to reuse a dictionary word.
 *
 *
 * Example 3:
 *
 * Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
 * Output: false
 *
 *
 * Constraints:
 *
 *     1 <= s.length <= 300
 *     1 <= wordDict.length <= 1000
 *     1 <= wordDict[i].length <= 20
 *     s and wordDict[i] consist of only lowercase English letters.
 *     All the strings of wordDict are unique.
 *
 **/

class TrieNode final {
public:
    void insert(const std::string& s) {
        this->insert_inner(s.c_str(), s.size(), s.size() - 1);
    }

    bool find(const char* const s, const std::size_t s_len) {
        if (s_len >= _max_depth) {
            return false;
        }
        return this->find_inner(s, s_len, s_len - 1);
    }

    friend std::ostream& operator<<(std::ostream& os, const TrieNode& node) {
        os << "{is_end:" << node._is_end;
        std::string sep = ", children:";
        char c = 'a';
        for (const auto& child : node._children) {
            if (nullptr == child) {
                ++c;
                continue;
            }

            os << sep << c << ":" << *child;

            sep = ", ";
            ++c;
        }
        os << "}";
        return os;
    }

private:
    bool find_inner(const char* const s, const std::size_t s_len, const std::size_t idx) {
        assert(idx < s_len);

        const std::size_t child_idx = s[idx] - 'a';
        const auto& child = _children.at(child_idx);

        if (child == nullptr) {
            return false;
        }

        if (idx == 0) {
            return child->_is_end;
        }

        return child->find_inner(s, s_len, idx - 1);
    }

    void insert_inner(const char* const s, const std::size_t s_len, const std::size_t idx) {
        assert(idx < s_len);

        const std::size_t child_idx = s[idx] - 'a';
        auto& child = _children.at(child_idx);
        if (nullptr == child) {
            child = std::make_unique<TrieNode>();
        }

        if (idx == 0) {
            child->_is_end = true;
            child->_max_depth = std::max(child->_max_depth, 1ul);
        } else {
            child->insert_inner(s, s_len, idx - 1);
        }

        this->_max_depth = std::max(this->_max_depth, child->_max_depth + 1);
    }

private:
    std::array<std::unique_ptr<TrieNode>, 26> _children{};
    bool _is_end = false;
    std::size_t _max_depth = 0;
};

class Solution {
public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
        TrieNode root;
        { // construct a Trie-tree
            for (const auto& word : wordDict) {
                root.insert(word);
            }
        }

        std::vector<bool> results(s.size(), false);
        for (std::size_t i = 0; i < s.size(); ++i) {
            bool result = root.find(s.c_str(), i + 1);

            for (std::size_t j = 0; !result && j < i; ++j) {
                result = results.at(j) && root.find(s.c_str() + j + 1, i - j);
            }

            results.at(i) = result;
        }

        return results.at(s.size() - 1);
    }
};

TEST(WordBreak, simple) {
    Solution solution;

    std::cout << std::boolalpha;
    {
        const std::string s = "leetcode";
        std::vector<std::string> dict = {"leet", "code"};
        const bool output = solution.wordBreak(s, dict);
        const bool expect_output = true;

        print(std::make_tuple(s, dict), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        const std::string s = "applepenapple";
        std::vector<std::string> dict = {"apple", "pen"};
        const bool output = solution.wordBreak(s, dict);
        const bool expect_output = true;

        print(std::make_tuple(s, dict), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        const std::string s = "catsandog";
        std::vector<std::string> dict = {"cats", "dog", "sand", "and", "cat"};
        const bool output = solution.wordBreak(s, dict);
        const bool expect_output = false;

        print(std::make_tuple(s, dict), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        const std::string s = "ab";
        std::vector<std::string> dict = {"a", "b"};
        const bool output = solution.wordBreak(s, dict);
        const bool expect_output = true;

        print(std::make_tuple(s, dict), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN

