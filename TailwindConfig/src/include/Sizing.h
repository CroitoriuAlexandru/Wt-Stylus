#pragma once
#include "Base.h"

namespace Tailwind {

    class Sizing {
    public:
        Sizing(std::vector<std::string> sizing_variants = {});
        Propriety width;
        Propriety min_width;
        Propriety max_width;

        Propriety height;
        Propriety min_height;
        Propriety max_height;
        
        std::string widthData();
        std::string heightData();
        std::string minWidthData();
        std::string maxWidthData();
        std::string minHeightData();
        std::string maxHeightData();
        
        std::vector<std::string> search_data();

        boost::regex width_regex = boost::regex("(?<=\n| )(!)?w-(fit|max|min|screen|full|11\\/12|10\\/12|9\\/12|8\\/12|7\\/12|6\\/12|5\\/12|4\\/12|3\\/12|2\\/12|1\\/12|5\\/6|4\\/6|3\\/6|2\\/6|1\\/6|4\\/5|3\\/5|2\\/5|1\\/5|3\\/4|2\\/4|1\\/4|2\\/3|1\\/3|1\\/2|auto|96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|px|0|\\[\\S*\\])(?!\\w|-)");

        boost::regex min_width_regex = boost::regex("(?<=\n| )(!)?min-w-(0|full|min|max|fit|\\[[\\S]*\\])(?!\\w|-)");
        boost::regex max_width_regex = boost::regex("(?<=\n| )(!)?max-w-(0|none|xs|sm|md|ls|lg|xl|2xl|3xl|4xl|5xl|6xl|7xl|full|min|max|fit|prose|screen-sm|screen-md|screen-lg|screen-xl|screen-2xl|\\[[\\S]*\\])(?!\\w|-)");
        
        boost::regex height_regex = boost::regex("(?<=\n| )(!)?h-(full|screen|min|max|fit|11\\/12|10\\/12|9\\/12|8\\/12|7\\/12|6\\/12|5\\/12|4\\/12|3\\/12|2\\/12|1\\/12|5\\/6|4\\/6|3\\/6|2\\/6|1\\/6|4\\/5|3\\/5|2\\/5|1\\/5|3\\/4|2\\/4|1\\/4|2\\/3|1\\/3|1\\/2|auto|96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|px|0|\\[\\S*\\])(?!\\w|-)");
        boost::regex min_height_regex = boost::regex("(?<=\n| )(!)?min-h-(0|full|screen|min|max|fit|\\[[\\S]*\\])(?!\\w|-)");
        boost::regex max_height_regex = boost::regex("(?<=\n| )(!)?max-h-(96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px|none|full|screen|min|max|fit|\\[[\\S]*\\])(?!\\w|-)");
    };
    
};
