#ifndef MODELS
#define MODELS
#include <tuple>
#include <vector>
#include "Math.hpp"

using namespace std;

auto linearRegression(vector<vector<float>> x, vector<float> y, float alpha, int epochs) {
    int m = x.size(); // number of samples
    int n = x[0].size(); // number of features
    vector<float> w(n);

    // initialize random weights
    for (int i = 0; i < n; i++) {
        w[i] = rng(-1, 1, 5);
    }
    cout << endl;

    float b = rng(-1, 1, 5);

    // start training
    for (int i = 0; i < epochs; i++) {
        vector<float> yp(m);

        // get predictions
        for (int j = 0; j < m; j++) {
            yp[j] = dotProduct(x[j], w) + b;
        }
        
        // compute error
        float error = mse(yp, y);
        cout << yp << endl;
        cout << "Epoch " << (i+1) << " error: " << error << endl; 
        
        // compute gradient
        vector<float> grad_w(n, 0.0);
        float grad_b = 0.0;

        for (int i = 0; i < m; i++) {
            float diff = yp[i] - y[i];
            for (int j = 0; j < n; j++) {
                grad_w[j] += diff * x[i][j];
            }
            grad_b += diff;
        }

        for (int j = 0; j < n; j++) {
            grad_w[j] /= m;
        }
        grad_b /= m;

        // update weights and bias
        for (int j = 0; j < n; j++) {
            w[j] -= alpha * grad_w[j];
        }
        b -= alpha * grad_b;
    }
    return make_tuple(w, b);
}

#endif