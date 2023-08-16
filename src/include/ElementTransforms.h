#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxes.h"
#include <Wt/WDialog.h>
#include <Wt/WPanel.h>

struct TransformsData
{
	std::vector<std::string> scale;
	std::string rotate;
	std::vector<std::string> translate;
	std::vector<std::string> skew;
	std::string transform_origin;
};


class ElementTransformsWidget : public Wt::WPanel
{
public:
	ElementTransformsWidget(std::shared_ptr<Config> tailwindConfig);
	// margin and padding at the moment


	void setClasses(TransformsData transformsData);
    Wt::Signal<>& styleChanged() { return styleChanged_; };
	std::string getStyles();
	void resetStyles();
private:
	void setCustomTestValues();
	
	Wt::WTemplate* 				content_temp;
	std::shared_ptr<Config> 	tailwindConfig_;
	
	ComboBoxClassWithCustoms* 	comboBox_scale_;
	ComboBoxClassWithCustoms* 	comboBox_scale_x_;
	ComboBoxClassWithCustoms* 	comboBox_scale_y_;
	ComboBoxClassWithCustoms* 	comboBox_rotate_;
	ComboBoxClassWithCustoms* 	comboBox_translate_x_;
	ComboBoxClassWithCustoms* 	comboBox_translate_y_;
	ComboBoxClassWithCustoms* 	comboBox_skew_x_;
	ComboBoxClassWithCustoms* 	comboBox_skew_y_;
	ComboBoxClassWithCustoms* 	comboBox_transform_origin_;
	
	Wt::Signal<> styleChanged_;

	// bg custom regexp
	std::regex regex_custom_color =  std::regex("bg-\\[[\\S]*\\]");
	// bg-(inherit|current|transparent|black|white)
	std::regex regex_def_classes = std::regex("(bg|from|via|to)-(inherit|current|transparent|black|white)");
	// bg-((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)\/((100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)|\[[\S]*\])[ ]((from|via|to)-(0|5|10|15|20|25|30|35|40|45|50|55|60|65|70|75|80|85|90|95|100)%)?)
	std::regex regex_color_classes = std::regex("(bg|from|via|to)-((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)\\/((100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)|\\[[\\S]*\\]))");
};