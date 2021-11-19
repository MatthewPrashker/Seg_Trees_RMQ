#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>

template<typename T>
struct pt {
    T x;
    T y;
    pt(): x(T(0)), y(T(0)) {}
    pt(T _x, T _y): x(_x), y(_y) {}
    pt<T> operator=(const pt<T>& other) {
        x = other.x;
        y = other.y;
        return *this;
    }
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

    //Return the point with lowest y-coordinate
    //Break ties with lowest x-coordinate
    //Point to be used as pivot in Graham Scan
    template<typename T>
    pt<T> find_lowest(std::vector<pt<T> >& points) {
        assert(points.size() > 0);
        pt<T> lowest = points[0];
        for(auto it = next(points.begin()); it != points.end(); it++) {
            if((*it).y < lowest.y) {
                lowest = *it;
                continue;
            }
            if((*it).x < lowest.x) {
                lowest = *it;
            }
        }
        return lowest;
    }

}




int main() {
    pt<double> p1{0,0};
    pt<double> p2{1,-1};
    pt<double> p3{1,1};

    //create a vector of points to sort
    std::vector<pt<double> >points {p1, p2, p3};
    




    std::cout << gscan::find_lowest(points);
    
}
