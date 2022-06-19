//
//  color.h
//  RayTracing
//
//  Created by 刘清峰 on 2022/6/18.
//

#ifndef color_h
#define color_h

#include "../vec3.h"

void write_color(std::ostream &out, color pixel_color) {
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
         << static_cast<int>(255.999 * pixel_color.y()) << ' '
         << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif /* color_h */
