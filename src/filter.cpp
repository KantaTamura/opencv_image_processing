#include "image.h"

Image Image::filterOperation() {
    // define operation
    const int op[3][3] = {
            { 2, -2,  2},
            {-2,  4, -2},
            { 2, -2,  2},
            };

    // buffer pixel values
    std::vector< std::vector< int > > buf_pix_val(img_height, std::vector<int>(img_width, 0));

    // calculate operation
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            int sum = 0;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (height + (i - 1) < 0 || height + (i - 1) >= img_height
                    || width + (j - 1) < 0 || width + (j - 1) >= img_width)
                        continue;
                    sum += pix_val[height + (i - 1)][width + (j - 1)] * op[i][j];
                }
            }
            buf_pix_val[height][width] = sum;
        }
    }

    // search max(min) value
    int max = std::numeric_limits<int>::min(), min = std::numeric_limits<int>::max();
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            if (buf_pix_val[height][width] > max) max = buf_pix_val[height][width];
            if (buf_pix_val[height][width] < min) min = buf_pix_val[height][width];
        }
    }

    // change 256 steps
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            if (buf_pix_val[height][width] < min) buf_pix_val[height][width] = 0;
            else if (buf_pix_val[height][width] > max) buf_pix_val[height][width] = 255;
            else {
                double formula = (buf_pix_val[height][width] - min) * 255. / (max - min);
                pix_val[height][width] = (unsigned char)formula;
            }
        }
    }

    return *this;
}

Image Image::medianFilter() {
    std::vector< std::vector< unsigned char > > buf_pix_val(img_height, std::vector<unsigned char>(img_width));

    // select median
    for (int height = 1; height < img_height - 1; ++height) {
        for (int width = 1; width < img_width - 1; ++width) {
            std::vector<unsigned char> val;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    val.push_back(pix_val[height + i][width + j]);
                }
            }
            sort(val.begin(), val.end());
            buf_pix_val[height][width] = val[4];
        }
    }

    // update pixel values
    for (int height = 1; height < img_height - 1; ++height) {
        for (int width = 1; width < img_width - 1; ++width) {
            pix_val[height][width] = buf_pix_val[height][width];
        }
    }

    return *this;
}