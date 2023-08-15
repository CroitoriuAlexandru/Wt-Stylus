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

        std::string BlurData();
        std::string BrightnessData();
        std::string ContrastData();
        std::string DropShadowData();
        std::string GrayscaleData();
        std::string HueRotateData();
        std::string InvertData();
        std::string SaturateData();
        std::string SepiaData();
        std::string BackdropBlurData();
        std::string BackdropBrightnessData();
        std::string BackdropContrastData();
        std::string BackdropGrayscaleData();
        std::string BackdropHueRotateData();
        std::string BackdropInvertData();
        std::string BackdropOpacityData();
        std::string BackdropSaturateData();
        std::string BackdropSepiaData();

    };

};