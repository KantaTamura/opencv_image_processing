#include "../lib/image.h"

Image Image::makeHistogram(const std::string& file_name) {
    // calc histogram
    std::vector<double> histogram_values(256, 0);
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            histogram_values[pix_val[height][width]] += 1;
        }
    }

    // get max histogram value
    auto max_histogram_value = *max_element(histogram_values.begin(), histogram_values.end());

    // normalize
    for (auto& value : histogram_values) {
        value /= max_histogram_value;
    }

    // print normalized histogram values
    //    for (auto value : histogram_values) {
    //        std::cout << value << std::endl;
    //    }

    // output histogram image
    cv::Mat image_histogram;

    // specify the image size
    image_histogram = cv::Mat(cv::Size(276,110), CV_8UC3, cv::Scalar(255,255,255));

    // draw range
    rectangle(image_histogram, cv::Point(10, 10),
              cv::Point(265, 100), cv::Scalar(230, 230, 230), -1);

    // draw histogram
    for (int i = 0; i <= 255; ++i) {
        line(image_histogram, cv::Point(10 + i, 100),
             cv::Point(10 + i, 100 - (int)(histogram_values[i] * 80)),
             cv::Scalar(98,169,255), 1, 8, 0);

        // additional line (spacing 10)
        if (i % 10 == 0)
            line(image_histogram, cv::Point(10+i, 100), cv::Point(10+i, 10),
                 cv::Scalar(170,170,170), 1, 8, 0);

        // additional line (spacing 50)
        if (i % 50 == 0)
            line(image_histogram, cv::Point(10+i, 100), cv::Point(10+i, 10),
                 cv::Scalar(50,50,50), 1, 8, 0);
    }

    cv::imwrite(file_name, image_histogram);

    return *this;
}