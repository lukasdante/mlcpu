#ifndef MODELS
#define MODELS
#include "Math.hpp"
#include "Loss.hpp"
#include <tuple>
#include <vector>
#include <string>

using namespace std;

template <typename Scalar, typename Param>
class Model {
    protected:
        vector<vector<Scalar>> data;
        vector<Scalar> label;
        int m, n, epochs;
        float alpha;
    public:
        using Vector = vector<Scalar>;
        using Matrix = vector<Vector>;
        Model(Matrix x, Vector y, int epochs, float alpha)
            : data(x), label(y), m(x.size()), n(x[0].size()), epochs(epochs), alpha(alpha) {}
        virtual ~Model() {}
        virtual Param initParams() = 0;
        virtual Vector predict(const Param& params) = 0;
        virtual Scalar cost(const Vector& yp) = 0;
        virtual Param grad(const Vector& yp, Param& params) = 0;
        virtual Param train() {
            cout << "Starting training process..." << endl;
            cout << "Samples: " << m << endl;
            cout << "Labels:  " << n << endl;

            Param params = initParams();

            for (int i = 0; i < epochs; i++) {
                Vector predictions = predict(params);
                
                float error = cost(predictions);
                cout << "Epoch " << (i+1) << " error: " << error << endl;

                params = grad(predictions, params);   
            }

            return params;
        }
};

template <typename Scalar>
class LinearRegression : public Model<Scalar, tuple<vector<Scalar>, Scalar>> {
    using Base = Model<Scalar, tuple<vector<Scalar>, Scalar>>;
    using Base::Base;
    using typename Base::Matrix;
    using typename Base::Vector;
    using Param = tuple<Vector, Scalar>;

    public:
        Param initParams() override {
            Vector w(this->n);
            Scalar b;

            for (int i = 0; i < this->n; i++) {
                w[i] = rng(-1, 1, 5);
            }
            b = rng(-1, 1, 5);

            return make_tuple(w, b);
            
        }

        Vector predict(const Param& wb) override {
            Vector yp(this->m);
            Vector w = get<0>(wb);
            Scalar b = get<1>(wb); 
            
            for (int j = 0; j < this->m; j++) {
                yp[j] = dotProduct(this->data[j], w) + b;
            }

            return yp;
        }

        Scalar cost(const Vector& yp) override {
            Scalar error = loss(yp, this->label, meanSquaredError);
            return error;
        }

        Param grad(const Vector& yp, Param& wb) override {
            Vector grad_w(this->n, 0.0);
            Scalar grad_b = 0.0;

            Vector w = get<0>(wb);
            Scalar b = get<1>(wb); 

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

template <typename Scalar>
class LogisticRegression : public Model<Scalar, tuple<vector<Scalar>, Scalar>> {
    using Base = Model<Scalar, tuple<vector<Scalar>, Scalar>>;
    using Base::Base;
    using typename Base::Matrix;
    using typename Base::Vector;
    using Param = tuple<Vector, Scalar>;

    public:
        Param initParams() override {
            Vector w(this->n);
            Scalar b;

            for (int i = 0; i < this->n; i++) {
                w[i] = rng(-1, 1, 5);
            }
            b = rng(-1, 1, 5);

            return make_tuple(w, b);
            
        }

        Vector predict(const Param& wb) override {
            Vector yp(this->m);
            Vector w = get<0>(wb);
            Scalar b = get<1>(wb); 
            
            for (int j = 0; j < this->m; j++) {
                Scalar z = dotProduct(this->data[j], w) + b;
                yp[j] = sigmoid(z);
            }

            return yp;
        }

        Scalar cost(const Vector& yp) override {
            Scalar error = loss(yp, this->label, binaryCrossEntropy);
            return error;
        }

        Param grad(const Vector& yp, Param& wb) override {
            Vector grad_w(this->n, 0.0);
            Scalar grad_b = 0.0;

            Vector w = get<0>(wb);
            Scalar b = get<1>(wb); 

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