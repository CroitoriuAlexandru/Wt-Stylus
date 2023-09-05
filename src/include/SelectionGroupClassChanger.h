#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WCheckBox.h>
#include <Wt/WSpinBox.h>
#include <Wt/WSignal.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WAnchor.h>
#include <Wt/WRadioButton.h>

#include <vector>
#include <string>
#include <regex>

#include <Wt/WString.h>
#include <Wt/WLineEdit.h>
#include "../../TailwindConfig/src/include/Config.h"



class SelectionGroupClassChanger : public Wt::WContainerWidget
{
public:
	SelectionGroupClassChanger(Propriety propriety, std::string title, std::string classRepeatName = "");

    std::string getValue();
	void setValue(std::string className = "none");

	void disable(bool disable);

	std::shared_ptr<Wt::WButtonGroup> group_;
	Wt::WCheckBox *checkbox_important_;
	Wt::WText *btn_reset_;

	Wt::WContainerWidget *titleBar;
	Wt::WContainerWidget *content;
    Wt::WContainerWidget *btns_container;

	Wt::Signal<std::string>& classChanged() { return classChanged_; }
    int getIndesOfStringInVector(std::string str, std::vector<StyleClass> vec);
	Wt::WAnchor* title_;
private:
	Propriety propriety_;
	std::string defaultValue = "none";

	Wt::Signal<std::string> classChanged_;
};




