#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

class Image {
    cv::Mat img;
    std::vector< std::vector< unsigned char > > pix_val;
    int img_height{}, img_width{};

public:
    Image() = default;
    // imageIO.cpp
    Image readImage(const std::string& file_name);
    Image copyImage(const Image& base_image);
    Image writeImage(const std::string& file_name);
    // transformation.cpp
    Image posterization();
    Image changeLinear();
    Image gammaTransformation();
    // filter.cpp
    Image filterOperation();
    Image medianFilter();
    // histogram.cpp
    Image makeHistogram(const std::string& file_name);
};

#endif // IMAGE_H
