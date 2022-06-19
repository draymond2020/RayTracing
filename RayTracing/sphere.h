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
    
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    
public:
    point3 center;
    double radius;
};

bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto h = dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = h * h - a * c;
    if(discriminant < 0) {
        return false;
    }
    // 找到t_min,t_max 范围内最小的root
    auto root = ((-h - sqrt(discriminant)) / a);
    if(root < t_min || t_max < root) {
        root = ((-h + sqrt(discriminant)) / a);
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
