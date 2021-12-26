#pragma once

#include <vector>

template<typename T>
class SegmentTree {
public:
    explicit SegmentTree(const std::vector<T> &data) :
            data_(data),
            tree_(std::vector<T>(4 * data_.size())) {
        Build(0, 0, data_.size());
    }

    T Update(int position, int new_value) {
        return Update(0, 0, static_cast<int>(data_.size()) - 1, position, new_value);
    }

    T Sum(int left, int right) {
        return Sum(0, 0, static_cast<int>(data_.size()) - 1, left, right);
    }

private:
    void Build(int vertex, int left, int right) {
        if (left == right) {
            tree_[vertex] = data_[left];
        } else {
            T tree_mid = (left + right) / 2;
            Build(vertex * 2 + 1, left, tree_mid);
            Build(vertex * 2 + 2, tree_mid + 1, right);
            tree_[vertex] = tree_[vertex * 2 + 1] + tree_[vertex * 2 + 2];
        }
    }


    T Update(int vertex, int tree_left, int tree_right, int position, int new_value) {
        if (tree_left == tree_right) {
            tree_[vertex] = new_value;
        } else {
            int tree_mid = (tree_left + tree_right) / 2;
            if (position <= tree_mid) {
                Update(vertex * 2 + 1, tree_left, tree_mid, position, new_value);
            } else {
                Update(vertex * 2 + 2, tree_mid + 1, tree_right, position, new_value);
            }

            tree_[vertex] = tree_[vertex * 2 + 1] + tree_[vertex * 2 + 2];
        }

        return tree_[vertex];
    }

    T Sum(int vertex, int tree_left, int tree_right, int left, int right) {
        if (left > right) {
            return 0;
        }

        if (left == tree_left and right == tree_right) {
            return tree_[vertex];
        }

        int tree_mid = (tree_left + tree_right) / 2;
        return Sum(vertex * 2 + 1, tree_left, tree_mid, left, std::min(right, tree_mid))
               + Sum(vertex * 2 + 2, tree_mid + 1, tree_right, std::max(left, tree_mid + 1), right);
    }


    std::vector<T> data_;
    std::vector<T> tree_;
};