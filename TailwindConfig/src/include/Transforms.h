#pragma once
#include "Base.h"

namespace Tailwind {

    class Transforms {
    public:
        Transforms(std::vector<std::string> sizing_variants = {});
        Propriety scale;
        Propriety scale_x;
        Propriety scale_y;
        Propriety rotate;
        Propriety translate_x;
        Propriety translate_y;
        Propriety skew_x;
        Propriety skew_y;
        Propriety transform_origin;

        std::string ScaleData();
        std::string RotateData();
        std::string TranslateData();
        std::string SkewData();
        std::string TransformOriginData();
    };

};
