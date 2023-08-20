#include "include/ElementBackground.h"
#include "include/ComboBoxes.h"
#include <iostream>
#include <regex>
#include <Wt/WApplication.h>

void StyleClassComboBox::setCustom(bool custom)
{
	if(custom){
		checkbox_custom_value_->setChecked(true);
		comboBox_class->hide();
		lineEdit_size_custom_->show();
		lineEdit_size_custom_->setFocus();
		checkbox_custom_value_->toggleStyleClass("[&>span]:text-green-700", true, true);
	}else {
		checkbox_custom_value_->setChecked(false);
		lineEdit_size_custom_->hide();
		comboBox_class->show();
		comboBox_class->setFocus();
		checkbox_custom_value_->toggleStyleClass("[&>span]:text-green-700", false, true);
	}
}

StyleClassComboBox::StyleClassComboBox(Propriety propriety)
	: Wt::WContainerWidget()
{
	setStyleClass("flex justify-betwen items-center w-full text-sm py-0.5 rounded-sm");
	
	checkbox_important_ = addWidget(std::make_unique<Wt::WCheckBox>("!"));
	comboBox_class = addWidget(std::make_unique<Wt::WComboBox>());
	lineEdit_size_custom_ = addWidget(std::make_unique<Wt::WLineEdit>());
	btn_reset_ = addWidget(std::make_unique<Wt::WText>("↺"));
	checkbox_custom_value_ = addWidget(std::make_unique<Wt::WCheckBox>("]"));

	btn_reset_->setThemeStyleEnabled(false);
	
	// set styles
	btn_reset_->setStyleClass("hover:bg-neutral-800 text-center p-0.5 cursor-pointer");
	checkbox_important_->setStyleClass("hover:bg-neutral-800 text-center p-0.5 [&>input]:hidden [&>span]:px-1 [&>span]:text [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0 [&>span]:hover:bg-neutral-950 rounded-md font-bold");
	checkbox_custom_value_->setStyleClass("hover:bg-neutral-800 text-center p-0.5 [&>input]:hidden [&>span]:px-1 [&>span]:text [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0 [&>span]:hover:bg-neutral-95 rounded-md font-bold");
	comboBox_class->setStyleClass("px-1 w-full grow rounded-md h-full bg-neutral-800 text-center appearance-none hover:bg-neutral-900 min-w-[70px]");
	lineEdit_size_custom_->setStyleClass("px-1 w-full grow rounded-md h-full bg-neutral-800 text-center appearance-none hover:bg-neutral-900 min-w-[70px]");
	setOptions(propriety);

	btn_reset_->clicked().connect(this, [=](){
		checkbox_custom_value_->setChecked(false);
		setCustom(false);
		comboBox_class->setCurrentIndex(comboBox_class->findText(defaultValue, Wt::MatchFlag::StringExactly));
		checkbox_important_->setChecked(false);
		checkbox_important_->toggleStyleClass("text-red-500", false, true);
		classChanged_.emit();
	});

	checkbox_custom_value_->clicked().connect(this, [=](){
		if(checkbox_custom_value_->isChecked()){
			setCustom(true);
		}else{
			setCustom(false);
		}
	});
	checkbox_important_->clicked().connect(this, [=](){
		if(checkbox_important_->isChecked()){
			checkbox_important_->toggleStyleClass("text-red-500", true, true);
		}else {
			checkbox_important_->toggleStyleClass("text-red-500", false, true);
		}
		if(getValue().compare(defaultValue) != 0) classChanged_.emit();
	});


	lineEdit_size_custom_->enterPressed().connect(this, [=](){
		// std::cout << "\n\n enter pressed \n\n";
		if(lineEdit_size_custom_->text().toUTF8() == ""){
			checkbox_custom_value_->setChecked(false);
			setCustom(false);
			classChanged_.emit();
		}
	});

	// emit signal when something changes
	comboBox_class->sactivated().connect(this, [=](Wt::WString className){
		classChanged_.emit();
		comboBox_class->setFocus();
	});

	// create keybord shortcuts when combobox is focused
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
			if(checkbox_custom_value_->isHidden()) return;
			if(checkbox_custom_value_->isChecked()) {
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
		}
	});

		lineEdit_size_custom_->keyWentDown().connect(this, [=](Wt::WKeyEvent e){
			if(e.modifiers() == Wt::KeyboardModifier::Shift && e.key() == Wt::Key::Q){
				if(checkbox_important_->isChecked()) {
					checkbox_important_->setChecked(false);
					checkbox_important_->toggleStyleClass("text-red-500", false, true);
				} else {
					checkbox_important_->setChecked(true);
					checkbox_important_->toggleStyleClass("text-red-500", true, true);
				}
				classChanged_.emit();
				lineEdit_size_custom_->setFocus();
			}else if(e.modifiers() == Wt::KeyboardModifier::Shift && e.key() == Wt::Key::W){
				if(checkbox_custom_value_->isChecked()) {
					setCustom(false);
				} else {
					setCustom(true);
				}
			}
		});

}

