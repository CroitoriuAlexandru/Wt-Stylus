#pragma once
#include "Base.h"

namespace Tailwind {

    class Filters {
    public:
        Filters();
        Propriety blur;
        Propriety brightness;
        Propriety contrast;
        Propriety drop_shadow;
        Propriety grayscale;
        Propriety hue_rotate;
        Propriety invert;
        Propriety saturate;
        Propriety sepia;
        Propriety backdrop_blur;
        Propriety backdrop_brightness;
        Propriety backdrop_contrast;
        Propriety backdrop_grayscale;
        Propriety backdrop_hue_rotate;
        Propriety backdrop_invert;
        Propriety backdrop_opacity;
        Propriety backdrop_saturate;
        Propriety backdrop_sepia;
        
        std::vector<std::string> search_data();

        std::string blurData();
        std::string brightnessData();
        std::string contrastData();
        std::string dropShadowData();
        std::string grayscaleData();
        std::string hueRotateData();
        std::string invertData();
        std::string saturateData();
        std::string sepiaData();
        std::string backdropBlurData();
        std::string backdropBrightnessData();
        std::string backdropContrastData();
        std::string backdropGrayscaleData();
        std::string backdropHueRotateData();
        std::string backdropInvertData();
        std::string backdropOpacityData();
        std::string backdropSaturateData();
        std::string backdropSepiaData();


        boost::regex blur_regex = boost::regex("(?<!\\S)(!)?blur(-none|-sm|-md|-lg|-xl|-2xl|-3xl)?(?!\\w|-)");
        boost::regex brightness_regex = boost::regex("(?<!\\S)(!)?brightness-(200|150|125|110|105|100|95|90|75|50|0)(?!\\w|-)");
        boost::regex contrast_regex = boost::regex("(?<!\\S)(!)?contrast-(200|150|125|100|75|50|0)(?!\\w|-)");
        boost::regex drop_shadow_regex = boost::regex("(?<!\\S)(!)?drop-shadow(-sm|-md|-lg|-xl|-2xl|-none)?(?!\\w|-)");
        boost::regex grayscale_regex = boost::regex("(?<!\\S)(!)?grayscale(-0)?(?!\\w|-)");
        boost::regex hue_rotate_regex = boost::regex("(?<!\\S)(!)?hue-rotate-(180|90|60|30|15|0)(?!\\w|-)");
        boost::regex invert_regex = boost::regex("(?<!\\S)(!)?invert(-0)?(?!\\w|-)");
        boost::regex saturate_regex = boost::regex("(?<!\\S)(!)?saturate-(200|150|100|50|0)(?!\\w|-)");
        boost::regex sepia_regex = boost::regex("(?<!\\S)(!)?sepia(-0)?(?!\\w|-)");
        boost::regex backdrop_blur_regex = boost::regex("(?<!\\S)(!)?backdrop-blur(-none|-sm|-md|-lg|-xl|-2xl|-3xl)?(?!\\w|-)");
        boost::regex backdrop_brightness_regex = boost::regex("(?<!\\S)(!)?backdrop-brightness-(200|150|125|110|105|100|95|90|75|50|0)(?!\\w|-)");
        boost::regex backdrop_contrast_regex = boost::regex("(?<!\\S)(!)?backdrop-contrast-(200|150|125|100|75|50|0)(?!\\w|-)");
        boost::regex backdrop_grayscale_regex = boost::regex("(?<!\\S)(!)?backdrop-grayscale(-0)?(?!\\w|-)");
        boost::regex backdrop_hue_rotate_regex = boost::regex("(?<!\\S)(!)?backdrop-hue-rotate-(180|90|60|30|15|0)(?!\\w|-)");
        boost::regex backdrop_invert_regex = boost::regex("(?<!\\S)(!)?backdrop-invert(-0)?(?!\\w|-)");
        boost::regex backdrop_opacity_regex = boost::regex("(?<!\\S)(!)?backdrop-opacity-(100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)(?!\\w|-)");
        boost::regex backdrop_saturate_regex = boost::regex("(?<!\\S)(!)?backdrop-saturate-(200|150|100|50|0)(?!\\w|-)");
        boost::regex backdrop_sepia_regex = boost::regex("(?<!\\S)(!)?backdrop-sepia(-0)?(?!\\w|-)"); 
    };

};