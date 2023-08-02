#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxes.h"
#include <Wt/WDialog.h>
#
struct BackgroundStyleClasses {
	std::vector<std::string> bg_attachment_classes;
	std::vector<std::string> bg_clip_classes;
	std::vector<std::string> color_classes;
	std::vector<std::string> bg_origin_classes; 
	std::vector<std::string> bg_position_classes;
	std::vector<std::string> bg_repeat_classes;
	std::vector<std::string> bg_size_classes;
	std::vector<std::string> bg_image_classes;

	std::vector<std::string> color_intensity;
	std::vector<std::string> color_opacity;
	
	BackgroundStyleClasses();
};

struct BackgroundData
{
	// bg-(fixed|local|scroll)
	std::string bg_attachment;
	// bg-clip-(border|padding|content|text)
	std::string bg_clip;
	std::string bg_color_class;
	// bg-origin-(border|padding|content)
	std::string bg_origin;
	// bg-(bottom|center|left|left-bottom|left-top|right|right-bottom|right-top|top)
	std::string bg_position;
	// bg-(repeat|no-repeat|repeat-x|repeat-y|repeat-round|repeat-space)
	std::string bg_repeat;
	// bg-(auto|cover|contain)
	std::string bg_size;
	// bg-gradient-(to-t|to-tr|to-r|to-br|to-b|to-bl|to-l|to-tl)
	std::string bg_image;
	std::string bg_color_via;
	std::string bg_color_to;



};


class ElementBackgroundWidget : public Wt::WDialog
{
public:
	ElementBackgroundWidget(std::string templateName = "stylus.background.template");
	// margin and padding at the moment

	void setClasses(BackgroundData bgData);
    Wt::Signal<>& styleChanged() { return styleChanged_; };
	std::string getStyles();
	void resetStyles();
	void setCustom(bool custom) { comboBox_color->setCustom(custom); };
private:
	Wt::WTemplate* content_temp;
	
	ComboBoxClassWithCustoms *comboBox_attachment;
	ComboBoxClassWithCustoms *comboBox_clip;
	ComboBoxColors *comboBox_color;
	ComboBoxClassWithCustoms *comboBox_origin;
	ComboBoxClassWithCustoms *comboBox_position;
	ComboBoxClassWithCustoms *comboBox_repeat;
	ComboBoxClassWithCustoms *comboBox_size;
	ComboBoxClassWithCustoms *comboBox_image;

	ComboBoxColors *comboBox_color_via;
	ComboBoxColors *comboBox_color_to;

	Wt::Signal<> styleChanged_;

	// bg custom regexp
	std::regex regex_custom_color =  std::regex("[!]?bg-\\[[\\S]*\\]");
	// bg-(inherit|current|transparent|black|white)
	std::regex regex_def_classes = std::regex("[!]?bg-(inherit|current|transparent|black|white)");
	// bg-((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)?\/(100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0))
	std::regex regex_color_classes = std::regex("[!]?bg-((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)?\\/(100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0))");


};

