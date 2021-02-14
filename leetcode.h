#pragma once

#include <compare>
#pragma GCC system_header

#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <queue>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#define SELF_TEST

template<typename T>
struct TreeNodeBase {
    T val;
    TreeNodeBase<T> *left;
    TreeNodeBase<T> *right;

    template<typename ...Args>
    TreeNodeBase(Args&& ...args) : val(std::forward<Args>(args)...), left(nullptr), right(nullptr) {}
};

template<typename T>
struct print_tree {
    const TreeNodeBase<T>* data;

    explicit print_tree(const TreeNodeBase<T>* const data_) : data(data_) {}
};

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const print_tree<T> root) {
    if (nullptr == root.data) {
        return out;
    }
    out << "Tree{Node:" << root.data->val << ", Left:" << print_tree<T>(root.data->left) << ", Right:" << print_tree(root.data->right) << "}";
    return out;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const TreeNodeBase<T>* root) {
    if (nullptr == root) {
        return out;
    }
    out << "<TreeNode:" << root->val << ">";
    return out;
}

template<typename T>
struct ListNodeBase {
    T val;
    ListNodeBase<T> *next;

    template<typename ...Args>
    ListNodeBase(Args&& ...args) : val(std::forward<Args>(args)...), next(nullptr) {}

    bool operator==(const ListNodeBase<T>& other) const {
        const ListNodeBase<T>* node1 = this;
        const ListNodeBase<T>* node2 = &other;

        while (node1 != nullptr && node2 != nullptr) {
            if (node1->val != node2->val) {
                return false;
            }
            node1 = node1->next;
            node2 = node2->next;
        }
        if (node1 != nullptr || node2 != nullptr) {
            return false;
        }

        return true;
    }
};

template<typename T>
struct print_list {
    const ListNodeBase<T>* data;

    explicit print_list(const ListNodeBase<T>* const data_) : data(data_) {}
};

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const print_list<T> head) {
    if (nullptr == head.data) {
        return out;
    }
    out << "List{Node:" << head.data->val;
    for (auto node = head.data->next; nullptr != node; node = node->next) {
        out << ", Node:" << node->val;
    }
    out << "}";
    return out;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const ListNodeBase<T>* node) {
    if (nullptr == node) {
        return out;
    }
    out << "<LinkNode:" << node->val << ">";
    return out;
}

template<typename T>
struct is_container : std::false_type {};

template<typename T>
struct is_container<std::vector<T>> : std::true_type {};

template<typename T>
struct is_container<std::queue<T>> : std::true_type {};

template<typename T>
struct is_container<std::deque<T>> : std::true_type {};

template<typename Key, typename Value>
struct is_container<std::map<Key, Value>> : std::true_type {};

template<typename Key, typename Value>
struct is_container<std::unordered_map<Key, Value>> : std::true_type {};

template<typename T, std::enable_if_t<is_container<T>::value>* = nullptr>
inline std::ostream& operator<<(std::ostream& out, const T& elements) {
    out << "<";
    std::string seperator = "";
    for (const auto& e : elements) {
        out << seperator << e;
        seperator = ", ";
    }
    out << ">";
    return out;
}

template<typename ...Args, std::size_t ...Is>
constexpr void print_tuple(std::ostream& out, const std::tuple<Args...>& t, std::index_sequence<Is...>) {
    ((void)(out << (Is == 0 ? "" : ", ") << std::get<Is>(t)), ...);
}

template<typename ...Args>
inline constexpr std::ostream& operator<<(std::ostream& out, const std::tuple<Args...>& t) {
    print_tuple(out, t, std::make_index_sequence<sizeof...(Args)>());
    return out;
}

template<typename T1, typename T2>
inline std::ostream& operator<<(std::ostream& out, const std::pair<T1, T2>& pair) {
    out << "(" << pair.first << ", " << pair.second << ")";
    return out;
}

template<typename ...Args, typename T>
inline void print(const std::tuple<Args...>& input, const T& output, const T& expect_output) {
    std::cout << "Input:{" << input << "}, Output:" << output
        << ", Expect:" << expect_output << std::endl;
}

#define DEFINE_MAIN \
int main(int argc, char* argv[]) { \
    ::testing::FLAGS_gtest_color="true"; \
    ::testing::InitGoogleTest(&argc, argv); \
    return RUN_ALL_TESTS(); \
}
