#include "src/image.h"
Image image;

int main(int argc, char* argv[]) {
    image
        .readImage("../SIDBA_Gray/House1.jpg")
        .filterOperation()
        .writeImage("../result/House1_median.jpg")
        .makeHistogram("../result/House1_median_histogram.jpg");
}
