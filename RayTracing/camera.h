//
//  camera.h
//  RayTracing
//
//  Created by 刘清峰 on 2022/6/19.
//

#ifndef camera_h
#define camera_h

class camera {
public:
    camera() {
        auto aspect_ratio = 16.0 / 9.0;     // 宽高比
        auto viewport_height = 2.0;         // 视口的高度
        auto viewport_width = aspect_ratio * viewport_height;   // 视口的宽度
        auto focal_length = 1.0;            // 相机的焦距
        
        origin = point3(0, 0, 0);
        horizontal = vec3(viewport_width, 0.0, 0.0);
        vertical = vec3(0.0, viewport_height, 0.0);
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0.0, 0.0, focal_length);
    }
    
    ray get_ray(double u, double v) const {
        return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }
    
private:
    point3 origin;              // 摄像机的原点
    point3 lower_left_corner;   // 2维图片的左下角
    vec3 horizontal;            // 水平轴
    vec3 vertical;              // 垂直轴
};

#endif /* camera_h */
