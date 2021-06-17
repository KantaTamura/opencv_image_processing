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

}

Image Image::discriminant() {

}

Image Image::expantion() {

}

Image Image::contraction() {

}