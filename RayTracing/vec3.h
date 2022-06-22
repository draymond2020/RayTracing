//
//  vec3.h
//  RayTracing
//
//  Created by 刘清峰 on 2022/6/18.
//

#ifndef vec3_h
#define vec3_h

#include <cmath>
#include <iostream>
#include "rtweekend.h"

using std::sqrt;

class vec3 {
    public:
        double e[3];
    public:
        vec3():e{0, 0, 0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}
        
        double x() const {return e[0];}
        double y() const {return e[1];}
        double z() const {return e[2];}
        
        vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
        double operator[](int i) const {return e[i];}
        double& operator[](int i) {return e[i];}
        
        vec3& operator+=(const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }
        
        vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }
        
        vec3& operator/=(const double t) {
            return *this *= 1 / t;
        }

        double length_squared() const {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }
        
        double length() const {
            return sqrt(length_squared());
        }
    
        inline static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        inline static vec3 random(double min, double max) {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }
};

// 定义vec3的别名
using point3 = vec3;    // 3d point
using color = vec3;     // RGB color

// vec3 Utility Functions

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
}

inline vec3 operator+(const vec3 & u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 & u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 & u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3 &v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 & u, const vec3 &v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 & u, const vec3 &v) {
    // 根据向量叉乘公式
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// 归一化
inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

// 在单位立方体中随机生成一个点，根据球公式 x^2 + y^2 + z^2 = 1，如果 x^2 + y^2 + z^2 >= 1 是球外
inline vec3 random_in_unit_sphere() {
    while(true) {
        auto p = vec3::random(-1, 1);
        if(p.length_squared() >= 1) continue;
        return p;
    }
}

inline vec3 random_unit_vector() {
    // return unit_vector(random_in_unit_sphere());
    auto a = random_double(0, 2*pi);
    auto z = random_double(-1, 1);
    auto r = sqrt(1 - z*z);
    return vec3(r*cos(a), r*sin(a), z);
}

// 获取点的半球表面
inline vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}
#endif /* vec3_h */
