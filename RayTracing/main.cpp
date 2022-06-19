//
//  main.cpp
//  RayTracing
//
//  Created by 刘清峰 on 2022/6/18.
//

#include <iostream>
#include "vec3.h"
#include "common/color.h"
#include "common/ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include "rtweekend.h"
#include "camera.h"
/*
 光线与球的相交算法
 球体方程：x^2 + y^2 + z^2 = R^2
 给定一个点P（x,y,z）,如果点在球面上 x^2 + y^2 + z^2 = R^2，在球外 x^2 + y^2 + z^2 > R^2，在球内 x^2 + y^2 + z^2 < R^2
 如果球心是 C（Cx, Cy, Cz）,
 1、(x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2 = r^2
 2、(x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2 = （P - C）*（P - C）
 3、r^2 =（P - C）*（P - C）, 任何一点p满足此方程就在球面上
 4、射线方程：P(t) = A + tb, 则有 (A + tb - C) * (A + tb - C) = r^2 ，展开：t^2 * b * b + 2 * t * b *(A - C) + (A - C) * (A - C) - r^2 = 0;
 5、展开后的方程是 t 的2元一次方程，可知：t = ( -b 加减 根号下 b^2 - 4ac ) / 2a，也就是说 b^2 - 4ac > 0 就有根，有根就有交点
 6、a系数 = (b * b) , b系数 = (2 * b * (A - C)), c系数 = (A - C) * (A - C) - r^2， A:射线原点，b:射线方向，C:球中心点，r:球半径
 **/

/*
优化相交算法， 推理
( -b 加减 根号下 b^2 - 4ac ) / 2a  ， 设 b = 2h, h = dot(oc, r.direction())
那么 (-2h 加减 根号下 (2h)^2 - 4 * a * c) / 2a  => (-h 加减 根号下 h^2 - a * c) / a
    double hit_sphere(const point3& center, double radius, const ray& r) {
        vec3 oc = r.origin() - center;
        auto a = dot(r.direction(), r.direction());
        auto b = 2.0 * dot(oc, r.direction());
        auto c = dot(oc, oc) - radius * radius;
        auto discriminant = b * b - 4 * a * c;
        if(discriminant < 0) {
            return -1.0;
        } else {
            return ((-b - sqrt(discriminant)) / (2.0 * a));
        }
    }
*/

double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    // auto b = 2.0 * dot(oc, r.direction());
    auto h = dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = h * h - a * c;
    if(discriminant < 0) {
        return -1.0;
    } else {
        return ((-h - sqrt(discriminant)) / a);
    }
}
/*
color ray_color(const ray& r) {
    vec3 centerPoint = point3(0, 0, -1);  // 相对于摄像机坐标系
    auto t = hit_sphere(centerPoint, 0.5, r);
    if(t > 0.0) {
        // 交点到球心的向量的单位化，即法线
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        // 单位法线转换到 0.0 - 1.0
        double x = (N.x() - (-1.0)) / (1.0 - (-1.0));
        double y = (N.y() - (-1.0)) / (1.0 - (-1.0));
        double z = (N.z() - (-1.0)) / (1.0 - (-1.0));
        return vec3(x, y, z);
    }
    vec3 unit_direction = unit_vector(r.direction());   // 单位化后 -1.0 < y < 1.0;
    // 根据公式：X - minX / maxX - minX 转换到 0 < t < 1.0
    t = (unit_direction.y() - (-1.0)) / (1.0 - (-1.0));
    // 线性插值 lerp,当t=0时是白色，t=1是蓝色
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}
*/

color ray_color(const ray& r, const hittable_list& world) {
    vec3 centerPoint = point3(0, 0, -1);  // 相对于摄像机坐标系
    hit_record rec;
    bool isHit = world.hit(r, 0, infinity, rec);
    if(isHit) {
        vec3 N = rec.normal;
        // 单位法线转换到 0.0 - 1.0
        double x = (N.x() - (-1.0)) / (1.0 - (-1.0));
        double y = (N.y() - (-1.0)) / (1.0 - (-1.0));
        double z = (N.z() - (-1.0)) / (1.0 - (-1.0));
        return vec3(x, y, z);
    }
    vec3 unit_direction = unit_vector(r.direction());   // 单位化后 -1.0 < y < 1.0;
    // 根据公式：X - minX / maxX - minX 转换到 0 < t < 1.0
    auto t = (unit_direction.y() - (-1.0)) / (1.0 - (-1.0));
    // 线性插值 lerp,当t=0时是白色，t=1是蓝色
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main(int argc, const char * argv[]) {
    /*
    // Image,定义ppm格式图片的高宽
    const int image_width = 256;
    const int image_height = 256;
    // wirte ppm file, ppm file example
    // P3
    // # The P3 means colors are is ASCII, then 3 columns and 2 rows,
    // # then 255 for max color, then RGB triplets
    // 3 2
    // 255
    // 255  0  0   0  255  0   0 0 255
    // 255 255 0  255 255 255  0 0  0
    // Render
    std::cout << "P3\n" << image_width << ", " << image_height << "\n255\n";
    
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining " << j << " " << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
            write_color(std::cout, pixel_color);
        }
    }
    
    std::cerr << "\nDone.\n";
    */
    
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;  // 每个像素采样100根光线
    
    // world
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    
    // Camera
//    auto viewport_height = 2.0;
//    auto viewport_width = aspect_ratio * viewport_height;
//    auto focal_length = 1.0;
    
//    auto origin = point3(0, 0, 0);  // 原点
//    auto horizontal = vec3(viewport_width, 0, 0);   // x轴
//    auto vertical = vec3(0, viewport_height, 0);    // y轴
//    // 图片的左下角
//    auto lower_left_corner = vec3(-viewport_width * 0.5, -viewport_height * 0.5, -1);
    camera cam;
    
    // Render
    std::cout << "P3\n" << image_width << ", " << image_height << "\n255\n";
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining " << j << " " << std::flush;
        for (int i = 0; i < image_width; ++i) {
            // 纹理的uv坐标
//            auto u = double(i) / (image_width - 1);
//            auto v = double(j) / (image_height - 1);
//            // 构建一条光线，原点，方向
//            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
//            color pixel_color = ray_color(r, world);
//            write_color(std::cout, pixel_color);
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = double(i + random_double()) / (image_width - 1);
                auto v = double(j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
    return 0;
}
