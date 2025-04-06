#ifndef MATH_UTILS
#define MATH_UTILS
#include <vector>
#include <iostream>
#include <cmath>
#include "Error.hpp"

using namespace std;

float rng(float min, float max, int resolution){
    int exp_resolution = static_cast<int>(pow(10, resolution));
    float steps = (max - min) / exp_resolution;
    int rn = rand() % exp_resolution;
    float num = min + steps * rn;
    return num;
}

float dotProduct(vector<float>& va, vector<float>& vb) {
    if (va.size() != vb.size()) throw VectorSizeMismatch();

    float product = 0;
    for (int i = 0; i < va.size(); i++) {
        product += (va[i] * vb[i]);
    }
    return product;
}

float distance(vector<float>& va) {
    float sum = 0;
    for (int i = 0; i < va.size(); i++) {
        sum += pow(va[i], 2);
    }

    return sqrt(sum);
}

float mse(vector<float>& yp, vector<float> yt) {
    if (yp.size() != yt.size()) throw VectorSizeMismatch();

    float sum = 0;
    for (int i = 0; i < yp.size(); i++) {
        sum += pow((yt[i] - yp[i]), 2);
    }

    return sum / yp.size();
}

vector<float> vectorProjection(vector<float>& va, vector<float>& vb) {
    if (va.size() != vb.size()) throw VectorSizeMismatch();

    vector<float> projection;

    float dp = dotProduct(va, vb);
    float di = pow(distance(vb), 2);
    float pj = dp / di;

    for (int i = 0; i < va.size(); i++) {
        projection.push_back(pj * vb[i]);
    }

    return projection;
}

#endif