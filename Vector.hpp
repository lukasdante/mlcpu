#ifndef VECTOR_UTILS
#define VECTOR_UTILS
#include <vector>

using namespace std;

ostream& operator<<(ostream& os, const vector<float>& v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    return os;
}

#endif