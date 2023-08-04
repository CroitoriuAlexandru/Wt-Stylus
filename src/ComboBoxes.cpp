#include "include/ElementBackground.h"
#include "include/ComboBoxes.h"
#include <iostream>
#include <regex>

void ComboBoxClassWithCustoms::setCustom(bool custom)
{
	if(custom){
		setCondition("class-custom", true);
		setCondition("class-combobox", false);
		// select_temp_->toggleStyleClass("hidden", true, true);
		// lineEdit_size_custom_->toggleStyleClass("hidden", false, true);
		checkbox_custom_value_->toggleStyleClass("[&>span]:text-green-700", true, true);
	}else {
		setCondition("class-custom", false);
		setCondition("class-combobox", true);
		// select_temp_->toggleStyleClass("hidden", false, true);
		// lineEdit_size_custom_->toggleStyleClass("hidden", true, true);
		checkbox_custom_value_->toggleStyleClass("[&>span]:text-green-700", false, true);
	}
}

ComboBoxClassWithCustoms::ComboBoxClassWithCustoms(std::vector<std::string> classNames)
	: WTemplate(tr("stylus.class.changer.widget"))
{
	bindEmpty("other");
	setStyleClass("flex justify-betwen items-center w-full text-xs relative px-3 me-2");
	
	setCondition("important-checkbox", true);
	setCondition("refresh-button", true);
	setCondition("custom-checkbox", true);
	setCondition("other-widgets", false);
	setCondition("class-custom", false);
	setCondition("class-combobox", true);

	btn_reset_ = bindWidget("refresh-button", std::make_unique<Wt::WPushButton>("↺"));
	select_temp_ = bindWidget("select-combobox", std::make_unique<Wt::WTemplate>(tr("stylus.class.changer.select.template")));
	checkbox_custom_value_ = bindWidget("checkbox-select-custom", std::make_unique<Wt::WCheckBox>("]"));
	checkbox_important_ = bindWidget("checkbox-important", std::make_unique<Wt::WCheckBox>("!"));
	btn_prev_ = select_temp_->bindWidget("prev-button", std::make_unique<Wt::WPushButton>("<"));
	comboBox_class = select_temp_->bindWidget("class-combobox", std::make_unique<Wt::WComboBox>());
	btn_next_ = select_temp_->bindWidget("next-button", std::make_unique<Wt::WPushButton>(">"));
	lineEdit_size_custom_ = bindWidget("custom-lineedit", std::make_unique<Wt::WLineEdit>());

	btn_prev_->setThemeStyleEnabled(false);
	btn_next_->setThemeStyleEnabled(false);
	btn_reset_->setThemeStyleEnabled(false);
	
	// comboBox_class->setStyleClass("overflow-visible");
	checkbox_important_->setStyleClass("[&>input]:hidden [&>span]:px-1 [&>span]:text [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0 [&>span]:hover:bg-neutral-800 rounded-md font-bold");
	checkbox_custom_value_->setStyleClass("[&>input]:hidden [&>span]:px-1 [&>span]:text [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0 [&>span]:hover:bg-neutral-800 rounded-md font-bold");
	btn_prev_->setStyleClass("rounded-r-none rounded-l-md border-r border-gray-600 border-solid px-1 bg-neutral-800 hover:bg-neutral-900 disabled:bg-neutral-700");
	btn_next_->setStyleClass("rounded-l-none rounded-r-md border-l border-gray-600 border-solid px-1 bg-neutral-800 hover:bg-neutral-900 disabled:bg-neutral-700");
	btn_reset_->setStyleClass("rounded-none p-1 m-0 hover:bg-neutral-800 rounded-xl");

	setOptions(classNames);


	btn_prev_->clicked().connect(this, [=](){
		comboBox_class->setCurrentIndex(comboBox_class->currentIndex() - 1);
		if(comboBox_class->currentIndex() < 0) comboBox_class->setCurrentIndex(comboBox_class->count()-1);
		classChanged_.emit();
	});

	btn_next_->clicked().connect(this, [=](){
		comboBox_class->setCurrentIndex(comboBox_class->currentIndex() + 1);
		classChanged_.emit();
	});

	btn_reset_->clicked().connect(this, [=](){
		checkbox_custom_value_->setChecked(false);
		setCustom(false);
		comboBox_class->setCurrentIndex(comboBox_class->findText(defaultValue, Wt::MatchFlag::StringExactly));
		checkbox_important_->setChecked(false);
		checkbox_important_->toggleStyleClass("text-red-500", false, true);
		classChanged_.emit();
	});

	// custom_temp_->toggleStyleClass("hidden", true, true);
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

	// emit signal when something changes
	comboBox_class->changed().connect(this, [=](){
		classChanged_.emit();
	});
	lineEdit_size_custom_->enterPressed().connect(this, [=](){
		classChanged_.emit();
	});


}

void ComboBoxClassWithCustoms::setOptions(std::vector<std::string> classNames)
{
	comboBox_class = select_temp_->bindWidget("class-combobox", std::make_unique<Wt::WComboBox>());
	for(auto& className : classNames){
		comboBox_class->addItem(className);
	}

	setValue(defaultValue);
	setCustom(false);
}

std::string ComboBoxClassWithCustoms::getValue()
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

