#include "include/ElementBackground.h"
#include "include/ComboBoxClassChanger.h"
#include <iostream>
#include <regex>
#include <Wt/WApplication.h>

void ComboBoxClassChanger::setCustom(bool custom)
{
	if(custom_start_.compare("none") == 0) return;
	if(custom){
		checkBox_custom_value_->setChecked(true);
		comboBox_class->hide();
		lineEdit_custom_value_->show();
		// lineEdit_custom_value_->setFocus();
		checkBox_custom_value_->toggleStyleClass("[&>span]:text-green-700", true, true);
	}else {
		checkBox_custom_value_->setChecked(false);
		lineEdit_custom_value_->hide();
		comboBox_class->show();
		// comboBox_class->setFocus();
		checkBox_custom_value_->toggleStyleClass("[&>span]:text-green-700", false, true);
	}

}

void ComboBoxClassChanger::setCustomValueString(std::string custom_start)
{
	custom_start_ = custom_start;

	lineEdit_custom_value_->show();
	checkBox_custom_value_->show();

	lineEdit_custom_value_->enable();
	checkBox_custom_value_->enable();
	

	checkBox_custom_value_->clicked().connect(this, [=](){
		if(checkBox_custom_value_->isChecked()){
			setCustom(true);
		}else{
			setCustom(false);
		}
	});

	lineEdit_custom_value_->keyWentUp().connect(this, [=](Wt::WKeyEvent e){
		if(e.modifiers() == Wt::KeyboardModifier::Control)
		{
			if(e.key() == Wt::Key::Delete){
				// reset to default
				comboBox_class->setCurrentIndex(comboBox_class->findText(defaultValue, Wt::MatchFlag::StringExactly));
				checkbox_important_->setChecked(false);
				checkbox_important_->toggleStyleClass("text-red-500", false, true);
				classChanged_.emit(getValue());
				comboBox_class->setFocus();
			}else if (e.key() == Wt::Key::End){
				// toggle important
				if(checkbox_important_->isChecked()) {
					checkbox_important_->setChecked(false);
					checkbox_important_->toggleStyleClass("text-red-500", false, true);
				} else {
					checkbox_important_->setChecked(true);
					checkbox_important_->toggleStyleClass("text-red-500", true, true);
				}
			}else if (e.key() == Wt::Key::Home){
				// toggle custom value
				if(checkBox_custom_value_->isChecked()) {
					setCustom(false);
					comboBox_class->setFocus(true);
				} else {
					setCustom(true);
					lineEdit_custom_value_->setFocus(true);
				}
			}

		}
		 if (e.key() == Wt::Key::Escape){
			auto app = Wt::WApplication::instance();
			auto search_input = app->findWidget("search-input");
			if(search_input != nullptr) search_input->setFocus(true);
			else {
				app->findWidget("stylus")->setFocus(true);
			}
		}
	});

	lineEdit_custom_value_->enterPressed().connect(this, [=](){
		if(lineEdit_custom_value_->text().toUTF8() != ""){
			classChanged_.emit(getValue());
		}
		lineEdit_custom_value_->setFocus();
	});
}

