#include "lib/image.h"
Image image;

int main(int argc, char* argv[]) {
    std::string input_img_name = "BRIDGE", output_img_name = "bin_192";
    image
        .readImage("../SIDBA_Gray/" + input_img_name + ".jpg")
        .writeImage("../result/" + input_img_name + "_original.jpg")
        .makeHistogram("../result/histogram/" + input_img_name + "_histogram_original.jpg")
        .binarization()
        .writeImage("../result/" + input_img_name + "_" + output_img_name + ".jpg")
        .makeHistogram("../result/histogram/" + input_img_name + "_histogram_" + output_img_name + ".jpg");
}
