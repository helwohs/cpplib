#pragma once
#include <cpplib/adt/modular.hpp>
#include <cpplib/stdinc.hpp>

/**
 * Modular Combinatorics.
 *
 * Provides modular combinatorial algorithms
 * such as C, P, factorials and fibonacci
 * computation.
 *
 * Note: M must be prime.
 *
 * Note: if __uint128_t is not present, *
 * may cause overflow in modular operations.
 *
 * Time Complexity: O(n).
 * Space Complexity: O(n).
 * Where n is the greatest precomputed value.
 */
template<uint M = MOD>
class ModC
{
public:
    static_assert(M > 0, "M must be prime, thus greater than 0.");

    using mint = modular<M>;

    ModC(const uint max_value = MAXN) :
        max_value(max_value)
    {
        assert(0 < max_value and max_value < M);
        _fact = range_factorial(max_value);
        _inv = range_inverse(max_value);
    }

    /**
     * Modular Combination.
     *
     * Returns C(n, k)%M.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    mint C(const uint n, const uint k) const
    {
        assert(k <= n and n <= max_value);
        return fact(n) * inv(fact(k) * fact(n - k));
    }

    /**
     * Modular Permutation.
     *
     * Returns P(n, k)%M.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    mint P(const uint n, const uint k) const
    {
        assert(k <= n and n <= max_value);
        return fact(n) * inv(fact(n - k));
    }

    /**
     * Modular Factorial.
     *
     * Returns n!%M.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    mint fact(const uint n) const
    {
        assert(n <= max_value);
        return _fact[n];
    }

    /**
     * Modular Fibonacci Number.
     *
     * Computes the n-th fibonacci number mod M.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(log(n)).
     */
    mint fib(const uint n) const
    {
        return _fib(n).first;
    }

    /**
     * Modular Catalan Number.
     *
     * Computes the n-th catalan number mod M.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    mint catalan(const uint n) const
    {
        assert(2 * n <= max_value);
        return C(2 * n, n) * inv(n + 1);
    }

    /**
     * Modular Multiplicative Inverse.
     *
     * Returns the modular multiplicative inverse
     * of a with mod M.
     *
     * Note: this specific algorithm requires a
     * prime M value.
     *
     * Time Complexity: O((a <= max_value? 1 : log(a))).
     * Space Complexity: O(1).
     */
    mint inv(const mint &a) const
    {
        assert(a.value > 0);
        return a.value <= max_value ? _inv[a.value] : inverse(a);
    }

private:
    /**
     * Range Modular Factorial.
     *
     * Computes the factorial for each natural <=
     * n, mod M.
     *
     * Time Complexity: O(n).
     * Space Complexity: O(n).
     */
    vector<mint> range_factorial(const uint n) const
    {
        vector<mint> fact(n + 1);
        fact[0] = 1;
        for(uint i = 1; i <= n; ++i)
            fact[i] = fact[i - 1] * i;
        return fact;
    }

    /**
     * Modular Fibonacci Number.
     *
     * Computes the n-th and n+1-th
     * fibonacci numbers mod M.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(log(n)).
     */
    pair<mint, mint> _fib(const uint n) const
    {
        if(n == 0)
            return {0, 1};
        pair<mint, mint> p = _fib(n >> 1);
        mint c = p.first * (2 * p.second - p.first), d = p.first * p.first + p.second * p.second;
        if(n & 1)
            return {d, c + d};
        return {c, d};
    }

    /**
     * Range Modular Multiplicative Inverse.
     *
     * Computes the modular multiplicative
     * inverse for each positive integer <= n
     * with mod M.
     *
     * Note: this specific algorithm requires a
     * prime M value.
     *
     * Time Complexity: O(n).
     * Space Complexity: O(n).
     */
    vector<mint> range_inverse(const mint &n) const
    {
        assert(n.value > 0);
        vector<mint> inv(n.value + 1);
        inv[1] = 1;
        for(uint i = 2; i <= n.value; ++i)
            inv[i] = -inv[M % i] * (M / i);
        return inv;
    }

    uint max_value;
    vector<mint> _inv, _fact;
};
