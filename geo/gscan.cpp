#include <iostream>
#include <vector>
#include <cmath>

template<typename T>
struct pt {
    T x;
    T y;
    pt(): x(T(0)), y(T(0)) {}
    pt(T _x, T _y): x(_x), y(_y) {}
    pt<T> operator+(const pt<T>& other) {
        return pt{x + other.x, y + other.y};
    }
    pt<T> operator-(const pt<T>& other) {
        return pt{x - other.x, y - other.y};
    }  
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const pt<T>& p) {
    os << "(" << p.x << "," << p.y << ")" << "\n";
    return os;
} 

template <typename T>
T cross(pt<T> p1, pt<T> p2) {
    return T(p1.x*p2.y - p1.y*p2.x);
}

template <typename T>
T dot(pt<T> p1, pt<T> p2) {
    return T(p1.x*p2.x + p1.y*p2.y);
}


//returns 1 if (p1, p2, p3) is positively oriented
//        0 if                  collinear
//        -1 if                 negatively oriented
template <typename T>
int orient(pt<T> p1, pt<T> p2, pt<T> p3) {
    T c = cross(p2 - p1, p3 - p1);
    if(c > T(0)) {return 1;}
    if(c < T(0)) {return -1;}
    return 0;
}

namespace gscan {

}




int main() {
    pt<double> p1{0,0};
    pt<double> p2{1,0};
    pt<double> p3{1,1};
    std::cout << orient(p2, p3, p3) << "\n";
    std::cout << cross(p1, p1 + p1) << "\n";
}
