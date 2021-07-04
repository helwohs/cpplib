#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Segment Tree Node Base.
 *
 * Helps to hold range data dynamically so
 * that only a small number of nodes are
 * visited per query.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
template<typename T>
struct STNodeB
{
    T value, lazy = 0;

    STNodeB()
    {
        // meant to create a node with default value.
    }

    STNodeB(const T value) :
        value(value)
    {
        // meant to initialize a node with a defined value.
    }

    STNodeB(const STNodeB &lhs, const STNodeB &rhs)
    {
        // meant to create a node by merging lhs and rhs.
    }

    /**
     * Checks if a value matches with
     * this->value according to the
     * node implementation.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    virtual bool match(const T value) const
    {
        return true;
    }

    /**
     * Updates the current node according to
     * the node implementation.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    virtual void update(const size_t range) = 0;

    /**
     * Updates the current node's lazy
     * according to the node
     * implementation.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    virtual void update_lazy(const T delta)
    {
        lazy += delta;
    }

    /**
     * Checks if the current node has some
     * kind of lazy to apply.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    virtual bool has_lazy() const
    {
        return lazy != 0;
    }
};

/**
 * Segment Tree Base.
 *
 * Arranges data in a binary tree so that
 * it is possible to perform range queries
 * and modifications over an array
 * effectively.
 *
 * Note: when the tree is constructed by
 * inserting each value one by one using
 * update the time complexity is actually
 * O(n*log(n)).
 *
 * Time Complexity: O(n).
 * Space Complexity: O(n).
 * Where n is the size of the array.
 */
template<typename Node, typename T>
class SegTreeB
{
public:
    SegTreeB() :
        SegTreeB(1) {}

    SegTreeB(const size_t arr_size) :
        tree(4 * arr_size), arr_size(arr_size) {}

    SegTreeB(const vector<T> &arr) :
        SegTreeB(arr.size(), arr) {}

    SegTreeB(const size_t arr_size, const vector<T> &arr) :
        SegTreeB(arr_size)
    {
        build(0, arr_size - 1, 0, arr);
    }

    SegTreeB(const SegTreeB &lhs, const SegTreeB &rhs) :
        SegTreeB(lhs.arr_size)
    {
        assert(lhs.arr_size == rhs.arr_size);
        for(size_t i = 0; i < 4 * arr_size; ++i)
            tree[i] = Node(lhs.tree[i], rhs.tree[i]);
    }

    /**
     * Finds the index of the first element
     * over the array that matches with value.
     *
     * It returns the size of the array when
     * the value doesn't match with any array
     * value.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    size_t find(const T value)
    {
        return find(0, arr_size - 1, 0, value);
    }

    /**
     * Computes the ith array value.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    T query(const size_t i)
    {
        assert(i < arr_size);
        return query(i, i);
    }

    /**
     * Computes the value corresponding to the
     * range [l, r] of the array.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    T query(const size_t l, const size_t r)
    {
        assert(l <= r and r < arr_size);
        return query(0, arr_size - 1, l, r, 0).value;
    }

    /**
     * Updates the ith array value according to
     * the SegmentTreeKind.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    void update(const size_t i, const T delta)
    {
        assert(i < arr_size);
        update(i, i, delta);
    }

    /**
     * Updates the array values in the range
     * [l, r] according to the SegmentTreeKind.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    void update(const size_t l, const size_t r, const T delta)
    {
        assert(l <= r and r < arr_size);
        update(0, arr_size - 1, l, r, 0, delta);
    }

private:
    Node build(const size_t l, const size_t r, const size_t pos, const vector<T> &arr)
    {
        if(l == r)
            return tree[pos] = Node(arr[l]);

        size_t mid = (l + r) / 2;
        return tree[pos] = Node(build(l, mid, 2 * pos + 1, arr), build(mid + 1, r, 2 * pos + 2, arr));
    }

    size_t find(const size_t l, const size_t r, const size_t pos, const T value)
    {
        propagate(l, r, pos);

        if(!tree[pos].match(value))
            return arr_size;
        else if(l == r)
            return l;

        size_t mid = (l + r) / 2;
        size_t ans = find(l, mid, 2 * pos + 1, value);
        return ans != arr_size ? ans : find(mid + 1, r, 2 * pos + 2, value);
    }

    Node query(const size_t l, const size_t r, const size_t i, const size_t j, const size_t pos)
    {
        propagate(l, r, pos);

        if(l > j or r < i)
            return Node();

        if(l >= i and r <= j)
            return tree[pos];

        size_t mid = (l + r) / 2;
        return Node(query(l, mid, i, j, 2 * pos + 1), query(mid + 1, r, i, j, 2 * pos + 2));
    }

    Node update(const size_t l, const size_t r, const size_t i, const size_t j, const size_t pos, const T delta)
    {
        propagate(l, r, pos);

        if(l > j or r < i)
            return tree[pos];

        if(l >= i and r <= j) {
            tree[pos].lazy = delta;
            // it's important to propagate before returning and merge nodes.
            propagate(l, r, pos);
            return tree[pos];
        }

        size_t mid = (l + r) / 2;
        return tree[pos] = Node(update(l, mid, i, j, 2 * pos + 1, delta), update(mid + 1, r, i, j, 2 * pos + 2, delta));
    }

    virtual void propagate(const size_t l, const size_t r, const size_t pos)
    {
        if(!tree[pos].has_lazy())
            return;

        T lazy = tree[pos].lazy;
        tree[pos].update(r - l + 1);

        if(l != r) {
            tree[2 * pos + 1].update_lazy(lazy);
            tree[2 * pos + 2].update_lazy(lazy);
        }
    }

protected:
    vector<Node> tree;
    size_t arr_size;
};