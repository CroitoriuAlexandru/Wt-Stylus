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



class SelectionGroupClassChanger : public Wt::WContainerWidget
{
public:
	SelectionGroupClassChanger(Propriety propriety, std::string title, std::string classRepeatName = "");

	void setCustomValueString(std::string custom_start);
    std::string getValue();
	void setValue(std::string className = "none");

	void setCustom(bool custom);
	void disable(bool disable);

	std::shared_ptr<Wt::WButtonGroup> group_;
	Wt::WCheckBox *checkbox_important_;
	Wt::WLineEdit *lineEdit_custom_value_;
	Wt::WCheckBox *checkBox_custom_value_;
	Wt::WText *btn_reset_;

	Wt::WContainerWidget *titleBar;
	Wt::WContainerWidget *content;
    Wt::WContainerWidget *btns_container;

	Wt::Signal<std::string>& classChanged() { return classChanged_; }
    int getIndesOfStringInVector(std::string str, std::vector<StyleClass> vec);
private:
	Propriety propriety_;
	std::string defaultValue = "none";

	std::string custom_start_ = "none";
	Wt::Signal<std::string> classChanged_;
};




