#include "include/ElementBackground.h"
#include "include/ComboBoxes.h"
#include <iostream>
#include <regex>
#include <Wt/WApplication.h>

void StyleClassComboBox::setCustom(bool custom)
{
	if(custom_start_.compare("none") == 0) return;
	if(custom){
		checkBox_custom_value_->setChecked(true);
		comboBox_class->hide();
		lineEdit_custom_value_->show();
		lineEdit_custom_value_->setFocus();
		checkBox_custom_value_->toggleStyleClass("[&>span]:text-green-700", true, true);
	}else {
		checkBox_custom_value_->setChecked(false);
		lineEdit_custom_value_->hide();
		comboBox_class->show();
		comboBox_class->setFocus();
		checkBox_custom_value_->toggleStyleClass("[&>span]:text-green-700", false, true);
	}

}

void StyleClassComboBox::setCustomValueString(std::string custom_start)
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
	lineEdit_custom_value_->enterPressed().connect(this, [=](){
		if(lineEdit_custom_value_->text().toUTF8() == ""){
			checkBox_custom_value_->setChecked(false);
			setCustom(false);
			classChanged_.emit();
		}
	});

	lineEdit_custom_value_->keyWentDown().connect(this, [=](Wt::WKeyEvent e){
		if(e.modifiers() == Wt::KeyboardModifier::Shift && e.key() == Wt::Key::Q){
			if(checkbox_important_->isChecked()) {
				checkbox_important_->setChecked(false);
				checkbox_important_->toggleStyleClass("text-red-500", false, true);
			} else {
				checkbox_important_->setChecked(true);
				checkbox_important_->toggleStyleClass("text-red-500", true, true);
			}
			classChanged_.emit();
			lineEdit_custom_value_->setFocus();
		}else if(e.modifiers() == Wt::KeyboardModifier::Shift && e.key() == Wt::Key::W){
			if(checkBox_custom_value_->isChecked()) {
				setCustom(false);
			} else {
				setCustom(true);
			}
		}else if (e.key() == Wt::Key::Escape){
			auto app = Wt::WApplication::instance();
			auto search_input = app->findWidget("search-input");
			if(search_input != nullptr) search_input->setFocus(true);
			else {
				app->findWidget("stylus")->setFocus(true);
			}
		}
	});
}