void StyleClassComboBox::setOptions(Propriety propriety)
{
	comboBox_class->clear();
	for(auto& styleClass : propriety.styleClasses_){
		comboBox_class->addItem(styleClass.className_);

	}

	setValue(defaultValue);
	setCustom(false);

	classChanged_.connect(this, [=](){
		if(getValue().compare("none") == 0) 
			toggleStyleClass("bg-neutral-900", false);
			else 
			toggleStyleClass("bg-neutral-900", true);
	});
}

std::string StyleClassComboBox::getValue()
{
	std::string selectedClass = "";

	if(checkbox_custom_value_->isChecked() && lineEdit_size_custom_->text().toUTF8() != ""){
		selectedClass = custom_start_.toUTF8() + "[" + lineEdit_size_custom_->valueText().toUTF8() + "]";
	}else{
		selectedClass = comboBox_class->currentText().toUTF8();
	}	
	if(checkbox_important_->isChecked() && selectedClass.compare(defaultValue) != 0){
		selectedClass = "!" + selectedClass;
	}
	// std::cout << "\n selectedClass: " << selectedClass << "\n";
return selectedClass;
}

void StyleClassComboBox::setValue(std::string className)
{
	if(className.compare("") == 0 || className.compare("none") == 0)
	{
		comboBox_class->setCurrentIndex(comboBox_class->findText(defaultValue, Wt::MatchFlag::StringExactly));
		checkbox_important_->setChecked(false);
		checkbox_important_->toggleStyleClass("text-red-500", false, true);
		checkbox_custom_value_->setChecked(false);
		setCustom(false);
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
		// std::cout << "\n\n important value :" << className << "\n\n";
	}


	if(className.find("]") != std::string::npos) {
		// std::cout << "\n\n custom value :" << className << "\n\n";
		checkbox_custom_value_->setChecked(true);
		checkbox_custom_value_->clicked().emit(Wt::WMouseEvent());
		// find the next '[' position in className
		int pos = className.find("[");
		if(pos != std::string::npos){
			// find the next ']' position in className
			int pos2 = className.find("]");
			if(pos2 != std::string::npos){
				// get the value between '[' and ']'
				std::string value = className.substr(pos+1, pos2-pos-1);
				lineEdit_size_custom_->setText(value);
			}
		}

	}else {
		// std::cout << "\n\n default value :" << className << "\n\n";
		checkbox_custom_value_->setChecked(false);
		checkbox_custom_value_->clicked().emit(Wt::WMouseEvent());
		comboBox_class->setCurrentIndex(comboBox_class->findText(className, Wt::MatchFlag::StringExactly));
	}
}

