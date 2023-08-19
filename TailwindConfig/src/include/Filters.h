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


        boost::regex blur_regex = boost::regex("(?<=\n| )(!)?blur(-none|-sm|-md|-lg|-xl|-2xl|-3xl)?");
        boost::regex brightness_regex = boost::regex("(?<=\n| )(!)?brightness-(200|150|125|110|105|100|95|90|75|50|0)");
        boost::regex contrast_regex = boost::regex("(?<=\n| )(!)?contrast-(200|150|125|100|75|50|0)");
        boost::regex drop_shadow_regex = boost::regex("(?<=\n| )(!)?drop-shadow(-sm|-md|-lg|-xl|-2xl|-none)?");
        boost::regex grayscale_regex = boost::regex("(?<=\n| )(!)?grayscale(-0)?");
        boost::regex hue_rotate_regex = boost::regex("(?<=\n| )(!)?hue-rotate-(180|90|60|30|15|0)");
        boost::regex invert_regex = boost::regex("(?<=\n| )(!)?invert(-0)?");
        boost::regex saturate_regex = boost::regex("(?<=\n| )(!)?saturate-(200|150|100|50|0)");
        boost::regex sepia_regex = boost::regex("(?<=\n| )(!)?sepia(-0)?");
        boost::regex backdrop_blur_regex = boost::regex("(?<=\n| )(!)?backdrop-blur(-none|-sm|-md|-lg|-xl|-2xl|-3xl)?");
        boost::regex backdrop_brightness_regex = boost::regex("(?<=\n| )(!)?backdrop-brightness-(200|150|125|110|105|100|95|90|75|50|0)");
        boost::regex backdrop_contrast_regex = boost::regex("(?<=\n| )(!)?backdrop-contrast-(200|150|125|100|75|50|0)");
        boost::regex backdrop_grayscale_regex = boost::regex("(?<=\n| )(!)?backdrop-grayscale(-0)?");
        boost::regex backdrop_hue_rotate_regex = boost::regex("(?<=\n| )(!)?backdrop-hue-rotate-(180|90|60|30|15|0)");
        boost::regex backdrop_invert_regex = boost::regex("(?<=\n| )(!)?backdrop-invert(-0)?");
        boost::regex backdrop_opacity_regex = boost::regex("(?<=\n| )(!)?backdrop-opacity-(100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)");
        boost::regex backdrop_saturate_regex = boost::regex("(?<=\n| )(!)?backdrop-saturate-(200|150|100|50|0)");
        boost::regex backdrop_sepia_regex = boost::regex("(?<=\n| )(!)?backdrop-sepia(-0)?"); 
    };

};