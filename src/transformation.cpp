#include "../lib/image.h"

Image Image::posterization() {
    // number of steps to split
    int steps;  std::cout << "number of steps :", std::cin >> steps;
    // number included in one step
    int diff = 256 / steps;

    // change pixel values
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            double step = (pix_val[height][width] / 256.) * steps;
            pix_val[height][width] = (unsigned char)step * diff;
        }
    }

    return *this;
}

Image Image::changeLinear() {
    // get max(min) values
    unsigned char max = -1, min = 255;
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            if (pix_val[height][width] > max) max = pix_val[height][width];
            if (pix_val[height][width] < min) min = pix_val[height][width];
        }
    }

    // change pixel values
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            if (pix_val[height][width] < min) pix_val[height][width] = 0;
            else if (pix_val[height][width] > max) pix_val[height][width] = 255;
            else {
                double formula = 255. / (max - min) * (pix_val[height][width] - min);
                pix_val[height][width] = (unsigned char)formula;
            }
        }
    }

    return *this;
}

Image Image::gammaTransformation() {
    double gamma;
    std::cout << "number of gamma :", std::cin >> gamma;
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            double formula = 255. * pow(pix_val[height][width] / 255., 1 / gamma);
            pix_val[height][width] = (unsigned char)formula;
        }
    }

    return *this;
}