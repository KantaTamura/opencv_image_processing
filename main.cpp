#include "lib/image.h"
Image image;

int main(int argc, char* argv[]) {
    image
        .readImage("../SIDBA_Gray/LENNA.jpg")
        .writeImage("../result/LENNA_original.jpg")
        .makeHistogram("../result/histogram/LENNA_histogram_original.jpg")
        .binarization()
        .writeImage("../result/LENNA_bin_128.jpg")
        .makeHistogram("../result/histogram/LENNA_histogram_bin_128.jpg");
}