void StyleClassComboBox::disable(bool disable)
{
	if(disable)
	{
		comboBox_class->disable();
		// btn_prev_->disable();
		// btn_next_->disable();
		btn_reset_->disable();
		checkbox_custom_value_->disable();
		checkbox_important_->disable();
		lineEdit_size_custom_->disable();
	}else {
		comboBox_class->enable();
		// btn_prev_->enable();
		// btn_next_->enable();
		btn_reset_->enable();
		checkbox_custom_value_->enable();
		checkbox_important_->enable();
		lineEdit_size_custom_->enable();
	}
}


ComboBoxColors::ComboBoxColors(ProprietyColor proprietyColor)
	: Wt::WContainerWidget()
{
	setStyleClass("relative ms-auto flex justify-start");
	// setCondition("other-widgets", true);
	comboBox_color = addWidget(std::make_unique<StyleClassComboBox>(proprietyColor));
	comboBox_intensity = addWidget(std::make_unique<StyleClassComboBox>(proprietyColor.intensity_));
	comboBox_opacity = addWidget(std::make_unique<StyleClassComboBox>(proprietyColor.opacity_));

	comboBox_opacity->lineEdit_size_custom_->setPlaceholderText("%");
	comboBox_opacity->lineEdit_size_custom_->addStyleClass("!w-[50px]");

	// reset styles --- flex justify-betwen items-center w-full text-xs relative px-3 me-2
	comboBox_intensity->removeStyleClass("pr-8");
	comboBox_intensity->removeStyleClass("pl-3");
	comboBox_opacity->removeStyleClass("pr-8");
	comboBox_opacity->removeStyleClass("pl-3");
	// comboBox_opacity->addStyleClass("pr-3");
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

	comboBox_color->checkbox_custom_value_->changed().connect(this, [=](){
		if(comboBox_color->checkbox_custom_value_->isChecked()){
			comboBox_intensity->setHidden(true);
			comboBox_opacity->setHidden(true);
		}else {
			comboBox_intensity->setHidden(false);
			comboBox_opacity->setHidden(false);
		}
		classChanged_.emit();
	});

	comboBox_color->btn_reset_->clicked().connect(this, [=](){
		comboBox_color->setValue();
		comboBox_intensity->setValue();
		comboBox_opacity->setValue();
		classChanged_.emit();
	});

	comboBox_intensity->classChanged().connect(this, [=](){ classChanged_.emit(); });
	comboBox_opacity->classChanged().connect(this, [=](){ classChanged_.emit(); });

	comboBox_intensity->setValue();
	comboBox_opacity->setValue();
	// // set styles
	// std::string comboBox_styles = "apearance-none bg-neutral-800 hover:bg-neutral-900 p-px w-full rounded-none m-0 h-full w-full text-center focus-visible:outline-none";
	// comboBox_intensity->setStyleClass(comboBox_styles);
	// comboBox_opacity->setStyleClass(comboBox_styles);

	// // comboBox signals
	// option_container_->toggleStyleClass("hidden", true, true);
	// classChanged().connect(this, [=](){ 
	// 	auto selectedClass = getValue();
	// 	if(std::regex_match(selectedClass, regex_def_classes) || selectedClass.compare(defaultValue) == 0){
	// 		option_container_->toggleStyleClass("hidden", true, true);
	// 	}else {
	// 		option_container_->toggleStyleClass("hidden", false, true);
	// 	}
	// 	classChanged().emit();
	// });
	
	// comboBox_intensity->activated().connect(this, [=](){ classChanged().emit(); });
	// comboBox_opacity->activated().connect(this, [=](){ classChanged().emit(); });

}