ComboBoxClassChanger::ComboBoxClassChanger(Propriety propriety)
	: Wt::WContainerWidget()
{
	setStyleClass("flex justify-betwen items-center w-full text-sm py-0.5 rounded-sm");

	// setToolTip(Wt::WString().tr("tooltip-styleClasses").arg("first argument").arg("seccond argument"), Wt::TextFormat::UnsafeXHTML);
	
	checkbox_important_ = addWidget(std::make_unique<Wt::WCheckBox>("!"));
	comboBox_class = addWidget(std::make_unique<Wt::WComboBox>());
	lineEdit_custom_value_ = addWidget(std::make_unique<Wt::WLineEdit>());
	btn_reset_ = addWidget(std::make_unique<Wt::WText>("↺"));
	checkBox_custom_value_ = addWidget(std::make_unique<Wt::WCheckBox>("]"));

	btn_reset_->setThemeStyleEnabled(false);
	
	lineEdit_custom_value_->hide();
	lineEdit_custom_value_->disable();
	checkBox_custom_value_->hide();
	checkBox_custom_value_->disable();

	// set styles
	btn_reset_->setStyleClass("hover:bg-neutral-800 text-center p-0.5 cursor-pointer");
	comboBox_class->setStyleClass("px-1 w-full grow rounded-md h-full bg-neutral-800 text-center appearance-none hover:bg-neutral-900 min-w-[70px]");
	checkBox_custom_value_->setStyleClass("hover:bg-neutral-800 text-center p-0.5 [&>input]:hidden [&>span]:px-1 [&>span]:text [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0 [&>span]:hover:bg-neutral-95 rounded-md font-bold");
	
	checkbox_important_->setStyleClass("hover:bg-neutral-800 text-center p-0.5 [&>input]:hidden [&>span]:px-1 [&>span]:text [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0 [&>span]:hover:bg-neutral-950 rounded-md font-bold");
	lineEdit_custom_value_->setStyleClass("px-1 w-full grow rounded-md h-full bg-neutral-800 text-center appearance-none hover:bg-neutral-900 min-w-[70px]");
	

	for(auto& styleClass : propriety.styleClasses_){ comboBox_class->addItem(styleClass.className_); }
	
	btn_reset_->clicked().connect(this, [=](){
		setValue("none");
		// checkBox_custom_value_->setChecked(false);
		// setCustom(false);
		// comboBox_class->setCurrentIndex(comboBox_class->findText(defaultValue, Wt::MatchFlag::StringExactly));
		// checkbox_important_->setChecked(false);
		// checkbox_important_->toggleStyleClass("text-red-500", false, true);
		classChanged_.emit("none");
	});

	checkbox_important_->clicked().connect(this, [=](){
		if(checkbox_important_->isChecked()){
			checkbox_important_->toggleStyleClass("text-red-500", true, true);
		}else {
			checkbox_important_->toggleStyleClass("text-red-500", false, true);
		}
		if(getValue().compare(defaultValue) != 0) classChanged_.emit(getValue());
	});

	// emit signal when something changes
	classChanged_.connect(this, [=](std::string className){
		std::cout << "\n\n class changed: " << className << "\n\n";
		if(getValue().compare("none") == 0) 
			toggleStyleClass("bg-neutral-900", false);
			else 
			toggleStyleClass("bg-neutral-900", true);
	});

	comboBox_class->sactivated().connect(this, [=](Wt::WString className){
		classChanged_.emit(className.toUTF8());
		comboBox_class->setFocus(true);
	});

	comboBox_class->keyWentUp().connect(this, [=](Wt::WKeyEvent e){
		if(e.modifiers() == Wt::KeyboardModifier::Control)
		{
			if(e.key() == Wt::Key::Delete){
				// reset to default
				comboBox_class->setCurrentIndex(comboBox_class->findText(defaultValue, Wt::MatchFlag::StringExactly));
				checkbox_important_->setChecked(false);
				checkbox_important_->toggleStyleClass("text-red-500", false, true);
				classChanged_.emit(getValue());
				comboBox_class->setFocus();
			}else if (e.key() == Wt::Key::End){
				// toggle important
				if(checkbox_important_->isChecked()) {
					checkbox_important_->setChecked(false);
					checkbox_important_->toggleStyleClass("text-red-500", false, true);
				} else {
					checkbox_important_->setChecked(true);
					checkbox_important_->toggleStyleClass("text-red-500", true, true);
				}
			}else if (e.key() == Wt::Key::Home){
				// toggle custom value
				if(checkBox_custom_value_->isChecked()) {
					setCustom(false);
					comboBox_class->setFocus(true);
				} else {
					setCustom(true);
					lineEdit_custom_value_->setFocus(true);
				}
			}

		}
		 if (e.key() == Wt::Key::Escape){
			auto app = Wt::WApplication::instance();
			auto search_input = app->findWidget("search-input");
			if(search_input != nullptr) search_input->setFocus(true);
			else {
				app->findWidget("stylus")->setFocus(true);
			}
		}
	});

	setValue("none");
}

std::string ComboBoxClassChanger::getValue()
{
	std::string selectedClass = "";

		if(custom_start_.compare("none") != 0 &&
			checkBox_custom_value_->isChecked() && 
			lineEdit_custom_value_->text().toUTF8() != ""
		){
			selectedClass = custom_start_ + "[" + lineEdit_custom_value_->valueText().toUTF8() + "]";
		}else{
			selectedClass = comboBox_class->currentText().toUTF8();
		}	
		if(checkbox_important_->isChecked() && selectedClass.compare(defaultValue) != 0){
			selectedClass = "!" + selectedClass;
		}


return selectedClass;
}

