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
    ComboBoxClassWithCustoms();

	void setCustomValueString(Wt::WString custom_start){ custom_start_ = custom_start; };
    std::string getValue();
	// classType is default classes from tailwind p-1 or custom p-[10px]
	void setValue(std::string className = "none");
	void setComboBoxValues(std::vector<std::string> classNames);
	Wt::Signal<>& classChanged() { return classChanged_; }

	Wt::WTemplate *select_temp_;
	Wt::WTemplate *custom_temp_;

	Wt::WCheckBox *checkbox_custom_value_;
private:
    Wt::WComboBox *comboBox_class;
	Wt::WLineEdit *lineEdit_size_custom_;
	
	Wt::WPushButton *btn_reset_;

    Wt::WPushButton *btn_prev_;
    Wt::WPushButton *btn_next_;
	std::regex custom_option_regexp = std::regex("\\[\\S*\\]");
	Wt::WString custom_start_;
	Wt::Signal<> classChanged_;
};




class ComboBoxColors : public Wt::WTemplate
{
public:
	ComboBoxColors();
	void setCustomValueString(Wt::WString custom_start){ custom_start_ = custom_start; };

	std::string getValue();
	void setValue(std::string className = "none");
	void setComboBoxValues(std::vector<std::string> classNames);
	Wt::Signal<>& classChanged() { return classChanged_; }
private:
	ComboBoxClassWithCustoms *comboBox_class;
	Wt::WComboBox *comboBox_color;
	Wt::WComboBox *comboBox_intensity;
	Wt::WComboBox *comboBox_opacity;

	Wt::WLineEdit *lineEdit_color_custom_;
	// Wt::WPushButton *btn_prev_;
	// Wt::WPushButton *btn_next_;
	
	Wt::WString class_name_;

	Wt::WString custom_start_;
	Wt::Signal<> classChanged_;
};