#include "Math.hpp"
#include <vector>
#include <iostream>
#include <cmath>

template <typename T>
float loss(const vector<T>& yp, const vector<T>& yt, float (*op)(const T&, const T&)) {
    if (yp.size() != yt.size()) throw VectorSizeMismatch();

    float sum = 0;
    for (int i = 0; i < yp.size(); i++) {
        sum += op(yp[i], yt[i]);
    }

    return sum / yp.size();
};

template <typename T>
float mse(const T& yp_i, const T& yt_i) {
    return pow((yt_i - yp_i), 2);
}

template <typename T>
float binaryCrossEntropy(const T& yp_i, const T& yt_i) {
    return -1 * (yt_i * log(yp_i) + (1 - yt_i) * log(1 - yp_i));
}