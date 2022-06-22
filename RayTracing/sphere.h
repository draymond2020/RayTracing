//
//  sphere.h
//  RayTracing
//
//  Created by 刘清峰 on 2022/6/19.
//

#ifndef sphere_h
#define sphere_h


class sphere : public hittable {
public:
    sphere(){}
    sphere(point3 cen, double r) : center(cen), radius(r) {}
    
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
    
public:
    point3 center;
    double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto h = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = h * h - a * c;
    // 如果函数无解则直接返回false
    if(discriminant < 0) {
        return false;
    }
    auto sqrtd = sqrt(discriminant);
    // 找到t_min,t_max 范围内最小的root
    auto root = ((-h - sqrtd) / a);
    if(root < t_min || t_max < root) {
        root = ((-h + sqrtd) / a);
        if(root < t_min || t_max < root) {
            return false;
        }
    }
    
    rec.t = root;
    rec.p = r.at(rec.t);
    // 
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    
    return true;
}

#endif /* sphere_h */
