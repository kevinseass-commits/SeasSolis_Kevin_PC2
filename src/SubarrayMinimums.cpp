#include "SubarrayMinimums.h"
#include <stack>
#include <vector>

const int MOD = 1e9 + 7;

int SubarrayMinimums::sumSubarrayMins(const std::vector<int>& arr) {
    int n = arr.size();
    std::vector<int> left(n), right(n);
    std::stack<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && arr[st.top()] > arr[i]) {
            st.pop();
        }
        left[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && arr[st.top()] >= arr[i]) {
            st.pop();
        }
        right[i] = st.empty() ? n : st.top();
        st.push(i);
    }

    long long res = 0;
    for (int i = 0; i < n; ++i) {
        long long count_left = i - left[i];
        long long count_right = right[i] - i;
        long long contrib = (count_left * count_right) % MOD;
        contrib = (contrib * arr[i]) % MOD;
        res = (res + contrib) % MOD;
    }
    return res;
}