void ComboBoxClassWithCustoms::setValue(std::string className)
{
	if(className.compare("") == 0)
	{
		comboBox_class->setCurrentIndex(comboBox_class->findText(defaultValue, Wt::MatchFlag::StringExactly));
		return;
	}
	// check for ! at the start of the class
	if(className.find("!") != std::string::npos){
		checkbox_important_->setChecked(true);
		// comboBox_class->checkbox_important_->clicked().emit(Wt::WMouseEvent());
		className = className.substr(1, className.length()-1);
		checkbox_important_->toggleStyleClass("text-red-500", true, true);
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

void ComboBoxClassWithCustoms::disable(bool disable)
{
	if(disable)
	{
		comboBox_class->disable();
		btn_prev_->disable();
		btn_next_->disable();
		btn_reset_->disable();
		checkbox_custom_value_->disable();
		checkbox_important_->disable();
		lineEdit_size_custom_->disable();
	}else {
		comboBox_class->enable();
		btn_prev_->enable();
		btn_next_->enable();
		btn_reset_->enable();
		checkbox_custom_value_->enable();
		checkbox_important_->enable();
		lineEdit_size_custom_->enable();
	}
}

ComboBoxColors::ComboBoxColors(std::vector<std::string> classNames, std::vector<std::string> colorIntensity, std::vector<std::string> colorOpacity)
	: WTemplate(tr("stylus.class.changer.color.widget"))
{
	setStyleClass("relative px-3 ms-auto me-2 flex");
	setCondition("other-widgets", true);
	comboBox_color = bindWidget("color-combobox", std::make_unique<ComboBoxClassWithCustoms>(classNames));
	comboBox_intensity = bindWidget("intensity-combobox", std::make_unique<ComboBoxClassWithCustoms>(colorIntensity));
	comboBox_opacity = bindWidget("opacity-combobox", std::make_unique<ComboBoxClassWithCustoms>(colorOpacity));

	comboBox_intensity->setCondition("important-checkbox", false);
	comboBox_opacity->setCondition("important-checkbox", false);
	
	comboBox_intensity->setCondition("refresh-button", false);
	comboBox_opacity->setCondition("refresh-button", false);
	
	comboBox_intensity->setCondition("custom-checkbox", false);
	comboBox_opacity->setCondition("custom-checkbox", false);

	comboBox_color->removeStyleClass("relative");
	comboBox_intensity->removeStyleClass("relative");
	comboBox_opacity->removeStyleClass("relative");

	comboBox_color->removeStyleClass("px-3");
	comboBox_intensity->removeStyleClass("px-3");
	comboBox_opacity->removeStyleClass("px-3");
	
	comboBox_color->addStyleClass("w-[100px]");

	comboBox_opacity->setDefaultValue("100");
	comboBox_intensity->setDefaultValue("500");

	comboBox_intensity->disable(true);
	comboBox_opacity->disable(true);

	comboBox_intensity->setValue("500");
	comboBox_opacity->setValue("100");

	comboBox_intensity->setValue();
	comboBox_opacity->setValue();

	comboBox_color->classChanged().connect(this, [=](){ 
		auto color = comboBox_color->getValue();
		if(color.compare("bg-inherit") == 0 ||
			color.compare("bg-current") == 0 ||
			color.compare("bg-transparent") == 0 ||
			color.compare("bg-black") == 0 ||
			color.compare("bg-white") == 0 ||
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
	std::cout << "\n combobox colors set value: " << className << "\n";
	comboBox_color->setValue();
	comboBox_intensity->setValue("500");
	comboBox_opacity->setValue("100");
	if(std::regex_match(className, regex_custom_color)){
		//custom color so it should :
		// hide intensity and opacity
		// set custom checkbox to true
		// set custom lineEdit to value
		std::cout << "set custom value";
		comboBox_color->setValue(className);
	}else if(std::regex_match(className, regex_def_classes) || className.compare("none") == 0){
		std::cout << "should deactivate" << className << "\n";
		comboBox_intensity->disable(true);
		comboBox_opacity->disable(true);
		std::cout << "default value: \n";
	} else {
		std::cout << "should activate" << className << "\n";
		comboBox_intensity->disable(false);
		comboBox_opacity->disable(false);
		auto pos = className.find("-");
		auto nextPos = className.find("-", pos+1);
		auto colorClass = className.substr(0, nextPos);
		auto intensityClass = className.substr(nextPos+1, className.find("/", nextPos+1)-nextPos-1);				
		auto opacityClass = className.substr(className.find("/")+1, className.length()-className.find("/")-1);
		std::cout << "colorClass: " << colorClass << "\n";
		std::cout << "intensityClass: " << intensityClass << "\n";
		std::cout << "opacityClass: " << opacityClass << "\n";
		comboBox_color->setValue(colorClass);
		comboBox_intensity->setValue(intensityClass);
		comboBox_opacity->setValue(opacityClass);
	}


}


std::string ComboBoxColors::getValue()
{
	std::string selectedClass = comboBox_color->getValue();
	
	if(selectedClass.compare("bg-inherit") == 0 ||
		selectedClass.compare("bg-current") == 0 ||
		selectedClass.compare("bg-transparent") == 0 ||
		selectedClass.compare("bg-black") == 0 ||
		selectedClass.compare("bg-white") == 0 ||
		selectedClass.compare("none") == 0)
		{
		return selectedClass;
	} else
	{
		selectedClass = comboBox_color->getValue() + "-" + comboBox_intensity->getValue() + "/" + comboBox_opacity->getValue();
	}
	return selectedClass;
}

// void ComboBoxColors::setCustom(bool custom){
// 	if(custom){
//  		comboBox_color->setCustom(custom);
// 		setCondition("custom-checkbox", true);
// 	}else {
// 		comboBox_color->setCustom(custom);
// 		setCondition("custom-checkbox", false);
// 	}
// }

