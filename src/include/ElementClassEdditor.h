#pragma once
#include "ElementSpacing.h"
#include "ElementSizing.h"
#include "ElementBackground.h"

#include <Wt/WTemplate.h>
#include <Wt/WSignal.h>
#include <regex>

class ElementClassEdditor : public Wt::WTemplate
{
public:
    ElementClassEdditor();

    void setStyleClasses(std::string classes);
    Wt::Signal<std::string> &styleChanged() { return styleChanged_; }

    void resetStyles();
    Wt::WPushButton* spacing_btn_display;
    Wt::WPushButton* sizing_btn_display;
    Wt::WPushButton* background_btn_display;

    std::string getStyles();
private:
    std::vector<std::string> findAndRemoveMatches(std::regex regex, std::string& str);
    std::string findAndRemoveMatche(std::regex regex, std::string& str);

    ElementBackgroundWidget *backgroundWidget_;
    ElementSpacingWidget *spacingWidget_;
    ElementSizingWidget *sizingWidget_;

    std::string notFoundClasses = "";
    std::string backgroundClasses = "";
    std::string spacingClasses = "";
    std::string sizingClasses = "";

    Wt::Signal<std::string> styleChanged_;


    // spacing regexp
    std::regex padding_regexp = std::regex("[!]?p[x,y,t,r,b,l]?-(?:96|80|72|64|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|0|px|[\\[\\S]*\\])");
    std::regex margin_regexp =  std::regex("[!]?-?m[x,y,t,r,b,l]?-(?:auto|96|80|72|64|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|0|px|[\\[\\S]*\\])");
    std::regex space_regexp = std::regex("[!]?space-[x|y]?-(?:reverse|96|80|72|64|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|0|px|[\\[\\S]*\\])");

    // sizing regexp
    std::regex width_regexp = std::regex("(?: |^)[!]?w-(?:fit|max|min|screen|full|11\\/12|10\\/12|9\\/12|8\\/12|7\\/12|6\\/12|5\\/12|4\\/12|3\\/12|2\\/12|1\\/12|5\\/6|4\\/6|3\\/6|2\\/6|1\\/6|4\\/5|3\\/5|2\\/5|1\\/5|3\\/4|2\\/4|1\\/4|2\\/3|1\\/3|1\\/2|auto|96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|px|0|\\[\\S*\\])");
    std::regex minWidth_regex = std::regex("[!]?min-w-(?:0|full|min|max|fit|\\[[\\S]*\\])");
    std::regex maxWidth_regex = std::regex("[!]?max-w-(?:0|none|xs|sm|md|ls|lg|xl|2xl|3xl|4xl|5xl|6xl|7xl|full|min|max|fit|prose|screen-sm|screen-md|screen-lg|screen-xl|screen-2x|\\[[\\S]*\\])");
    
    std::regex height_regexp = std::regex("(?: |^)[!]?h-(?:full|screen|min|max|fit|11\\/12|10\\/12|9\\/12|8\\/12|7\\/12|6\\/12|5\\/12|4\\/12|3\\/12|2\\/12|1\\/12|5\\/6|4\\/6|3\\/6|2\\/6|1\\/6|4\\/5|3\\/5|2\\/5|1\\/5|3\\/4|2\\/4|1\\/4|2\\/3|1\\/3|1\\/2|auto|96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|px|0|\\[\\S*\\])");
    std::regex minHeight_regex = std::regex("[!]?min-h-(?:0|full|screen|min|max|fit|\\[[\\S]*\\])");
    std::regex maxHeight_regex = std::regex("[!]?max-h-(?:96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px|none|full|screen|min|max|fit|\\[[\\S]*\\])");

    // background regexp

    std::regex background_attachment_regex = std::regex("[!]?bg-(fixed|local|scroll)");
    std::regex background_clip_regex = std::regex("[!]?bg-clip-(border|padding|content|text)");
    std::regex background_color_regexp = std::regex("[!]?bg-((inherit|current|transparent|black|white|\\[[\\S]*\\])|(slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)?\\/((100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)|\\[[\\S]*\\]))");
	std::regex background_origin_regex = std::regex("[!]?bg-origin-(border|padding|content)");
    std::regex background_position_regex = std::regex("[!]?bg-(bottom|center|left|left-bottom|left-top|right|right-bottom|right-top|top)");
    std::regex background_repeat_regex = std::regex("[!]?bg-(repeat|no-repeat|repeat-x|repeat-y|repeat-round|repeat-space)");
    std::regex background_size_regex = std::regex("[!]?bg-(auto|cover|contain)");
    std::regex background_image_regex = std::regex("bg-gradient-to-(tr|tl|br|bl|r|b|t|l)");
    std::regex background_color_from_regex = std::regex("[!]?from-((inherit|current|transparent|black|white|\\[[\\S]*\\])|(slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)?\\/((100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)|\\[[\\S]*\\]))");
    std::regex background_color_via_regex = std::regex("[!]?via-((inherit|current|transparent|black|white|\\[[\\S]*\\])|(slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)?\\/((100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)|\\[[\\S]*\\]))");
    std::regex background_color_to_regex = std::regex("[!]?to-((inherit|current|transparent|black|white|\\[[\\S]*\\])|(slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)?\\/((100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)|\\[[\\S]*\\]))");

    std::regex background_color_from_step = std::regex("from-(0|5|10|15|20|25|30|35|40|45|50|55|60|65|70|75|80|85|90|95|100)%");
    std::regex background_color_via_step = std::regex("via-(0|5|10|15|20|25|30|35|40|45|50|55|60|65|70|75|80|85|90|95|100)%");
    std::regex background_color_to_step = std::regex("to-(0|5|10|15|20|25|30|35|40|45|50|55|60|65|70|75|80|85|90|95|100)%");

};
