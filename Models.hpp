#ifndef MODELS
#define MODELS
#include "Math.hpp"
#include "Loss.hpp"
#include <tuple>
#include <vector>
#include <string>

using namespace std;

template <typename T, typename Param>
class Model {
    protected:
        vector<vector<T>> data;
        vector<T> label;
        int m, n, epochs;
        float alpha;
    public:
        Model(vector<vector<T>> x, vector<T> y, int epochs, float alpha)
            : data(x), label(y), m(x.size()), n(x[0].size()), epochs(epochs), alpha(alpha) {}
        virtual ~Model() {}
        virtual Param initParams() = 0;
        virtual vector<T> predict(const Param& params) = 0;
        virtual T cost(const vector<T>& yp) = 0;
        virtual Param grad(const vector<T>& yp, Param& params) = 0;
        virtual Param train() {
            cout << "Starting training process..." << endl;
            cout << "Samples: " << m << endl;
            cout << "Labels:  " << n << endl;

            Param params = initParams();

            for (int i = 0; i < epochs; i++) {
                vector<T> predictions = predict(params);
                
                float error = cost(predictions);
                cout << "Epoch " << (i+1) << " error: " << error << endl;

                params = grad(predictions, params);   
            }

            return params;
        }
};

template <typename T>
class LinearRegression : public Model<T, tuple<vector<T>, T>> {
    using Base = Model<T, tuple<vector<T>, T>>;
    using Base::Base;
    public:
        tuple<vector<T>, T> initParams() override {
            vector<T> w(this->n);
            T b;

            for (int i = 0; i < this->n; i++) {
                w[i] = rng(-1, 1, 5);
            }
            b = rng(-1, 1, 5);

            return make_tuple(w, b);
            
        }

        vector<T> predict(const tuple<vector<T>, T>& wb) override {
            vector<T> yp(this->m);
            vector<T> w = get<0>(wb);
            T b = get<1>(wb); 
            
            for (int j = 0; j < this->m; j++) {
                yp[j] = dotProduct(this->data[j], w) + b;
            }

            return yp;
        }

        T cost(const vector<T>& yp) override {
            T error = loss(yp, this->label, mse);
            return error;
        }

        tuple<vector<T>, T> grad(const vector<T>& yp, tuple<vector<T>, T>& wb) override {
            vector<T> grad_w(this->n, 0.0);
            T grad_b = 0.0;

            vector<T> w = get<0>(wb);
            T b = get<1>(wb); 

            // grad_w = 2X'(Xw - y) -> we are dropping 2 as scaling factor
            for (int i = 0; i < this->m; i++) {
                float diff = yp[i] - this->label[i];
                for (int j = 0; j < this->n; j++) {
                    grad_w[j] += diff * this->data[i][j];
                }
                // grad_b = 2*1'(Xw - y)
                grad_b += diff;
            }

            for (int k = 0; k < this->n; k++) {
                grad_w[k] /= this->m;
            }

            grad_b /= this->m;

            // update weights and bias
            for (int j = 0; j < this->n; j++) {
                w[j] -= this->alpha * grad_w[j];
            }
            b -= this->alpha * grad_b;

            return make_tuple(w, b);
        }
};

#endif