//
//  rtweekend.h
//  RayTracing
//
//  Created by 刘清峰 on 2022/6/19.
//

#ifndef rtweekend_h
#define rtweekend_h

#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// 度数转弧度
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // return a random real in [0, 1]
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // return a random real in [min, max]
    return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) {
    if(x < min) return min;
    if(x > max) return max;
    return x;
}

#endif /* rtweekend_h */
