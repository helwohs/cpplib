#include <cpplib/adt/rolling-hash.hpp>
#include <cpplib/stdinc.hpp>
#include <cpplib/utility/random.hpp>

int32_t main()
{
    // https://cses.fi/problemset/task/1732
    desync();
    string s;
    cin >> s;

    RollingHash hash(s, randuint16(53));

    vi ans;
    for(int i = 0; i < (int)s.size() - 1; ++i) {
        auto qp = hash.query(0, i), qs = hash.query(s.size() - 1 - i, s.size() - 1);
        if(qp == qs)
            ans.eb(i + 1);
    }
    for(int i = 0; i < (int)ans.size(); ++i) {
        if(i)
            cout << ' ';
        cout << ans[i];
    }
    cout << endl;
    return 0;
}
