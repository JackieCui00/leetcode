#include "leetcode.h"

#include <assert.h>

class CustomStack {
public:
    CustomStack(int maxSize) {
        mData.resize(maxSize);
        mPos = 0;
    }

    void push(int x) {
        if (static_cast<std::size_t>(mPos) >= mData.size())
        {
            return;
        }
        mData[mPos] = x;
        ++mPos;

        assert(static_cast<std::size_t>(mPos) <= mData.size());
    }

    int pop() {
        if (mPos <= 0)
        {
            return -1;
        }
        assert(static_cast<std::size_t>(mPos) <= mData.size());

        int result = mData[mPos - 1];
        --mPos;
        assert(mPos >= 0);

        return result;
    }

    void increment(int k, int val) {
        assert(static_cast<std::size_t>(mPos) <= mData.size());
        for (int i = 0; i < k && i < mPos; ++i)
        {
            mData[i] += val;
        }
    }

private:
    int mPos = 0;
    std::vector<int> mData;
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */

TEST(IncrementStack, simple)
{
    CustomStack stack(3);
    stack.push(1);
    stack.push(2);
    stack.pop();                            // return 2 --> Return top of the stack 2, stack becomes [1]
    stack.push(2);                          // stack becomes [1, 2]
    stack.push(3);                          // stack becomes [1, 2, 3]
    stack.push(4);                          // stack still [1, 2, 3], Do not add another elements as size is 4
    stack.increment(5, 100);                // stack becomes [101, 102, 103]
    stack.increment(2, 100);                // stack becomes [201, 202, 103]
    stack.pop();                            // return 103 --> Return top of the stack 103, stack becomes [201, 202]
    stack.pop();                            // return 202 --> Return top of the stack 202, stack becomes [201]
    stack.pop();                            // return 201 --> Return top of the stack 201, stack becomes []
    stack.pop();                            // return -1 --> Stack is empty return -1.
}

DEFINE_MAIN
