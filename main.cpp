#include "Math.hpp"
#include "Error.hpp"
#include "Vector.hpp"
#include "Models.hpp"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    vector<float> va = {3.0f, 4.0f};
    vector<float> vb = {1.0f, 2.0f};

    cout << dotProduct(va, vb) << endl;
    cout << pow(distance(vb), 2)  << endl;
    cout << vectorProjection(va, vb) << endl;
    cout << endl;

    vector<vector<float>> x = {
        {1}, {2}, {3}, {4}
    };

    vector<float> y = {3, 5, 7, 9};

    float alpha = 0.1;
    int epochs = 1000;

    auto [w, b] = linearRegression(x, y, alpha, epochs);

    cout << "\nFinal weight: " << w[0] << endl;
    cout << "Final bias: " << b << endl;

    return 0;
}