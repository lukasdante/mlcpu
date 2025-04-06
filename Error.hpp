#ifndef ERROR_UTILS
#define ERROR_UTILS

#include <iostream>
#include <vector>
#include <exception>

using namespace std;

class VectorSizeMismatch : public exception {
    public:
        virtual const char* what() const noexcept override {
            return "Vector sizes do not match!";
        }
};

#endif