StyleClassComboBox::StyleClassComboBox(Propriety propriety)
	: Wt::WContainerWidget()
{
	setStyleClass("flex justify-betwen items-center w-full text-sm py-0.5 rounded-sm");
	
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
	

	// setOptions(propriety);

	for(auto& styleClass : propriety.styleClasses_){
		comboBox_class->addItem(styleClass.className_);
	}
	
	btn_reset_->clicked().connect(this, [=](){
		checkBox_custom_value_->setChecked(false);
		setCustom(false);
		comboBox_class->setCurrentIndex(comboBox_class->findText(defaultValue, Wt::MatchFlag::StringExactly));
		checkbox_important_->setChecked(false);
		checkbox_important_->toggleStyleClass("text-red-500", false, true);
		classChanged_.emit();
	});


	checkbox_important_->clicked().connect(this, [=](){
		if(checkbox_important_->isChecked()){
			checkbox_important_->toggleStyleClass("text-red-500", true, true);
		}else {
			checkbox_important_->toggleStyleClass("text-red-500", false, true);
		}
		if(getValue().compare(defaultValue) != 0) classChanged_.emit();
	});


	// emit signal when something changes
	comboBox_class->sactivated().connect(this, [=](Wt::WString className){
		// comboBox_class->setFocus();
		classChanged_.emit();
	});


	classChanged_.connect(this, [=](){
		if(getValue().compare("none") == 0) 
			toggleStyleClass("bg-neutral-900", false);
			else 
			toggleStyleClass("bg-neutral-900", true);
	});

	comboBox_class->keyWentDown().connect(this, [=](Wt::WKeyEvent e){
		if(e.modifiers() == Wt::KeyboardModifier::Shift && e.key() == Wt::Key::Q){
			if(comboBox_class->currentText() == "none") return;
			if(checkbox_important_->isChecked()) {
				checkbox_important_->setChecked(false);
				checkbox_important_->toggleStyleClass("text-red-500", false, true);
			} else {
				checkbox_important_->setChecked(true);
				checkbox_important_->toggleStyleClass("text-red-500", true, true);
			}
			classChanged_.emit();
			comboBox_class->setFocus();
		}else if(e.modifiers() == Wt::KeyboardModifier::Shift && e.key() == Wt::Key::W){
			if(custom_start_.compare("none") == 0) return;
			if(checkBox_custom_value_->isChecked()) {
				setCustom(false);
			} else {
				setCustom(true);
			}
		}else if (e.key() == Wt::Key::Left || e.key() == Wt::Key::Up){
			comboBox_class->setCurrentIndex(comboBox_class->currentIndex() - 1);
			classChanged_.emit();
			comboBox_class->setFocus();
		}else if (e.key() == Wt::Key::Right || e.key() == Wt::Key::Down){
			comboBox_class->setCurrentIndex(comboBox_class->currentIndex() + 1);
			classChanged_.emit();
			comboBox_class->setFocus();
		}else if (e.key() == Wt::Key::Escape){
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

std::string StyleClassComboBox::getValue()
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

void StyleClassComboBox::setValue(std::string className)
{
	//  this is used by the search to reset styles to the default value 
	std::string reset = "res";
	if(className.compare("") == 0 || className.compare("none") == 0 || className.substr(className.length() - reset.length()) == reset)
	{
		comboBox_class->setCurrentIndex(comboBox_class->findText(defaultValue, Wt::MatchFlag::StringExactly));
		checkbox_important_->setChecked(false);
		checkbox_important_->toggleStyleClass("text-red-500", false, true);
		if(custom_start_.compare("none") != 0){
			// checkBox_custom_value_->setChecked(false);
			setCustom(false);
		}
		toggleStyleClass("bg-neutral-900", false);
		return;
	}
	toggleStyleClass("bg-neutral-900", true);
	// check for ! at the start of the class
	if(className.find("!") != std::string::npos){
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
		std::cout << "\n\n default value : <" << className << ">\n\n";
		std::cout << "\n\n index of value: <" << comboBox_class->findText(className, Wt::MatchFlag::StringExactly) << ">\n\n";
		std::cout << "\n\n value of index: <" << comboBox_class->itemText(comboBox_class->findText(className, Wt::MatchFlag::StringExactly)) << ">\n\n";
		checkBox_custom_value_->setChecked(false);
		checkBox_custom_value_->clicked().emit(Wt::WMouseEvent());
		comboBox_class->setCurrentIndex(comboBox_class->findText(className, Wt::MatchFlag::StringExactly));
	}
}

void StyleClassComboBox::disable(bool disable)
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


ColorsComboBox::ColorsComboBox(ProprietyColor proprietyColor)
	: Wt::WContainerWidget()
{
	setStyleClass("flex flex-col");
	
	auto title_color_wrapper = addWidget(std::make_unique<Wt::WContainerWidget>());
	auto intensity_opacity_wrapper = addWidget(std::make_unique<Wt::WContainerWidget>());


	title = title_color_wrapper->addWidget(std::make_unique<Wt::WText>("Title"));
	comboBox_color = title_color_wrapper->addWidget(std::make_unique<StyleClassComboBox>(proprietyColor));
	comboBox_intensity = intensity_opacity_wrapper->addWidget(std::make_unique<StyleClassComboBox>(proprietyColor.intensity_));
	comboBox_opacity = intensity_opacity_wrapper->addWidget(std::make_unique<StyleClassComboBox>(proprietyColor.opacity_));

	// comboBox_opacity->lineEdit_custom_value_->setPlaceholderText("%");
	title_color_wrapper->setStyleClass("flex justify-start items-center");
	intensity_opacity_wrapper->setStyleClass("flex justify-start");

	title->setStyleClass("font-bold text-neutral-400 text-sm whitespace-nowrap");

	// comboBox_intensity->comboBox_class->addStyleClass("!w-[30px]");
	// comboBox_opacity->comboBox_class->addStyleClass("!w-[30px]");
	// comboBox_gradient_step->comboBox_class->addStyleClass("!w-[120px]");

	comboBox_opacity->setDefaultValue("100");
	comboBox_intensity->setDefaultValue("500");


	comboBox_intensity->disable(true);
	comboBox_opacity->disable(false);


	comboBox_intensity->setValue();
	comboBox_opacity->setValue();

	comboBox_color->classChanged().connect(this, [=](){ 
		auto color = comboBox_color->getValue();
		if(std::regex_match(color, regex_def_classes) ||
			color.compare("none") == 0)
			{
			comboBox_intensity->disable(true);
			comboBox_opacity->disable(true);
		}else {
			comboBox_intensity->disable(false);
			comboBox_opacity->disable(false);
		}
		classChanged_.emit();
	});

	comboBox_color->checkBox_custom_value_->changed().connect(this, [=](){
		if(comboBox_color->checkBox_custom_value_->isChecked()){
			comboBox_intensity->setHidden(true);
			comboBox_opacity->setHidden(true);
		}else {
			comboBox_intensity->setHidden(false);
			comboBox_opacity->setHidden(false);
		}
		classChanged_.emit();
	});

	comboBox_color->btn_reset_->clicked().connect(this, [=](){
		comboBox_color->setValue("none");
		comboBox_intensity->setValue("none");
		comboBox_opacity->setValue("none");
		classChanged_.emit();
	});

	comboBox_intensity->classChanged().connect(this, [=](){ classChanged_.emit(); });
	comboBox_opacity->classChanged().connect(this, [=](){ classChanged_.emit(); });

}

void ColorsComboBox::setValue(std::string className)
{
	// std::cout << "\n combobox colors set value: " << className << "\n";
	comboBox_color->setValue("none");
	comboBox_intensity->setValue("500");
	comboBox_opacity->setValue("100");
	if(std::regex_match(className, regex_custom_color)){
		std::cout << "set custom value";
		comboBox_color->setValue(className);
	}else if(std::regex_match(className, regex_def_classes) || className.compare("none") == 0 || className.compare("") == 0){
		// std::cout << "should deactivate <" << className << ">\n";
		comboBox_intensity->disable(true);
		comboBox_opacity->disable(true);
		comboBox_color->setValue(className);
		// std::cout << "default value: \n";
	} else {
		// std::cout << "should activate <" << className << ">\n";
		comboBox_intensity->disable(false);
		comboBox_opacity->disable(false);
		auto pos = className.find("-");
		auto nextPos = className.find("-", pos+1);
		auto colorClass = className.substr(0, nextPos);
		auto intensityClass = className.substr(nextPos+1, className.find("/", nextPos+1)-nextPos-1);				
		auto opacityClass = className.substr(className.find("/")+1, className.length()-className.find("/")-1);
		std::cout << "colorClass: <" << colorClass << ">\n";
		std::cout << "intensityClass: <" << intensityClass << ">\n";
		std::cout << "opacityClass: <" << opacityClass << ">\n";
		comboBox_color->setValue(colorClass);
		comboBox_intensity->setValue(intensityClass);
		// comboBox_opacity->setValue(opacityClass);
		// std::cout << "set opacity index : <" << comboBox_opacity->comboBox_class->findText(opacityClass, Wt::MatchFlag::StringExactly) << ">\n";
		// comboBox_opacity->setValue(opacityClass);
	}


	
}


std::string ColorsComboBox::getValue()
{
	std::string selectedClass = comboBox_color->getValue();
	
	if(std::regex_match(selectedClass, regex_def_classes) || selectedClass.compare("none") == 0)
		{
		return selectedClass;
	} else
	{
		selectedClass = comboBox_color->getValue() + "-" + comboBox_intensity->getValue() + "/" + comboBox_opacity->getValue();
	}
	return selectedClass;
}
