#include "Math.hpp"
#include <vector>
#include <iostream>
#include <cmath>

template <typename Scalar>
float loss(const vector<Scalar>& yp, const vector<Scalar>& yt, float (*op)(const Scalar&, const Scalar&)) {
    if (yp.size() != yt.size()) throw VectorSizeMismatch();

    float sum = 0;
    for (int i = 0; i < yp.size(); i++) {
        sum += op(yp[i], yt[i]);
    }

    return sum / yp.size();
};

template <typename Scalar>
float meanSquaredError(const Scalar& yp_i, const Scalar& yt_i) {
    return pow((yt_i - yp_i), 2);
}

template <typename Scalar>
float binaryCrossEntropy(const Scalar& yp_i, const Scalar& yt_i) {
    return -1 * (yt_i * log(yp_i) + (1 - yt_i) * log(1 - yp_i));
}