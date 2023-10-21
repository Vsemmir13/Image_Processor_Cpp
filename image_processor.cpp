#include "Classes_and_Functions/Image/Image.h"
#include "Filters/Crop/Crop.h"
#include "Classes_and_Functions/Format_Command/Format_command.h"
#include "Filters/Grayscale/Grayscale.h"
#include "Filters/Negative/Negative.h"
#include "Filters/Sharpening/Sharpening.h"
#include "Filters/Edge_Detection/Edge_Detection.h"
#include "Filters/Gaussian_Blur/Gaussian_Blur.h"
#include "Filters/Pixelize/Pixelize.h"
#include <stdexcept>
#include <iostream>
#include <unordered_map>

int main(int argc, char** argv) {
    try {
        void (*crop)(Image&, std::vector<std::string>) = UseCrop;
        void (*neg)(Image&, std::vector<std::string>) = UseNegative;
        void (*gs)(Image&, std::vector<std::string>) = UseGrayscale;
        void (*sharp)(Image&, std::vector<std::string>) = UseSharpening;
        void (*edge)(Image&, std::vector<std::string>) = UseEdgeDetection;
        void (*blur)(Image&, std::vector<std::string>) = UseGaussianBlur;
        void (*px)(Image&, std::vector<std::string>) = UsePixelize;
        std::unordered_map<std::string_view, void (*)(Image&, std::vector<std::string>)> apply_filters = {
            {"crop", crop}, {"neg", neg}, {"gs", gs}, {"sharp", sharp}, {"edge", edge}, {"blur", blur}, {"px", px}};
        std::vector<Filter> filters_command = CommandSplit(argc, argv);
        Image picture;
        picture.Read(argv[1]);
        for (const Filter& filter : filters_command) {
            apply_filters[filter.name_filter](picture, filter.arguments);
        }
        picture.Create(argv[2]);
    } catch (const std::exception& ex) {
        std::cerr << "Упс, что-то пошло не так: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
