#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxes.h"
#include <Wt/WDialog.h>
#include <Wt/WPanel.h>

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


class ElementBackgroundWidget : public Wt::WPanel
{
public:
	ElementBackgroundWidget(std::shared_ptr<Config> tailwindConfig);
	// margin and padding at the moment


	void setClasses(BackgroundData bgData);
    Wt::Signal<>& styleChanged() { return styleChanged_; };
	std::string getStyles();
	void resetStyles();
private:
	void setCustomTestValues();
	
	Wt::WTemplate* content_temp;
	std::shared_ptr<Config> tailwindConfig_;
	
	ComboBoxClassWithCustoms *comboBox_attachment;
	ComboBoxClassWithCustoms *comboBox_clip;
	ComboBoxClassWithCustoms *comboBox_origin;
	ComboBoxClassWithCustoms *comboBox_position;
	ComboBoxClassWithCustoms *comboBox_repeat;
	ComboBoxClassWithCustoms *comboBox_size;
	ComboBoxClassWithCustoms *comboBox_image;
	BackgroundColorWidget *comboBox_color;

	BackgroundColorWidget *comboBox_color_via;
	BackgroundColorWidget *comboBox_color_to;

	Wt::Signal<> styleChanged_;

	// bg custom regexp
	std::regex regex_custom_color =  std::regex("bg-\\[[\\S]*\\]");
	// bg-(inherit|current|transparent|black|white)
	std::regex regex_def_classes = std::regex("(bg|from|via|to)-(inherit|current|transparent|black|white)");
	// bg-((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)\/((100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)|\[[\S]*\])[ ]((from|via|to)-(0|5|10|15|20|25|30|35|40|45|50|55|60|65|70|75|80|85|90|95|100)%)?)
	std::regex regex_color_classes = std::regex("(bg|from|via|to)-((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)\\/((100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)|\\[[\\S]*\\]))");
};