void ComboBoxColors::setValue(std::string className)
{
	// std::cout << "\n combobox colors set value: " << className << "\n";
	comboBox_color->setValue("none");
	comboBox_intensity->setValue("500");
	comboBox_opacity->setValue("100");
	if(std::regex_match(className, regex_custom_color)){
		// std::cout << "set custom value";
		comboBox_color->setValue(className);
	}else if(std::regex_match(className, regex_def_classes) || className.compare("none") == 0 || className.compare("") == 0){
		// std::cout << "should deactivate <" << className << ">\n";
		comboBox_intensity->disable(true);
		comboBox_opacity->disable(true);
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
		// std::cout << "colorClass: " << colorClass << "\n";
		// std::cout << "intensityClass: " << intensityClass << "\n";
		// std::cout << "opacityClass: " << opacityClass << "\n";
		comboBox_color->setValue(colorClass);
		comboBox_intensity->setValue(intensityClass);
		comboBox_opacity->setValue(opacityClass);
	}


	
}


std::string ComboBoxColors::getValue()
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



BackgroundColorWidget::BackgroundColorWidget(ProprietyColor proprietyColor, Propriety gradientStep)
	: ComboBoxColors(proprietyColor) 
{
	comboBox_gradient_step = addWidget(std::make_unique<StyleClassComboBox>(proprietyColor));
	comboBox_gradient_step->lineEdit_size_custom_->setPlaceholderText("%");
	// comboBox_gradient_step->setCondition("important-checkbox", false);

	comboBox_gradient_step->removeStyleClass("pl-3");
	comboBox_gradient_step->setHidden(true);


	comboBox_color->classChanged().connect(this, [=](){ 
		auto color = comboBox_color->getValue();
		if(std::regex_match(color, regex_def_classes) ||
			color.compare("none") == 0)
			{
			comboBox_intensity->disable(true);
			comboBox_opacity->disable(true);
			comboBox_gradient_step->disable(true);
		}else {
			comboBox_intensity->disable(false);
			comboBox_opacity->disable(false);
			comboBox_gradient_step->disable(false);
		}
		classChanged_.emit();
	});

	
	comboBox_gradient_step->classChanged().connect(this, [=](){ classChanged_.emit(); });
	
};


void BackgroundColorWidget::setValue(std::string className)
{
	// std::cout << "\n combobox colors set value: " << className << "\n";
	comboBox_color->setValue("none");
	comboBox_intensity->setValue("500");
	comboBox_opacity->setValue("100");
	comboBox_gradient_step->setValue();
	if(std::regex_match(className, regex_custom_color)){
		// std::cout << "set custom value";
		comboBox_color->setValue(className);
	}else if(std::regex_match(className, regex_def_classes) || className.compare("none") == 0 || className.compare("") == 0){
		// std::cout << "should deactivate <" << className << ">\n";
		comboBox_intensity->disable(true);
		comboBox_opacity->disable(true);
		comboBox_gradient_step->disable(true);
		// std::cout << "default value: \n";
	} else {
		// std::cout << "should activate <" << className << ">\n";
		comboBox_intensity->disable(false);
		comboBox_opacity->disable(false);
		comboBox_gradient_step->disable(false);
		auto pos = className.find("-");
		auto nextPos = className.find("-", pos+1);
		auto colorClass = className.substr(0, nextPos);
		auto intensityClass = className.substr(nextPos+1, className.find("/", nextPos+1)-nextPos-1);				
		auto opacityClass = className.substr(className.find("/")+1, className.length()-className.find("/")-1);
		// std::cout << "colorClass: " << colorClass << "\n";
		// std::cout << "intensityClass: " << intensityClass << "\n";
		// std::cout << "opacityClass: " << opacityClass << "\n";
		comboBox_color->setValue(colorClass);
		comboBox_intensity->setValue(intensityClass);
		comboBox_opacity->setValue(opacityClass);
	}

	if(std::regex_match(className, std::regex("(from|to|via)"))){
		// comboBox_color->setValue(className);
		// comboBox_gradient_step->setValue(className);
		comboBox_gradient_step->setHidden(false);
	}else {
		comboBox_gradient_step->setHidden(true);
	}
}


