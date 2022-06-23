//
//  hittable.h
//  RayTracing
//
//  Created by 刘清峰 on 2022/6/19.
//

#ifndef hittable_h
#define hittable_h

class material;

struct hit_record {
    point3 p;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    double t;
    bool front_face;
    
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        // 光线方向 和 法线 的点乘 如果 < 0 ,则光线是从球内部进入， > 0 光线从球外部进入
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif /* hittable_h */
