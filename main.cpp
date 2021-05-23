#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
using namespace std;
typedef unsigned char uchar;

class Image {
    cv::Mat img;
    vector< vector< uchar > > pix_val;
    int img_height{}, img_width{};

public:
    Image() = default;
    Image readImage(const string& file_name);
    Image copyImage(const Image& base_image);
    Image writeImage(const string& file_name);

    Image posterization();
    Image changeLinear();
    Image gammaTransformation();

    Image makeHistogram();
};

int main(int argc, char* argv[]) {
    Image img;

    img
        .readImage("../SIDBA_Gray/LENNA.jpg")
        .gammaTransformation()
        .writeImage("../result/LENNA_result.jpg")
        .makeHistogram();

    return 0;
}

Image Image::readImage(const string& file_name) {
    // read grayscale image
    img = cv::imread(file_name, cv::IMREAD_GRAYSCALE);
    // error handling
    if (img.empty()) {
        cerr << "Failed to open image file : " << file_name << endl;
        exit(EXIT_FAILURE);
    }

    // save image pixel size
    img_height = img.size().height; img_width = img.size().width;

    // save image pixel values
    pix_val.resize(img_height, vector<uchar>(img_width));
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            pix_val[height][width] = img.data[img_width * height + width];
        }
    }

    cout << "Read success : " << file_name << endl;

    return *this;
}

Image Image::copyImage(const Image& base_image) {
    // copy image data
    img = base_image.img.clone();
    // error handling
    if (img.empty()) {
        cerr << "Failed to copy image file" << endl;
        exit(EXIT_FAILURE);
    }

    img_height = base_image.img_height; img_width = base_image.img_width;

    // copy image pixel values
    pix_val = base_image.pix_val;

    cout << "Copy success" << endl;

    return *this;
}

Image Image::writeImage(const string& file_name) {
    // load pixel values
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            img.data[img_width * height + width] = pix_val[height][width];
        }
    }

    // write image
    cv::imwrite(file_name, img);

    cout << "Write : " << file_name << endl;

    return *this;
}

Image Image::posterization() {
    // number of steps to split
    int steps;  cout << "number of steps :", cin >> steps;
    // number included in one step
    int diff = 256 / steps;

    // change pixel values
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            double step = (pix_val[height][width] / 256.) * steps;
            pix_val[height][width] = (uchar)step * diff;
        }
    }

    return *this;
}

Image Image::changeLinear() {
    // get max(min) values
    uchar max = -1, min = 255;
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
                pix_val[height][width] = (uchar)formula;
            }
        }
    }

    return *this;
}

Image Image::gammaTransformation() {
    double gamma;
    cout << "number of gamma :", cin >> gamma;
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            double formula = 255. * pow(pix_val[height][width] / 255., 1 / gamma);
            pix_val[height][width] = (uchar)formula;
        }
    }

    return *this;
}

Image Image::makeHistogram() {
    // calc histogram
    vector<double> histogram_values(256, 0);
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
//        cout << value << endl;
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

    cv::imwrite("../result/histogram.jpg", image_histogram);

    return *this;
}
