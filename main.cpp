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
    void readImage(const string& file_name);
    void copyImage(const Image& base_image);
    void writeImage(const string& file_name);
};

int main(int argc, char* argv[]) {
    Image img;

    img.readImage("../SIDBA_Gray/LENNA.jpg");
    img.writeImage("../LENNA_result.jpg");

    return 0;
}

void Image::readImage(const string& file_name) {
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
}

void Image::copyImage(const Image& base_image) {
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
}

void Image::writeImage(const string& file_name) {
    // load pixel values
    for (int height = 0; height < img_height; ++height) {
        for (int width = 0; width < img_width; ++width) {
            img.data[img_width * height + width] = pix_val[height][width];
        }
    }

    // write image
    cv::imwrite(file_name, img);

    cout << "Write : " << file_name << endl;
}