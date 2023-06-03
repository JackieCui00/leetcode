// 4、给一个数组a[n]，数组大小不超过1e5，数据范围0~1e8，求其异或值最大连续子区间。
// 输入样例：1 4 5 6
// 输出样例（4^5^6=7）：7

#include <cstddef>
#include <cstdint>
#include <iostream>

#include <gtest/gtest.h>
#include <memory>
#include <sys/types.h>

std::vector<int> FindMaxXorRange(const std::vector<int>& numbers) {
    assert(numbers.size() > 1);

    std::vector<int> xor_values = numbers;
    int max_xor = 0;
    std::pair<std::size_t, std::size_t> range;

    for (std::size_t len = 2; len <= numbers.size(); ++len) {
        for (std::size_t start = 0; (start + len) <= numbers.size(); ++ start) {
            const int end = start + len - 1;
            const int value = xor_values.at(start) ^ numbers.at(end);
            xor_values.at(start) = value;

            if (value > max_xor) {
                max_xor = value;
                range.first = start;
                range.second = end;
            }
        }
    }

    std::vector<int> result;
    for (std::size_t i = range.first; i <= range.second; ++i) {
        result.push_back(numbers.at(i));
    }

    return result;
}

class Trie
{
public:
    Trie() = default;
    ~Trie() = default;

    void Insert(const int32_t value)
    {
        std::vector<Node*> path = this->findPath(value, true /* newNode */);
        assert(path.size() == 32);
        for (auto iter = path.rbegin(); iter != path.rend(); ++iter)
        {
            (*iter)->reference += 1;
        }

        this->verifyNode(&mRoot);
    }

    void Remove(const int32_t value)
    {
        assert(value > 0);
        std::vector<Node*> path = this->findPath(value, false /* newNode */);
        assert(path.size() == 32);

        Node* toDelete = nullptr;
        for (auto iter = path.rbegin(); iter != path.rend(); ++iter)
        {
            if (toDelete != nullptr)
            {
                if (toDelete == (*iter)->children[0].get())
                {
                    (*iter)->children[0].reset();
                }
                else if (toDelete == (*iter)->children[1].get())
                {
                    (*iter)->children[1].reset();
                }
                else
                {
                    assert(false);
                }

                toDelete = nullptr;
            }

            (*iter)->reference -= 1;

            if ((*iter)->reference == 0)
            {
                toDelete = *iter;
            }
        }

        if (toDelete != nullptr)
        {
            if (toDelete == mRoot.children[0].get())
            {
                mRoot.children[0].reset();
            }
            else if (toDelete == mRoot.children[1].get())
            {
                mRoot.children[1].reset();
            }
            else
            {
                assert(false);
            }
        }

        this->verifyNode(&mRoot);
    }

    int32_t MaxXor(const int32_t value)
    {
        const uint64_t unsigned_value = value;
        uint64_t result = 0u;

        Node* node = &mRoot;
        if (node->children[0] == nullptr && node->children[1] == nullptr)
        {
            // this trie is empty
            return 0;
        }

        for (int i = 31; i >= 0; --i)
        {
            const uint64_t bit = ((1ul << i) & unsigned_value) >> i;
            auto& child = node->children[bit];
            if (child != nullptr)
            {
                result |= 1ul << i;
                node = child.get();
            }
            else
            {
                node = node->children[~bit].get();
            }
            assert(node != nullptr);
        }

        assert(result < INT32_MAX);
        return result;
    }

private:
    struct Node
    {
        int value = 0;
        int reference = 0;
        std::unique_ptr<Node> children[2];
    };

    std::vector<Node*> findPath(const int32_t value, const bool newNode)
    {
        assert(value > 0);
        const uint64_t unsigned_value = value;
        Node* node = &mRoot;
        std::vector<Node*> path;
        for (int i = 31; i >= 0; --i)
        {
            const uint64_t bit = ((1ul << i) & unsigned_value) >> i;
            std::unique_ptr<Node>& child = node->children[bit];

            if (child == nullptr)   
            {
                if (newNode)
                {
                    child.reset(new Node());
                    child->value = bit;
                }
                else
                {
                    break;
                }
            }

            path.push_back(child.get());
            node = child.get();
        }

        return path;
    }

    int verifyNode(Node* node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        int reference = 0;
        if (node->children[0] != nullptr)
        {
            assert(node->children[0]->value == 0);
            assert(node->children[0]->reference > 0);
            reference += node->children[0]->reference;
        }

        if (node->children[1] != nullptr)
        {
            assert(node->children[1]->value == 1);
            assert(node->children[1]->reference > 0);
            reference += node->children[1]->reference;
        }

        assert(reference == 0 // leaf nodes
            || reference == node->reference);
        return reference;
    }

private:
    Node mRoot;
};

std::vector<int> FindMaxXorRange2(const std::vector<int>& numbers)
{
    Trie trie;

    std::vector<int> xors;
    {
        int32_t xor_value = 0;
        for (auto i : numbers)
        {
            xor_value ^= i;
            xors.push_back(xor_value);
            trie.Insert(xor_value);
        }
    }

    int32_t max_xor = 0;
    for (auto x : xors)
    {
        int32_t m = trie.MaxXor(x);
        max_xor = std::max(max_xor, m);
    }

    // TODO(cuijiacheng.cjc) Noway to recover the index, unless using an extra map
    return {};
}

inline std::ostream& operator<<(std::ostream& out, const std::vector<int>& elements) {
    out << "vector<";
    std::string seperator = "";
    for (const auto& e : elements) {
        out << seperator << e;
        seperator = ", ";
    }
    out << ">";
    return out;
}

TEST(FindMaxXorRange, simple) {
    {
        const std::vector<int> numbers = {1, 4, 5, 6};
        const auto result = FindMaxXorRange(numbers);
        std::cout << "Result for " << numbers << " is " << result << std::endl;
    }
}

TEST(TestTrie, simple)
{
    {
        Trie trie;
        for (const auto i : {1, 2, 3, 4})
        {
            trie.Insert(i);
        }
        for (const auto i : {4, 3, 2, 1})
        {
            trie.Remove(i);
        }
        assert(trie.MaxXor(234) == 0);

        trie.Insert(1);
        assert(trie.MaxXor(234) == 235);
    }
}


int main(int argc, char* argv[]) {
    ::testing::FLAGS_gtest_color="true";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
