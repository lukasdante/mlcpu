#ifndef REGULARIZATION
#define REGULARIZATION
#include <vector>

using namespace std;

template <typename Scalar>
vector<Scalar> l1(const vector<Scalar>& w, const Scalar& c) {
    vector<Scalar> l1w(w.size());
    
    for (int i = 0; i < w.size(); i++) {
        if (w[i] > 0) {
            l1w[i] = c;
        }
        else if (w[i] < 0) {
            l1w[i] = -c;
        }
        else {
            l1w[i] = 0;
        }
    }
    
    return l1w;
}

template <typename Scalar>
vector<Scalar> l2(const vector<Scalar>& w, const Scalar& c) {
    vector<Scalar> l2w(w.size());
    
    for (int i = 0; i < w.size(); i++) {
        l2w[i] = 2 * c * w[i];
    }
    
    return l2w;
}

template <typename Scalar>
vector<Scalar> elasticNet(const vector<Scalar>& w, const Scalar& c) {
    vector<Scalar> enw(w.size());
    
    enw = l1(w, c) + l2(w, c);
    
    return enw;
}



#endif