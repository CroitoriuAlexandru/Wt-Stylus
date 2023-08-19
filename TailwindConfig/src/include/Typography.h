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

        
        boost::regex font_family_regex = boost::regex("(?<=\n| )(!)?font-(sans|serif|mono)(?!\\w|-)");
        boost::regex font_size_regex = boost::regex("(?<=\n| )(!)?text-(xs|sm|base|lg|xl|2xl|3xl|4xl|5xl|6xl|7xl|8xl|9xl)(?!\\w|-)");
        boost::regex font_smoothing_regex = boost::regex("(?<=\n| )(!)?(antialiased|subpixel-antialiased)(?!\\w|-)");
        boost::regex font_style_regex = boost::regex("(?<=\n| )(!)?(italic|not-italic)(?!\\w|-)");
        boost::regex font_weight_regex = boost::regex("(?<=\n| )(!)?font-(thin|extralight|light|normal|medium|semibold|extrabold|bold|black)(?!\\w|-)");
        boost::regex font_variant_numeric_regex = boost::regex("(?<=\n| )(!)?(normal-nums|ordinal|slashed-zero|lining-nums|oldstyle-nums|proportional-nums|tabular-nums|diagonal-fractions|stacked-fractions)(?!\\w|-)");
        boost::regex letter_spacing_regex = boost::regex("(?<=\n| )(!)?tracking-(widest|wider|wide|tighter|tight|normal)(?!\\w|-)");
        boost::regex line_clamp_regex = boost::regex("(?<=\n| )(!)?line-clamp-(1|2|3|4|5|6|none)(?!\\w|-)");
        boost::regex line_height_regex = boost::regex("(?<=\n| )(!)?leading-(10|9|8|7|6|5|4|3|none|tight|snug|normal|relaxed|loose)(?!\\w|-)");
        boost::regex line_style_image_regex = boost::regex("(?<=\n| )(!)?list-image-none(?!\\w|-)");
        boost::regex line_style_position_regex = boost::regex("(?<=\n| )(!)?list-(inside|outside)(?!\\w|-)");
        boost::regex line_style_type_regex = boost::regex("(?<=\n| )(!)?list-(none|disc|decimal)(?!\\w|-)");
        boost::regex text_align_regex = boost::regex("(?<=\n| )(!)?text-(left|center|right|justify|start|end)(?!\\w|-)");
        // text color will be implemented programaticaly
        boost::regex text_decoration_regex = boost::regex("(?<=\n| )(!)?(underline|overline|line-through|no-underline)(?!\\w|-)");
        // text decoration color will be implemented programaticaly
        boost::regex text_decoration_style_regex = boost::regex("(?<=\n| )(!)?decoration-(solid|double|dotted|dashed|wavy)(?!\\w|-)");
        boost::regex text_decoration_thikness_regex = boost::regex("(?<=\n| )(!)?decoration-(auto|from-font|0|1|2|4|8)(?!\\w|-)");
        boost::regex text_underline_offset_regex = boost::regex("(?<=\n| )(!)?underline-offset-(auto|0|1|2|4|8)(?!\\w|-)");
        boost::regex text_transform_regex = boost::regex("(?<=\n| )(!)?(uppercase|lowercase|capitalize|normal-case)(?!\\w|-)");
        boost::regex text_overflow_regex = boost::regex("(?<=\n| )(!)?(truncate|text-(ellipsis|clip))(?!\\w|-)");
        boost::regex text_indent_regex = boost::regex("(?<=\n| )(!)?indent-(96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px)(?!\\w|-)");
        boost::regex vertical_align_regex = boost::regex("(?<=\n| )(!)?align-(baseline|top|middle|bottom|text-top|text-bottom|sub|super)(?!\\w|-)");
        boost::regex whitespace_regex = boost::regex("(?<=\n| )(!)?whitespace-(normal|nowrap|pre-line|pre-wrap|pre|break-spaces)(?!\\w|-)");
        boost::regex word_break_regex = boost::regex("(?<=\n| )(!)?break-(normal|words|all|keep)(?!\\w|-)");
        boost::regex hyphens_regex = boost::regex("(?<=\n| )(!)?hyphens-(none|manual|auto)(?!\\w|-)");
        boost::regex content_regex = boost::regex("(?<=\n| )(!)?content-none(?!\\w|-)");

        std::string fontFamilyData();
        std::string fontSizeData();
        std::string fontSmoothingData();
        std::string fontStyleData();
        std::string fontWeightData();
        std::string fontVariantNumericData();
        std::string letterSpacingData();
        std::string lineClampData();
        std::string lineHeightData();
        std::string listStyleImageData();
        std::string listStylePositionData();
        std::string listStyleTypeData();
        std::string textAlignData();
        std::string textDecorationData();
        std::string textDecorationStyleData();
        std::string textDecorationThiknessData();
        std::string textUnderlineOffsetData();
        std::string textTransformData();
        std::string textOverflowData();
        std::string textIndentData();
        std::string verticalAlignData();
        std::string whitespaceData();
        std::string wordBreakData();
        std::string hyphensData();
        std::string contentData();


    };

};
