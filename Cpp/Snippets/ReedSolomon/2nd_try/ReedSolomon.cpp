#include "ReedSolomon.h"
#include <algorithm>
#include <iostream>

constexpr int ReedSolomon::GF_EXP[GF_SIZE * 2] = { /* Precomputed GF_EXP table */ };
constexpr int ReedSolomon::GF_LOG[GF_SIZE] = { /* Precomputed GF_LOG table */ };

int ReedSolomon::gf_multiply(int x, int y) {
    return (x && y) ? GF_EXP[GF_LOG[x] + GF_LOG[y]] : 0;
}

int ReedSolomon::gf_inverse(int x) {
    return GF_EXP[GF_SIZE - 1 - GF_LOG[x]];
}

std::vector<int> ReedSolomon::gf_poly_add(const std::vector<int>& p, const std::vector<int>& q) {
    std::vector<int> r(std::max(p.size(), q.size()), 0);
    for (size_t i = 0; i < p.size(); ++i) {
        r[i + r.size() - p.size()] = p[i];
    }
    for (size_t i = 0; i < q.size(); ++i) {
        r[i + r.size() - q.size()] ^= q[i];
    }
    return r;
}

std::vector<int> ReedSolomon::gf_poly_scale(const std::vector<int>& p, int x) {
    std::vector<int> r(p.size(), 0);
    for (size_t i = 0; i < p.size(); ++i) {
        r[i] = gf_multiply(p[i], x);
    }
    return r;
}

std::vector<int> ReedSolomon::gf_poly_mul(const std::vector<int>& p, const std::vector<int>& q) {
    std::vector<int> r(p.size() + q.size() - 1, 0);
    for (size_t j = 0; j < q.size(); ++j) {
        for (size_t i = 0; i < p.size(); ++i) {
            r[i + j] ^= gf_multiply(p[i], q[j]);
        }
    }
    return r;
}

std::vector<int> ReedSolomon::gf_poly_div(const std::vector<int>& dividend, const std::vector<int>& divisor) {
    std::vector<int> result(dividend);
    for (size_t i = 0; i < dividend.size() - divisor.size() + 1; ++i) {
        int coef = result[i];
        if (coef != 0) {
            for (size_t j = 1; j < divisor.size(); ++j) {
                if (divisor[j] != 0) {
                    result[i + j] ^= gf_multiply(divisor[j], coef);
                }
            }
        }
    }
    return std::vector<int>(result.end() - divisor.size() + 1, result.end());
}

std::vector<int> ReedSolomon::gf_poly_mod(const std::vector<int>& dividend, const std::vector<int>& divisor) {
    std::vector<int> result = gf_poly_div(dividend, divisor);
    result.resize(dividend.size() - divisor.size() + 1);
    return result;
}

std::vector<int> ReedSolomon::gf_poly_sub(const std::vector<int>& p, const std::vector<int>& q) {
    std::vector<int> r(std::max(p.size(), q.size()), 0);
    for (size_t i = 0; i < p.size(); ++i) {
        r[i + r.size() - p.size()] = p[i];
    }
    for (size_t i = 0; i < q.size(); ++i) {
        r[i + r.size() - q.size()] ^= q[i];
    }
    return r;
}

std::vector<int> ReedSolomon::encode(const std::vector<int>& data, int nsym) {
    std::vector<int> gen = gf_poly(nsym);
    std::vector<int> message(data.begin(), data.end());
    message.resize(data.size() + nsym, 0);
    std::vector<int> remainder = gf_poly_mod(message, gen);
    std::vector<int> encoded_data = data;
    encoded_data.insert(encoded_data.end(), remainder.begin(), remainder.end());
    return encoded_data;
}

bool ReedSolomon::decode(std::vector<int>& data, int nsym) {
    std::vector<int> gen = gf_poly(nsym);
    std::vector<int> remainder = gf_poly_mod(data, gen);

    bool error = false;
    for (size_t i = 0; i < remainder.size(); ++i) {
        if (remainder[i] != 0) {
            error = true;
            break;
        }
    }
    if (!error) {
        data.resize(data.size() - nsym);
        return true;
    }

    std::vector<int> syndrome(nsym, 0);
    for (size_t i = 0; i < nsym; ++i) {
        syndrome[i] = gf_poly_eval(remainder, GF_EXP[i]);
    }

    std::vector<int> corrected_data = data;
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < syndrome.size(); ++j) {
            corrected_data[i] ^= gf_multiply(syndrome[j], GF_EXP[(i * j) % (GF_SIZE - 1)]);
        }
    }
    data = corrected_data;
    data.resize(data.size() - nsym);
    return true;
}

std::vector<int> ReedSolomon::gf_poly(int n) {
    std::vector<int> p = { 1 };
    for (int i = 0; i < n; ++i) {
        p = gf_poly_mul(p, { 1, GF_EXP[i] });
    }
    return p;
}

int ReedSolomon::gf_poly_eval(const std::vector<int>& p, int x) {
    int y = p[0];
    for (size_t i = 1; i < p.size(); ++i) {
        y = gf_multiply(y, x) ^ p[i];
    }
    return y;
}
