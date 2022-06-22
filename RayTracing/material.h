//
//  material.h
//  RayTracing
//
//  Created by 刘清峰 on 2022/6/22.
//

#ifndef material_h
#define material_h

#include "rtweekend.h"

struct hit_record;

// 材质类主要用来决定材质和光线是如何作用的，例如发生反射，折射、散射 和 能量的衰减
class material {
public:
    // attenuation : 衰减, 能量的衰减
    // scattered : 散射, 散射出去的光线
    virtual void scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

#endif /* material_h */
