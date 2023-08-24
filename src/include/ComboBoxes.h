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

#include <Wt/WGroupBox.h>
#include <Wt/WButtonGroup.h>
#include <Wt/WRadioButton.h>
#include <Wt/WSlider.h>

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

	// std::regex custom_option_regexp = std::regex("\\[\\S*\\]");
	std::string custom_start_ = "none";
	Wt::Signal<> classChanged_;
};




class ColorSelecionWidget : public Wt::WContainerWidget
{
public:
	ColorSelecionWidget(ProprietyColor proprietyColor, std::string title = "title not set");
	void setCustomValueString(std::string custom_start){ custom_start_ = custom_start; };

	std::string getValue();
	void setValue(std::string className = "none");

	std::string custom_start_;

	std::shared_ptr<Wt::WButtonGroup> colors_group;
	Wt::WSlider *opacity_slider;
	std::vector<std::string> colors_vector = {};
	int getIndexOfStringInVector(std::string str, std::vector<std::string> vec);

	Wt::Signal<>& classChanged() { return classChanged_; }
private:

	Wt::Signal<> classChanged_;

	std::regex regex_custom_color =  std::regex("[!]?bg-\\[[\\S]*\\]");
	std::regex regex_def_classes = std::regex("[!]?(bg|from|via|to)-(inherit|current|transparent|black|white)");

};
