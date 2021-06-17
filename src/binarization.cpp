#include "../lib/image.h"

Image Image::binarization(int threshold) {
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            if (pix_val[height][width] < threshold)
                pix_val[height][width] = 0;
            else
                pix_val[height][width] = 255;
        }
    }

    return *this;
}

Image Image::p_tail() {
    double rate; std::cout << "Ratio to be the standard for binarization :", std::cin >> rate;

    // calc histogram
    std::vector<double> histogram_values(256, 0);
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            histogram_values[pix_val[height][width]] += 1;
        }
    }

    // Save the number of pixels that becomes the threshold
    double threshold_pixel_value = img_height * img_width * rate;

    int threshold = 255;
    double all_data = 0.;
    for (int i = 0; i < 255; ++i) {
        all_data += i * histogram_values[i];

        // Save the pixel value when the threshold is exceeded
        if (all_data > threshold_pixel_value) {
            threshold = i;
            break;
        }
    }

    return this->binarization(threshold);
}

Image Image::discriminant() {
    double sb2_max = 0.;
    int threshold_result = 0;
    for (int threshold = 0; threshold <= 255; ++threshold) {
        int num0 = 0, sum0 = 0;
        int num1 = 0, sum1 = 0;
        for (int height = 0; height < img_height; ++height) {
            for (int width = 0; width < img_width; ++width) {
                if (pix_val[height][width] < threshold) {
                    sum0 += pix_val[height][width];
                    num0++;
                } else {
                    sum1 += pix_val[height][width];
                    num1++;
                }
            }
        }

        double m0 = 0., m1 = 0.;
        if (num0 == 0)  m0 = 0.;
        else    m0 = sum0 / num0;
        if (num1 == 0)  m1 = 0.;
        else    m1 = sum1 / num1;

        double sb2 = num0 * num1 * (m0 - m1) * (m0 - m1);
        if (sb2 > sb2_max) {
            sb2_max = sb2;
            threshold_result = threshold;
        }
    }
    return this->binarization(threshold_result);
}

Image Image::expantion() {

}

Image Image::contraction() {

}