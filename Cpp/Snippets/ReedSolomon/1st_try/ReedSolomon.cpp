#include "ReedSolomon.h"

const int GF_SIZE = 256;
const int GF_POLY = 0x11d;
const int GF_LOG[GF_SIZE] = { 0, 0, 1, 25, 2, 50, 26, 198, 3, 223, 51, 238, 27, 104, 199, 75, 4, 100, 224, 14, 52, 141, 239, 129, 28, 193, 105, 248, 200, 8, 76, 113, 5, 138, 101, 47, 225, 36, 15, 33, 53, 147, 142, 218, 240, 18, 130, 69, 29, 181, 194, 125, 106, 39, 249, 185, 201, 154, 9, 120, 77, 228, 114, 166, 6, 191, 139, 98, 102, 221, 48, 253, 226, 152, 37, 179, 16, 145, 34, 136, 54, 208, 148, 206, 143, 150, 219, 189, 241, 210, 19, 92, 131, 56, 70, 64, 30, 66, 182, 163, 195, 72, 126, 110, 107, 58, 40, 84, 250, 133, 186, 61, 202, 94, 155, 159, 10, 21, 121, 43, 78, 212, 229, 172, 115, 243, 167, 87, 7, 112, 192, 247, 140, 128, 99, 13, 103, 74, 222, 237, 49, 197, 254, 24, 227, 165, 153, 119, 38, 184, 180, 124, 17, 68, 146, 217, 35, 32, 137, 46, 55, 63, 209, 91, 149, 188, 207, 205, 144, 135, 151, 178, 220, 252, 190, 97, 242, 86, 211, 171, 20, 42, 93, 158, 132, 60, 57, 83, 71, 109, 65, 162, 31, 45, 67, 216, 183, 123, 164, 118, 196, 23, 73, 236, 127, 12, 111, 246, 108, 161, 59, 82, 41, 157, 85, 170, 251, 96, 134, 177, 187, 204, 62, 90, 203, 89, 95, 176, 156, 169, 160, 81, 11, 245, 22, 235, 122, 117, 44, 215, 79, 174, 213, 233, 230, 231, 173, 232, 116, 214, 244, 234, 168, 80, 88, 175 };
const int GF_EXP[GF_SIZE * 2] = { 1, 3, 5, 15, 17, 51, 85, 255, 26, 46, 114, 150, 161, 248, 19, 53, 95, 225, 56, 72, 216, 115, 149, 164, 247, 2, 6, 10, 30, 34, 102, 170, 229, 52, 92, 228, 55, 89, 235, 38, 106, 190, 217, 112, 144, 171, 230, 49, 83, 245, 4, 12, 20, 60, 68, 204, 79, 209, 104, 184, 211, 110, 178, 205, 76, 212, 103, 169, 224, 59, 77, 215, 98, 166, 241, 8, 24, 40, 120, 136, 131, 158, 185, 208, 107, 189, 220, 127, 129, 152, 179, 206, 73, 219, 118, 154, 181, 196, 87, 249, 16, 48, 80, 240, 11, 29, 39, 105, 187, 214, 97, 163, 254, 25, 43, 125, 135, 146, 173, 236, 47, 113, 147, 174, 233, 32, 96, 160, 251, 22, 58, 78, 210, 109, 183, 194, 93, 231, 50, 86, 250, 21, 63, 65, 195, 94, 226, 61, 71, 201, 64, 192, 91, 237, 44, 116, 156, 191, 218, 117, 159, 186, 213, 100, 172, 239, 42, 126, 130, 157, 188, 223, 122, 142, 137, 128, 155, 182, 193, 88, 232, 35, 101, 175, 234, 37, 111, 177, 200, 67, 197, 84, 252, 31, 33, 99, 165, 244, 7, 9, 27, 45, 119, 153, 176, 203, 70, 202, 69, 207, 74, 222, 121, 139, 134, 145, 168, 227, 62, 66, 198, 81, 243, 14, 18, 54, 90, 238, 41, 123, 141, 140, 143, 138, 133, 148, 167, 242, 13, 23, 57, 75, 221, 124, 132, 151, 162, 253, 28, 36, 108, 180, 199, 82, 246, 1, 3, 5, 15, 17, 51, 85, 255, 26, 46, 114, 150, 161, 248, 19, 53, 95, 225, 56, 72, 216, 115, 149, 164, 247, 2, 6, 10, 30, 34, 102, 170, 229, 52, 92, 228, 55, 89, 235, 38, 106, 190, 217, 112, 144, 171, 230, 49, 83, 245, 4, 12, 20, 60, 68, 204, 79, 209, 104, 184, 211, 110, 178, 205, 76, 212, 103, 169, 224, 59, 77, 215, 98, 166, 241, 8, 24, 40, 120, 136, 131, 158, 185, 208, 107, 189, 220, 127, 129, 152, 179, 206, 73, 219, 118, 154, 181, 196, 87, 249, 16, 48, 80, 240, 11, 29, 39, 105, 187, 214, 97, 163, 254, 25, 43, 125, 135, 146, 173, 236, 47, 113, 147, 174, 233, 32, 96, 160, 251, 22, 58, 78, 210, 109, 183, 194, 93, 231, 50, 86, 250, 21, 63, 65, 195, 94, 226, 61, 71, 201, 64, 192, 91, 237, 44, 116, 156, 191, 218, 117, 159, 186, 213, 100, 172, 239, 42, 126, 130, 157, 188, 223, 122, 142, 137, 128, 155, 182, 193, 88, 232, 35, 101, 175, 234, 37, 111, 177, 200, 67, 197, 84, 252, 31, 33, 99, 165, 244, 7, 9, 27, 45, 119, 153, 176, 203, 70, 202, 69, 207, 74, 222, 121, 139, 134, 145, 168, 227, 62, 66, 198, 81, 243, 14, 18, 54, 90, 238, 41, 123, 141, 140, 143, 138, 133, 148, 167, 242, 13, 23, 57, 75, 221, 124, 132, 151, 162, 253, 28, 36, 108, 180, 199, 82, 246 };

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

std::vector<int> ReedSolomon::gf_poly_eval(const std::vector<int>& p, int x) {
    int y = p[0];
    for (size_t i = 1; i < p.size(); ++i) {
        y = gf_multiply(y, x) ^ p[i];
    }
    return { y };
}
