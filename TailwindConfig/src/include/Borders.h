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


        // used just for printing
        std::string BorderRadiusData();
        std::string BorderWidthData();
        std::string BorderStyleData();
        std::string DivideData();
        std::string OutlineData();
        std::string RingData();
        
    };
};