void ComboBoxClassChanger::setValue(std::string className)
{
	if(className.compare("flex") == 0){
		std::cout << "\n\n flex value :" << className << "\n\n";
	}
	if(className.compare("") == 0 || className.compare("none") == 0)
	{
		comboBox_class->setCurrentIndex(comboBox_class->findText(defaultValue, Wt::MatchFlag::StringExactly));
		checkbox_important_->setChecked(false);
		checkbox_important_->toggleStyleClass("text-red-500", false, true);
		if(custom_start_.compare("none") != 0){
			setCustom(false);
		}
		toggleStyleClass("bg-neutral-900", false);
		return;
	}
	toggleStyleClass("bg-neutral-900", true);
	// check for ! at the start of the class
	if(className.find("!") != std::string::npos){
		// std::cout << "\n\n important value :" << className << "\n\n";
		checkbox_important_->setChecked(true);
		// comboBox_class->checkbox_important_->clicked().emit(Wt::WMouseEvent());
		className = className.substr(1, className.length()-1);
		checkbox_important_->toggleStyleClass("text-red-500", true);
	}


	if(className.find("]") != std::string::npos) {
		// std::cout << "\n\n custom value :" << className << "\n\n";
		checkBox_custom_value_->setChecked(true);
		checkBox_custom_value_->clicked().emit(Wt::WMouseEvent());
		// find the next '[' position in className
		int pos = className.find("[");
		if(pos != std::string::npos){
			// find the next ']' position in className
			int pos2 = className.find("]");
			if(pos2 != std::string::npos){
				// get the value between '[' and ']'
				std::string value = className.substr(pos+1, pos2-pos-1);
				lineEdit_custom_value_->setText(value);
			}
		}

	}else {
		std::cout << "\n\n className :" << className << "\n\n";
		checkBox_custom_value_->setChecked(false);
		checkBox_custom_value_->clicked().emit(Wt::WMouseEvent());
		comboBox_class->setCurrentIndex(comboBox_class->findText(className, Wt::MatchFlag::StringExactly));
		
	}
}
// void ComboBoxClassChanger::setValue(std::string className)
// {
// 	// if(className.compare("70") == 0)
// 	// 	{	
// 	// 		std::cout << "\n\n recived value : <" << className << ">\n\n";
// 	// 		std::cout << "\n\n index of value: <" << comboBox_class->findText(className, Wt::MatchFlag::StringExactly) << ">\n\n";
// 	// 		std::cout << "\n\n value of index: <" << comboBox_class->itemText(comboBox_class->findText(className, Wt::MatchFlag::StringExactly)) << ">\n\n";
// 	// 	}
// 	//  this is used by the search to reset styles to the default value 
// 	std::string reset = "res";
// 	if(className.compare("") == 0 || className.compare("none") == 0 || className.substr(className.length() - reset.length()) == reset)
// 	{
// 		comboBox_class->setCurrentIndex(comboBox_class->findText(defaultValue, Wt::MatchFlag::StringExactly));
// 		checkbox_important_->setChecked(false);
// 		checkbox_important_->toggleStyleClass("text-red-500", false, true);
// 		if(custom_start_.compare("none") != 0){
// 			setCustom(false);
// 		}
// 		toggleStyleClass("bg-neutral-900", false);
// 		return;
// 	}
// 	toggleStyleClass("bg-neutral-900", true);
// 	// check for ! at the start of the class
// 	if(className.find("!") != std::string::npos){
// 		// std::cout << "\n\n important value :" << className << "\n\n";
// 		checkbox_important_->setChecked(true);
// 		// comboBox_class->checkbox_important_->clicked().emit(Wt::WMouseEvent());
// 		className = className.substr(1, className.length()-1);
// 		checkbox_important_->toggleStyleClass("text-red-500", true);
// 	}


// 	if(className.find("]") != std::string::npos) {
// 		// std::cout << "\n\n custom value :" << className << "\n\n";
// 		checkBox_custom_value_->setChecked(true);
// 		checkBox_custom_value_->clicked().emit(Wt::WMouseEvent());
// 		// find the next '[' position in className
// 		int pos = className.find("[");
// 		if(pos != std::string::npos){
// 			// find the next ']' position in className
// 			int pos2 = className.find("]");
// 			if(pos2 != std::string::npos){
// 				// get the value between '[' and ']'
// 				std::string value = className.substr(pos+1, pos2-pos-1);
// 				lineEdit_custom_value_->setText(value);
// 			}
// 		}

// 	}else {
// 		// std::cout << "\n\n default value :" << className << "\n\n";
// 		checkBox_custom_value_->setChecked(false);
// 		checkBox_custom_value_->clicked().emit(Wt::WMouseEvent());
// 		comboBox_class->setCurrentIndex(comboBox_class->findText(className, Wt::MatchFlag::StringExactly));
		
// 	}
// }
void ComboBoxClassChanger::disable(bool disable)
{
	if(disable)
	{
		comboBox_class->disable();
		btn_reset_->disable();
		checkBox_custom_value_->disable();
		checkbox_important_->disable();
		lineEdit_custom_value_->disable();
	}else {
		comboBox_class->enable();
		btn_reset_->enable();
		checkBox_custom_value_->enable();
		checkbox_important_->enable();
		lineEdit_custom_value_->enable();
	}
}

