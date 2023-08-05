#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WCheckBox.h>
#include <Wt/WSpinBox.h>
#include <Wt/WSignal.h>
#include <vector>
#include <string>
#include <regex>

#include <Wt/WString.h>
#include <Wt/WLineEdit.h>


// this widget is used for margin, padding
class ComboBoxClassWithCustoms : public Wt::WTemplate
{
public:
    ComboBoxClassWithCustoms(std::vector<std::string> classNames);

	void setCustomValueString(Wt::WString custom_start){ custom_start_ = custom_start; };
    std::string getValue();
	// classType is default classes from tailwind p-1 or custom p-[10px]
	void setValue(std::string className = "none");
	Wt::Signal<>& classChanged() { return classChanged_; }
	void setOptions(std::vector<std::string> classNames);
	Wt::WTemplate *select_temp_;
	void setCustom(bool custom);
	void disable(bool disable);
	Wt::WCheckBox *checkbox_custom_value_;
    Wt::WComboBox *comboBox_class;
	Wt::WCheckBox *checkbox_important_;
	Wt::WLineEdit *lineEdit_size_custom_;
	Wt::WText *btn_reset_;

	void setDefaultValue(std::string defaultValue) { this->defaultValue = defaultValue; };
private:
	std::string defaultValue = "none";

    Wt::WText *btn_prev_;
    Wt::WText *btn_next_;
	std::regex custom_option_regexp = std::regex("\\[\\S*\\]");
	Wt::WString custom_start_;
	Wt::Signal<> classChanged_;
};




class ComboBoxColors : public Wt::WTemplate
{
public:
	ComboBoxColors(std::vector<std::string> classNames, std::vector<std::string> colorIntensity, std::vector<std::string> colorOpacity);
	void setCustomValueString(std::string custom_start){ custom_start_ = custom_start; };

	std::string getValue();
	void setValue(std::string className = "none");
	void setStepOptions(std::vector<std::string> classNames);
	// void setCustom(bool custom);
	Wt::Signal<>& classChanged() { return classChanged_; }

	std::string custom_start_;

	ComboBoxClassWithCustoms *comboBox_color;
	ComboBoxClassWithCustoms* comboBox_intensity;
	ComboBoxClassWithCustoms* comboBox_opacity;
	ComboBoxClassWithCustoms* comboBox_gradient_step;

private:
	std::string defaultValue = "none";

	// Wt::WLineEdit *lineEdit_color_custom_;


	Wt::Signal<> classChanged_;

	std::regex regex_custom_color =  std::regex("[!]?bg-\\[[\\S]*\\]");
	// bg-(inherit|current|transparent|black|white)
	std::regex regex_def_classes = std::regex("[!]?(bg|from|via|to)-(inherit|current|transparent|black|white)");
	// bg-((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)?\/(100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0))
	std::regex regex_color_classes = std::regex("[!]?bg-((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)?\\/(100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0))");


};