#include "image.h"

Image Image::readImage(const std::string& file_name) {
    // read grayscale image
    img = cv::imread(file_name, cv::IMREAD_GRAYSCALE);
    // error handling
    if (img.empty()) {
        std::cerr << "Failed to open image file : " << file_name << std::endl;
        exit(EXIT_FAILURE);
    }

    // save image pixel size
    img_height = img.size().height; img_width = img.size().width;

    // save image pixel values
    pix_val.resize(img_height, std::vector<unsigned char>(img_width));
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            pix_val[height][width] = img.data[img_width * height + width];
        }
    }

    std::cout << "Read success : " << file_name << std::endl;

    return *this;
}

Image Image::copyImage(const Image& base_image) {
    // copy image data
    img = base_image.img.clone();
    // error handling
    if (img.empty()) {
        std::cerr << "Failed to copy image file" << std::endl;
        exit(EXIT_FAILURE);
    }

    img_height = base_image.img_height; img_width = base_image.img_width;

    // copy image pixel values
    pix_val = base_image.pix_val;

    std::cout << "Copy success" << std::endl;

    return *this;
}

Image Image::writeImage(const std::string& file_name) {
    // load pixel values
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            img.data[img_width * height + width] = pix_val[height][width];
        }
    }

    // write image
    cv::imwrite(file_name, img);

    std::cout << "Write : " << file_name << std::endl;

    return *this;
}
