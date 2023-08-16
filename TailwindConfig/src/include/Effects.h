#pragma once
#include "Base.h"

namespace Tailwind {

    class Effects {
    public:
        Effects(
                std::vector<std::string> opacity_variants = {},
                std::vector<std::string> base_colors_variants = {},
                std::vector<std::string> colors_variants = {},
                Propriety color_intensity_propriety = Propriety(),
                Propriety color_opacity_propriety = Propriety()
                );

        Propriety box_shadow;
        Propriety box_shadow_inset;
        ProprietyColor box_shadow_color;
        Propriety opacity;
        Propriety mix_blend_mode;
        Propriety background_blend_mode;


        std::string boxShadowData();
        std::string boxShadowColorData();
        std::string opacityData();
        std::string mixBlendModeData();

        std::regex box_shadow_regex = std::regex("(?![\n| ])shadow(-sm|-md|-lg|-xl|-2xl|-none|-inset|-inner| )");
        std::regex box_shadow_color_regex = std::regex("(?![\n| ])[!]?shadow-((inherit|current|transparent|black|white|\\[[\\S]*\\])|(slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)?\\/((100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)|\\[[\\S]*\\]))");
        std::regex opacity_regex = std::regex("(?![\n| ])opacity-(100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|\\[[\\S]*\\])");
        std::regex mix_blend_mode_regex = std::regex("(?![\n| ])mix-blend-(normal|multiply|screen|overlay|darken|lighten|color-dodge|color-burn|hard-light|soft-light|difference|exclusion|hue|saturation|color|luminosity)");
        std::regex bg_blend_mode_regex = std::regex("(?![\n| ])bg-blend-(normal|multiply|screen|overlay|darken|lighten|color-dodge|color-burn|hard-light|soft-light|difference|exclusion|hue|saturation|color|luminosity)");
    };

};
