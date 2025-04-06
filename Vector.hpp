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

template <typename T>
vector<T> operator<<(ostream& os, const vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    return os;
}

template <typename T>
vector<T> operator+(const vector<T> a, const vector<T>& b) {
    if (a.size() != b.size()) throw VectorSizeMismatch();

    vector<T> result(a.size());
    for (int i = 0; i < a.size(); i++) {
        result.push_back(a[i] + b[i]);
    }

    return result;
}

template <typename T>
vector<T> operator-(const vector<T> a, const vector<T>& b) {
    if (a.size() != b.size()) throw VectorSizeMismatch();

    vector<T> result(a.size());
    for (int i = 0; i < a.size(); i++) {
        result.push_back(a[i] - b[i]);
    }

    return result;
}

template <typename T>
vector<T> operator*(const vector<T> a, const vector<T>& b) {
    if (a.size() != b.size()) throw VectorSizeMismatch();

    vector<T> result(a.size());
    for (int i = 0; i < a.size(); i++) {
        result.push_back(a[i] * b[i]);
    }

    return result;
}

template <typename T>
vector<T> operator/(const vector<T> a, const vector<T>& b) {
    if (a.size() != b.size()) throw VectorSizeMismatch();

    vector<T> result(a.size());
    for (int i = 0; i < a.size(); i++) {
        if (b[i] == 0) throw runtime_error("Divide by zero error.");
        result.push_back(a[i] / b[i]);
    }

    return result;
}

template <typename T>
float dotProduct(vector<T>& va, vector<T>& vb) {
    if (va.size() != vb.size()) throw VectorSizeMismatch();

    float product = 0;
    for (int i = 0; i < va.size(); i++) {
        product += (va[i] * vb[i]);
    }
    return static_cast<float>(product);
}

float distance(vector<float>& va) {
    float sum = 0;
    for (int i = 0; i < va.size(); i++) {
        sum += pow(va[i], 2);
    }

    return sqrt(sum);
}

template <typename T>
vector<T> vectorProjection(vector<T>& va, vector<T>& vb) {
    if (va.size() != vb.size()) throw VectorSizeMismatch();

    vector<T> projection;

    float dp = dotProduct(va, vb);
    float di = pow(distance(vb), 2);
    float pj = dp / di;

    for (int i = 0; i < va.size(); i++) {
        projection.push_back(pj * vb[i]);
    }

    return projection;
}


#endif