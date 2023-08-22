#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WCheckBox.h>
#include <Wt/WSpinBox.h>
#include <Wt/WSignal.h>
#include <Wt/WContainerWidget.h>
#include <vector>
#include <string>
#include <regex>

#include <Wt/WString.h>
#include <Wt/WLineEdit.h>
#include "../../TailwindConfig/src/include/Config.h"


// this widget is used for margin, padding
class StyleClassComboBox : public Wt::WContainerWidget
{
public:
    StyleClassComboBox(Propriety propriety);

	void setCustomValueString(std::string custom_start);
    std::string getValue();
	// classType is default classes from tailwind p-1 or custom p-[10px]
	void setValue(std::string className = "none");
	Wt::Signal<>& classChanged() { return classChanged_; }
	// void setOptions(Propriety propriety);
	Wt::WTemplate *select_temp_;
	void setCustom(bool custom);
	void disable(bool disable);

	Wt::WCheckBox *checkbox_important_;
    Wt::WComboBox *comboBox_class;
	Wt::WLineEdit *lineEdit_custom_value_;
	Wt::WCheckBox *checkBox_custom_value_;
	Wt::WText *btn_reset_;

	void setDefaultValue(std::string defaultValue) { this->defaultValue = defaultValue; };
private:
	std::string defaultValue = "none";

	std::regex custom_option_regexp = std::regex("\\[\\S*\\]");
	std::string custom_start_ = "none";
	Wt::Signal<> classChanged_;
};




class ColorsComboBox : public Wt::WContainerWidget
{
public:
	ColorsComboBox(ProprietyColor proprietyColor);
	void setCustomValueString(std::string custom_start){ custom_start_ = custom_start; };

	std::string getValue();
	void setValue(std::string className = "none");
	Wt::Signal<>& classChanged() { return classChanged_; }

	std::string custom_start_;
	Wt::WText *title;

	StyleClassComboBox *comboBox_color;
	StyleClassComboBox* comboBox_intensity;
	StyleClassComboBox* comboBox_opacity;
protected:


	Wt::Signal<> classChanged_;

	std::regex regex_custom_color =  std::regex("[!]?bg-\\[[\\S]*\\]");
	// bg-(inherit|current|transparent|black|white)
	std::regex regex_def_classes = std::regex("[!]?(bg|from|via|to)-(inherit|current|transparent|black|white)");
	// bg-((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)?\/(100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0))
	std::regex regex_color_classes = std::regex("[!]?bg-((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)?\\/(100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0))");

private:
	std::string defaultValue = "none";

};
