#ifndef MAScalarH_UScalarILS
#define MAScalarH_UScalarILS
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

float sigmoid(float z) {
    return 1 / (1 + exp(-z));
}

#endif