//
//  color.h
//  RayTracing
//
//  Created by 刘清峰 on 2022/6/18.
//

#ifndef color_h
#define color_h

#include "../vec3.h"
#include "../rtweekend.h"

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();
    
    // 求平均
    auto scale = 1.0 / samples_per_pixel;
    // 几乎所有的图像查看器都是有gama校正的，gama校正系数是2.2幂次方，这里直接开平方根处理
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);
    
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
         << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
         << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif /* color_h */
