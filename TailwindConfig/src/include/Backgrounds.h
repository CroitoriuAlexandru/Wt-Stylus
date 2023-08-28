#pragma once
#include "Base.h"
#include <iostream>

namespace Tailwind {

    class Backgrounds {
    public:
        Backgrounds(std::vector<std::string> colors_default_variants = {}, 
                    std::vector<std::string> colors_variants = {}, 
                    Propriety color_intensity_propriety = Propriety(),
                    Propriety color_opacity_propriety = Propriety(), 
                    std::vector<std::string> gradient_stops_variants = {});

        std::vector<std::string> colors_default_variants;

        Propriety background_attachment;
        Propriety background_clip;
        
        ProprietyColor background_color;
        ProprietyColor background_color_from;
        ProprietyColor background_color_via;
        ProprietyColor background_color_to;
        
        Propriety background_origin;
        Propriety background_position;
        Propriety background_repeat;
        Propriety background_size;
        Propriety background_image;
        
        Propriety gradient_stops_from;
        Propriety gradient_stops_via;
        Propriety gradient_stops_to;

        std::vector<std::string> search_data();

        std::string backgroundAttachmentData();
        std::string backgroundClipData();
        std::string backgroundColorData();
        std::string backgroundOriginData();
        std::string backgroundPositionData();
        std::string backgroundRepeatData();
        std::string backgroundSizeData();
        std::string backgroundImageData();
        std::string gradientStopsData();

        boost::regex background_attachment_regex = boost::regex(R"((?<!\S)(!)(!)?bg-(fixed|local|scroll)(?!\w|-))");
        // boost::regex background_attachment_regex = boost::regex("(?<!\\S)(!)(!)?bg-(fixed|local|scroll)(?!\\w|-)");
        boost::regex background_clip_regex = boost::regex("(?<=\n| )(!)?bg-clip-(border|padding|content|text)(?!\\w|-)");
        boost::regex background_color_regex = boost::regex(R"((?<!\S)(!)?bg-((\[[\S]*\])|((inherit|current|transparent|black|white)|((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|100|50)))(\/(100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0))?)(?!\\w|-|\/))");
        boost::regex background_color_from_regex = boost::regex(R"((?<!\S)(!)?from-((\[[\S]*\])|((inherit|current|transparent|black|white)|((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|100|50)))(\/(100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0))?)(?!\\w|-|\/))");
        boost::regex background_color_via_regex = boost::regex(R"((?<!\S)(!)?via-((\[[\S]*\])|((inherit|current|transparent|black|white)|((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|100|50)))(\/(100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0))?)(?!\\w|-|\/))");
        boost::regex background_color_to_regex = boost::regex(R"((?<!\S)(!)?to-((\[[\S]*\])|((inherit|current|transparent|black|white)|((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|100|50)))(\/(100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0))?)(?!\\w|-|\/))");
        boost::regex background_origin_regex = boost::regex("(?<=\n| )(!)?bg-origin-(border|padding|content)(?!\\w|-)");
        boost::regex background_position_regex = boost::regex("(?<=\n| )(!)?bg-(bottom|center|left|left-bottom|left-top|right|right-bottom|right-top|top)(?!\\w|-)");
        boost::regex background_repeat_regex = boost::regex("(?<=\n| )(!)?bg-(repeat|no-repeat|repeat-x|repeat-y|repeat-round|repeat-space)(?!\\w|-)");
        boost::regex background_size_regex = boost::regex("(?<=\n| )(!)?bg-(auto|cover|contain)(?!\\w|-)");
        boost::regex background_image_regex = boost::regex("bg-(gradient-to-(tr|tl|br|bl|r|b|t|l)|none)(?!\\w|-)");

        boost::regex background_color_from_step = boost::regex("(?<=\n| )(!)?from-(0|5|10|15|20|25|30|35|40|45|50|55|60|65|70|75|80|85|90|95|100)%(?!\\w|-)");
        boost::regex background_color_via_step = boost::regex("(?<=\n| )(!)?via-(0|5|10|15|20|25|30|35|40|45|50|55|60|65|70|75|80|85|90|95|100)%(?!\\w|-)");
        boost::regex background_color_to_step = boost::regex("(?<=\n| )(!)?to-(0|5|10|15|20|25|30|35|40|45|50|55|60|65|70|75|80|85|90|95|100)%(?!\\w|-)");

        
    };

};
