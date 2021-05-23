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

    void posterization();
    void changeLinear();
};

int main(int argc, char* argv[]) {
    Image img;

    img.readImage("../SIDBA_Gray/LENNA.jpg");
    img.changeLinear();
    img.writeImage("../result/LENNA_result.jpg");

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

void Image::posterization() {
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
}

void Image::changeLinear() {
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
}