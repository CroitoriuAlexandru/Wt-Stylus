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

#include <Wt/WRadioButton.h>

#include <Wt/WString.h>
#include <Wt/WLineEdit.h>
#include "../../TailwindConfig/src/include/Config.h"


// this widget is used for margin, padding
class ComboBoxClassChanger : public Wt::WContainerWidget
{
public:
    ComboBoxClassChanger(Propriety propriety);

	void setCustomValueString(std::string custom_start);
    std::string getValue();
	void setValue(std::string className = "none");
	Wt::Signal<std::string>& classChanged() { return classChanged_; }
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

	std::string custom_start_ = "none";
	Wt::Signal<std::string> classChanged_;
};

