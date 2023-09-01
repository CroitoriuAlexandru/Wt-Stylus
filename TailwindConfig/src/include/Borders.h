#pragma once
#include "Base.h"

namespace Tailwind {

    class Borders {
    public:
        Borders();
        Propriety border_radius;
        Propriety border_radius_s;
        Propriety border_radius_e;
        Propriety border_radius_t;
        Propriety border_radius_r;
        Propriety border_radius_b;
        Propriety border_radius_l;
        Propriety border_radius_ss;
        Propriety border_radius_se;
        Propriety border_radius_ee;
        Propriety border_radius_es;
        Propriety border_radius_tl;
        Propriety border_radius_tr;
        Propriety border_radius_br;
        Propriety border_radius_bl;

        Propriety border_width;
        Propriety border_width_x;
        Propriety border_width_y;
        Propriety border_width_t;
        Propriety border_width_r;
        Propriety border_width_b;
        Propriety border_width_l;
        Propriety border_width_s;
        Propriety border_width_e;
        // border color has to many classes and its interpreted programaticaly
        Propriety border_style;
        Propriety divide_x;
        Propriety divide_y;
        Propriety divide_x_reverse;
        Propriety divide_y_reverse;
        // divide color has to many classes and its interpreted programaticaly
        Propriety divide_style;
        Propriety outline_width;
        // outline color has to many classes and its interpreted programaticaly
        Propriety outline_style;
        Propriety outline_offset;
        Propriety ring_width;
        // ring color has to many classes and its interpreted programaticaly
        Propriety ring_offset_width;
        // ring offset color has to many classes and its interpreted programaticaly

        std::vector<std::string> search_data();

        // used just for printing
        std::string borderRadiusData();
        std::string borderWidthData();
        std::string borderStyleData();
        std::string divideData();
        std::string outlineData();
        std::string ringData();

        boost::regex border_radius_regex = boost::regex("(?<!\\S)(!)?rounded(-none|-sm|-md|-lg|-xl|-2xl|-3xl|-full|-ss|-se|-ee|-es|-tl|-tr|-br|-bl|-s|-e|-t|-l|-b|-r)?(-none|-sm|-md|-lg|-xl|-2xl|-3xl|-full)?(?!\\w|-)");
        boost::regex border_width_regex = boost::regex("(?<!\\S)(!)?border(-x|-y|-t|-l|-b|-r|-s|-e)?(-0|-2|-4|-8)?(?!\\w|-)");
        boost::regex border_style_regex = boost::regex("(?<!\\S)(!)?border-(solid|dashed|dotted|double|hidden|none)(?!\\w|-)");
        boost::regex divide_width_regex = boost::regex("(?<!\\S)(!)?divide(-x|-y)?(-0|-2|-4|-8|-reverse)?(?!\\w|-)");
        boost::regex divide_style_regex = boost::regex("(?<!\\S)(!)?divide-(solid|dashed|dotted|double|none)(?!\\w|-)");
        boost::regex outline_width_regex = boost::regex("(?<!\\S)(!)?outline-(0|1|2|4|8)?(?!\\w|-)");
        boost::regex outline_style_regex = boost::regex("(?<!\\S)(!)?outline(-none|-dashed|-dotted|-double)?(?!\\w|-)");
        boost::regex outline_offset_regex = boost::regex("(?<!\\S)(!)?outline-offset-(0|1|2|4|8)?(?!\\w|-)");
        boost::regex ring_width_regex = boost::regex("(?<!\\S)(!)?ring(-0|-1|-2|-4|-8|-inset)?(?!\\w|-)");
        // ring color
        boost::regex ring_offset_width_regex = boost::regex("(?<!\\S)(!)?ring-offset-(0|1|2|4|8)?(?!\\w|-)");
        // ring offset color
    };
};

