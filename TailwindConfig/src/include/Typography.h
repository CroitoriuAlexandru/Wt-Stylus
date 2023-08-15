#pragma once
#include "Base.h"

namespace Tailwind {

    class Typography {
    public:
        Typography(std::vector<std::string> spacing_variants = {});
        Propriety font_family;
        Propriety font_size;
        Propriety font_smoothing;
        Propriety font_style;
        Propriety font_weight;
        Propriety font_variant_numeric;
        Propriety letter_spacing;
        Propriety line_clamp;
        Propriety line_height;
        Propriety list_style_image;
        Propriety list_style_position;
        Propriety list_style_type;
        Propriety text_align;
        // text color will be implemented programaticaly
        Propriety text_decoration;
        // text decoration color will be implemented programaticaly
        Propriety text_decoration_style;
        Propriety text_decoration_thikness;
        Propriety text_underline_offset;
        Propriety text_transform;
        Propriety text_overflow;
        Propriety text_indent;
        Propriety vertical_align;
        Propriety whitespace;
        Propriety word_break;
        Propriety hyphens;
        Propriety content;

        std::string FontFamilyData();
        std::string FontSizeData();
        std::string FontSmoothingData();
        std::string FontStyleData();
        std::string FontWeightData();
        std::string FontVariantNumericData();
        std::string LetterSpacingData();
        std::string LineClampData();
        std::string LineHeightData();
        std::string ListStyleImageData();
        std::string ListStylePositionData();
        std::string ListStyleTypeData();
        std::string TextAlignData();
        std::string TextDecorationData();
        std::string TextDecorationStyleData();
        std::string TextDecorationThiknessData();
        std::string TextUnderlineOffsetData();
        std::string TextTransformData();
        std::string TextOverflowData();
        std::string TextIndentData();
        std::string VerticalAlignData();
        std::string WhitespaceData();
        std::string WordBreakData();
        std::string HyphensData();
        std::string ContentData();

    };

};
