#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

template<class const_node_iterator, class node_iterator, class cmp, class allocator> struct sum_node_update {
    public:
        typedef typename node_iterator::value_type iterator;
        struct metadata_type {
            int size, mx;
            metadata_type() : size(0), mx(0) {}
        };
        template<class T> int order_of_key(T key) {
            node_iterator it = node_begin();
            const_node_iterator end = node_end();
            int res = 0;
            while (it != end) {
                if (cmp()(**it, key)) {
                    res++;
                    if (it.get_l_child() != end) {
                        res += it.get_l_child().get_metadata().size;
                    }
                    it = it.get_r_child();
                }
                else {
                    it = it.get_l_child();
                }
            }
            return res;
        }
        iterator find_by_order(int pos) {
            pos++;
            node_iterator it = node_begin();
            const_node_iterator end = node_end();
            while (it != end) {
                int sz = 1;
                if (it.get_l_child() != end) {
                    sz += it.get_l_child().get_metadata().size;
                }
                if (sz == pos) {
                    return *it;
                }
                else if (sz > pos) {
                    it = it.get_l_child();
                }
                else {
                    pos -= sz;
                    it = it.get_r_child();
                }
            }
            return *it;
        }
    protected:
        inline void operator() (node_iterator it, const_node_iterator end) {
            metadata_type val;
            val.size = 1;
            if (it.get_l_child() != end) {
                val.size += it.get_l_child().get_metadata().size;
                val.mx = it.get_l_child().get_metadata().mx;
            }
            val.mx = max(val.mx, **it + val.size);
            if (it.get_r_child() != end) {
                val.mx = max(val.mx, it.get_r_child().get_metadata().mx + val.size);
                val.size += it.get_r_child().get_metadata().size;
            }
            (metadata_type&) it.get_metadata() = val;
        }
        virtual const_node_iterator node_begin() const = 0;
        virtual const_node_iterator node_end() const = 0;
};

typedef tree<int, null_type, less<int>, rb_tree_tag, sum_node_update> sum_set;

int main() {
    sum_set st;
    st.insert(6);
    st.insert(3);
    st.insert(4);
    st.insert(5);
    cout << st.node_begin().get_metadata().mx << "\n";
    cout << st.order_of_key(4) << "\n";
    sum_set::iterator it = st.find_by_order(2);
    cout << *it << "\n";
    st.erase(4);
    cout << st.node_begin().get_metadata().mx << "\n";
    it = st.find_by_order(2);
    cout << *it << "\n";
    return 0;
}
