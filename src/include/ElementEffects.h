#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxes.h"
#include <Wt/WDialog.h>
#include <Wt/WPanel.h>

struct EffectsData
{
	std::string boxShadow = "none";
	bool boxShadowInner = false;
	std::string boxShadowColor = "none";
	std::string opacity = "none";
	std::string mixBlendMode = "none";
	std::string backgroundBlendMode = "none";
};


class ElementEffectsWidget : public Wt::WPanel
{
public:
	ElementEffectsWidget(std::shared_ptr<Config> tailwindConfig);
	// margin and padding at the moment


	void setClasses(EffectsData effectsData);
    Wt::Signal<>& styleChanged() { return styleChanged_; };
	std::string getStyles();
	void resetStyles();
private:
	void setCustomTestValues();
	
	Wt::WTemplate* content_temp;
	std::shared_ptr<Config> tailwindConfig_;
	
	StyleClassComboBox*	comboBox_box_shadow;
	Wt::WCheckBox* 				checkBox_box_shadow_inner;
	// ColorsComboBox*				box_shadow_color;
	StyleClassComboBox*	comboBox_opacity;
	StyleClassComboBox*	comboBox_mix_blend_mode;
	StyleClassComboBox*	comboBox_bg_blend_mode;

	Wt::Signal<> styleChanged_;

	// bg custom regexp
	std::regex regex_custom_color =  std::regex("bg-\\[[\\S]*\\]");
	// bg-(inherit|current|transparent|black|white)
	std::regex regex_def_classes = std::regex("(bg|from|via|to)-(inherit|current|transparent|black|white)");
	// bg-((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)\/((100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)|\[[\S]*\])[ ]((from|via|to)-(0|5|10|15|20|25|30|35|40|45|50|55|60|65|70|75|80|85|90|95|100)%)?)
	std::regex regex_color_classes = std::regex("(bg|from|via|to)-((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)\\/((100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)|\\[[\\S]*\\]))");
};