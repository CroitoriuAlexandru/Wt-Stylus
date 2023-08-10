#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxes.h"
#include <Wt/WDialog.h>
#
struct BackgroundStyleClasses {
	std::vector<std::string> bg_attachment_classes;
	std::vector<std::string> bg_clip_classes;
	std::vector<std::string> bg_color_classes;
	std::vector<std::string> bg_origin_classes; 
	std::vector<std::string> bg_position_classes;
	std::vector<std::string> bg_repeat_classes;
	std::vector<std::string> bg_size_classes;

	std::vector<std::string> bg_image_classes;
	std::vector<std::string> bg_color_from_classes;
	std::vector<std::string> bg_color_via_classes;
	std::vector<std::string> bg_color_to_classes;
	std::vector<std::string> bg_gradient_step_from_classes;
	std::vector<std::string> bg_gradient_step_via_classes;
	std::vector<std::string> bg_gradient_step_to_classes;


	// those are used to create the classes 
	std::vector<std::string> color_intensity;
	std::vector<std::string> color_opacity;
	std::vector<std::string> gradient_step;


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
	std::string bg_color_from_step;
	std::string bg_color_via_step;
	std::string bg_color_to_step;



};


class ElementBackgroundWidget : public Wt::WTemplate
{
public:
	ElementBackgroundWidget();
	// margin and padding at the moment

	void setClasses(BackgroundData bgData);
    Wt::Signal<>& styleChanged() { return styleChanged_; };
	std::string getStyles();
	void resetStyles();
private:
	Wt::WTemplate* content_temp;
	BackgroundStyleClasses  colors;
	
	ComboBoxClassWithCustoms *comboBox_attachment;
	ComboBoxClassWithCustoms *comboBox_clip;
	ComboBoxClassWithCustoms *comboBox_origin;
	ComboBoxClassWithCustoms *comboBox_position;
	ComboBoxClassWithCustoms *comboBox_repeat;
	ComboBoxClassWithCustoms *comboBox_size;
	ComboBoxClassWithCustoms *comboBox_image;
	ComboBoxColors *comboBox_color;

	ComboBoxColors *comboBox_color_via;
	ComboBoxColors *comboBox_color_to;

	Wt::Signal<> styleChanged_;

	// bg custom regexp
	std::regex regex_custom_color =  std::regex("bg-\\[[\\S]*\\]");
	// bg-(inherit|current|transparent|black|white)
	std::regex regex_def_classes = std::regex("(bg|from|via|to)-(inherit|current|transparent|black|white)");
	// bg-((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)\/((100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)|\[[\S]*\])[ ]((from|via|to)-(0|5|10|15|20|25|30|35|40|45|50|55|60|65|70|75|80|85|90|95|100)%)?)
	std::regex regex_color_classes = std::regex("(bg|from|via|to)-((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)\\/((100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)|\\[[\\S]*\\]))");
};