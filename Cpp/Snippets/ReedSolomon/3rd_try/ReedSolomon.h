#include <vector>

class ReedSolomon {
public:
    static std::vector<int> encode(const std::vector<int>& data, int nsym);
    static bool decode(std::vector<int>& data, int nsym);

private:
    static constexpr int GF_SIZE = 256;
    static constexpr int GF_POLY = 0x11D;
    static const int GF_EXP[GF_SIZE * 2];
    static const int GF_LOG[GF_SIZE];

    static int gf_multiply(int x, int y);
    static int gf_inverse(int x);
    static std::vector<int> gf_poly_add(const std::vector<int>& p, const std::vector<int>& q);
    static std::vector<int> gf_poly_scale(const std::vector<int>& p, int x);
    static std::vector<int> gf_poly_mul(const std::vector<int>& p, const std::vector<int>& q);
    static std::vector<int> gf_poly_div(const std::vector<int>& dividend, const std::vector<int>& divisor);
    static std::vector<int> gf_poly_mod(const std::vector<int>& dividend, const std::vector<int>& divisor);
    static std::vector<int> gf_poly_sub(const std::vector<int>& p, const std::vector<int>& q);
    static std::vector<int> gf_poly(int n);
    static int gf_poly_eval(const std::vector<int>& p, int x);
};
