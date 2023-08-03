#include "include/ElementBackground.h"
#include "include/ComboBoxes.h"
#include <iostream>
#include <regex>

void ComboBoxClassWithCustoms::setCustom(bool custom)
{
	if(custom){
		select_temp_->toggleStyleClass("hidden", true, true);
		lineEdit_size_custom_->toggleStyleClass("hidden", false, true);
		checkbox_custom_value_->toggleStyleClass("[&>span]:text-green-700", true, true);
	}else {
		select_temp_->toggleStyleClass("hidden", false, true);
		lineEdit_size_custom_->toggleStyleClass("hidden", true, true);
		checkbox_custom_value_->toggleStyleClass("[&>span]:text-green-700", false, true);
	}
}

ComboBoxClassWithCustoms::ComboBoxClassWithCustoms(std::vector<std::string> classNames)
	: WTemplate(tr("stylus.class.changer.widget"))
{
	bindEmpty("other");
	setStyleClass("flex justify-betwen items-center w-full text-xs");
	setCondition("custom-checkbox", true);

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
	
	comboBox_class->setStyleClass("overflow-visible");
	checkbox_important_->setStyleClass("[&>input]:hidden [&>span]:px-1 [&>span]:text [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0 [&>span]:hover:bg-neutral-800 rounded-md font-bold");
	checkbox_custom_value_->setStyleClass("[&>input]:hidden [&>span]:px-1 [&>span]:text [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0 [&>span]:hover:bg-neutral-800 rounded-md font-bold");
	btn_prev_->setStyleClass("rounded-r-none rounded-l-md border-r border-gray-600 border-solid px-1 bg-neutral-800 hover:bg-neutral-900");
	btn_next_->setStyleClass("rounded-l-none rounded-r-md border-l border-gray-600 border-solid px-1 bg-neutral-800 hover:bg-neutral-900");
	btn_reset_->setStyleClass("rounded-none p-1 m-0 hover:bg-neutral-800 rounded-xl");

	// btn_prev_->toggleStyleClass("hidden", true, true);
	// btn_next_->toggleStyleClass("hidden", true, true);

	for(auto& className : classNames){
		comboBox_class->addItem(className);
	}

	setValue("none");
	setCustom(false);


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
		// checkbox_custom_value_->clicked().emit(Wt::WMouseEvent());
		setCustom(false);
		comboBox_class->setCurrentIndex(comboBox_class->findText("none", Wt::MatchFlag::StringExactly));
		// comboBox_class->activated().emit(comboBox_class->currentIndex());
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
		if(getValue().compare("none") != 0) classChanged_.emit();
	});

	// emit signal when something changes
	comboBox_class->activated().connect(this, [=](){
		classChanged_.emit();
	});
	lineEdit_size_custom_->enterPressed().connect(this, [=](){
		classChanged_.emit();
	});
}


std::string ComboBoxClassWithCustoms::getValue()
{
	std::string selectedClass = "";

	if(checkbox_custom_value_->isChecked() && lineEdit_size_custom_->text().toUTF8() != ""){
		selectedClass = custom_start_.toUTF8() + "[" + lineEdit_size_custom_->valueText().toUTF8() + "]";
	}else{
		selectedClass = comboBox_class->currentText().toUTF8();
	}	
	if(checkbox_important_->isChecked() && selectedClass.compare("none") != 0){
		selectedClass = "!" + selectedClass;
	}
	// std::cout << "\n selectedClass: " << selectedClass << "\n";
return selectedClass;
}

void ComboBoxClassWithCustoms::setValue(std::string className)
{
	if(className.compare("") == 0)
	{
		comboBox_class->setCurrentIndex(comboBox_class->findText("none", Wt::MatchFlag::StringExactly));
		return;
	}
	// check for ! at the start of the class
	if(className.find("!") != std::string::npos){
		checkbox_important_->setChecked(true);
		// comboBox_class->checkbox_important_->clicked().emit(Wt::WMouseEvent());
		className = className.substr(1, className.length()-1);
		checkbox_important_->toggleStyleClass("text-red-500", true, true);
		std::cout << "\n\n important value :" << className << "\n\n";
	}


	if(className.find("]") != std::string::npos) {
		std::cout << "\n\n custom value :" << className << "\n\n";
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


ComboBoxColors::ComboBoxColors(std::vector<std::string> classNames, std::vector<std::string> colorIntensity, std::vector<std::string> colorOpacity)
	: WTemplate(tr("stylus.colors.widget"))
{
	setStyleClass("flex justify-betwen items-center w-full");
	comboBox_class = bindWidget("combobox-1", std::make_unique<ComboBoxClassWithCustoms>(classNames));
	option_container_ = comboBox_class->bindWidget("other", std::make_unique<Wt::WContainerWidget>());
	
	auto intensity_temp = option_container_->addWidget(std::make_unique<Wt::WTemplate>(Wt::WString::tr("stylus.colors.intensity-opacity.template")));
	option_container_->addWidget(std::make_unique<Wt::WText>(" / "));
	auto opacity_temp = option_container_->addWidget(std::make_unique<Wt::WTemplate>(Wt::WString::tr("stylus.colors.intensity-opacity.template")));
	option_container_->setStyleClass("flex");


	// comboBox_color = bindWidget("combobox-2", std::make_unique<Wt::WComboBox>());
	comboBox_intensity = intensity_temp->bindWidget("combobox", std::make_unique<Wt::WComboBox>());
	comboBox_opacity = opacity_temp->bindWidget("combobox", std::make_unique<Wt::WComboBox>());

	auto intensity_btn_up = intensity_temp->bindWidget("up-button", std::make_unique<Wt::WPushButton>("▲"));
	auto intensity_btn_down = intensity_temp->bindWidget("down-button", std::make_unique<Wt::WPushButton>("▼"));

	auto opacity_btn_up = opacity_temp->bindWidget("up-button", std::make_unique<Wt::WPushButton>("▲"));
	auto opacity_btn_down = opacity_temp->bindWidget("down-button", std::make_unique<Wt::WPushButton>("▼"));

	intensity_btn_up->setThemeStyleEnabled(false);
	intensity_btn_down->setThemeStyleEnabled(false);
	opacity_btn_up->setThemeStyleEnabled(false);
	opacity_btn_down->setThemeStyleEnabled(false);

	std::vector<std::string> color_classes;
	for(auto& className : classNames){
		Wt::WString item;
		if(className.compare("none") == 0){
			item = className;
		}else{
			item = custom_start_ + className;
		}
		color_classes.push_back(item.toUTF8());
	}

	
	// set intensity and opacity values
	for(auto& intensity : colorIntensity){
		comboBox_intensity->addItem(intensity);
	}
	for(auto& opacity : colorOpacity){
		comboBox_opacity->addItem(opacity);
	}




	intensity_btn_up->clicked().connect(this, [=](){
		// std::cout << "\n\n intensity_btn_up \n\n";
		comboBox_intensity->setCurrentIndex(comboBox_intensity->currentIndex() + 1);
		comboBox_intensity->activated().emit(comboBox_intensity->currentIndex());
	});

	intensity_btn_down->clicked().connect(this, [=](){
		// std::cout << "\n\n intensity_btn_down \n\n";
		comboBox_intensity->setCurrentIndex(comboBox_intensity->currentIndex() - 1);
		comboBox_intensity->activated().emit(comboBox_intensity->currentIndex());
	});

	opacity_btn_up->clicked().connect(this, [=](){
		// std::cout << "\n\n opacity_btn_up \n\n";
		comboBox_opacity->setCurrentIndex(comboBox_opacity->currentIndex() - 1);
		comboBox_opacity->activated().emit(comboBox_opacity->currentIndex());
	});

	opacity_btn_down->clicked().connect(this, [=](){
		// std::cout << "\n\n opacity_btn_down \n\n";
		comboBox_opacity->setCurrentIndex(comboBox_opacity->currentIndex() + 1);
		comboBox_opacity->activated().emit(comboBox_opacity->currentIndex());
	});

	// set styles
	std::string comboBox_styles = "apearance-none bg-neutral-800 hover:bg-neutral-900 p-px w-full rounded-none m-0 h-full w-full text-center focus-visible:outline-none";
	comboBox_intensity->setStyleClass(comboBox_styles);
	comboBox_opacity->setStyleClass(comboBox_styles);

	// comboBox signals
	option_container_->toggleStyleClass("hidden", true, true);
	comboBox_class->classChanged().connect(this, [=](){ 
		auto selectedClass = comboBox_class->getValue();
		if(std::regex_match(selectedClass, regex_def_classes) || selectedClass.compare("none") == 0){
			option_container_->toggleStyleClass("hidden", true, true);
		}else {
			option_container_->toggleStyleClass("hidden", false, true);
		}
		classChanged_.emit();
	});
	
	comboBox_intensity->activated().connect(this, [=](){ classChanged_.emit(); });
	comboBox_opacity->activated().connect(this, [=](){ classChanged_.emit(); });

}

void ComboBoxColors::setValue(std::string className)
{
	// std::cout << "\n\n ComboBoxColors::setValue <"<< className << ">\n\n";
	// bg custom regexp


	// defoult classes bg-transparent bg-black bg-white bg-current bg-inherit
	if(std::regex_match(className, regex_def_classes)){
		std::cout << "default class <" << className << ">\n";
		comboBox_class->setValue(className);
		
	}
	// custom classes bg-[color]
	else if(std::regex_match(className, regex_custom_color)){
		std::cout << "custom class <" << className << ">\n";
		if(className.find("]") != std::string::npos) {
		// std::cout << "\n\n custom value :" << className << "\n\n";
		// find the next '[' position in className
		int pos = className.find("[");
		if(pos != std::string::npos){
			// find the next ']' position in className
			int pos2 = className.find("]");
			if(pos2 != std::string::npos){
				// get the value between '[' and ']'
				std::string value = className.substr(pos+1, pos2-pos-1);
				lineEdit_color_custom_->setText(value);
			}
		}
		comboBox_class->checkbox_custom_value_->clicked().emit(Wt::WMouseEvent());
		comboBox_class->setCustom(true);
		}else {
			comboBox_class->setCustom(false);
		}
	} else if (std::regex_match(className, regex_color_classes)){
	// color classes bg-[color]-[intensity]/[opacity]
		// find the secconds - in className
		int pos2 = className.find("-", className.find("-")+1);
		auto firstPartClass = className.substr(0, pos2);
		auto intensity = className.substr(pos2+1, className.find("/")-pos2-1);
		auto opacity = className.substr(className.find("/")+1, className.length()-className.find("/")-1);
		comboBox_class->setValue(firstPartClass);
		comboBox_intensity->setCurrentIndex(comboBox_intensity->findText(intensity, Wt::MatchFlag::StringExactly));
		comboBox_opacity->setCurrentIndex(comboBox_opacity->findText(opacity, Wt::MatchFlag::StringExactly));
		option_container_->toggleStyleClass("hidden", false, true);
		// std::cout << "color class <" << className << ">\n";
		// std::cout << "\n\n firstPartClass: " << firstPartClass << "\n\n";
		// std::cout << "\n\n intensity: " << intensity << "\n\n";
		// std::cout << "\n\n opacity: " << opacity << "\n\n";
	}else if(className.compare("none") == 0){
		comboBox_class->setValue(className);
		comboBox_intensity->setCurrentIndex(comboBox_intensity->findText("500", Wt::MatchFlag::StringExactly));
		comboBox_opacity->setCurrentIndex(comboBox_opacity->findText("100", Wt::MatchFlag::StringExactly));
		option_container_->toggleStyleClass("hidden", true, true);
		
	}else {
		// std::cout << "\n\nsomething is not write in the logic of setValue in ComboBoxColors -- " << className << "\n\n";
	}
}


std::string ComboBoxColors::getValue()
{
	std::string selectedClass = "";
	if(comboBox_class->checkbox_custom_value_->isChecked() && lineEdit_color_custom_->text().toUTF8() != ""){
		selectedClass = custom_start_.toUTF8() + "[" + lineEdit_color_custom_->valueText().toUTF8() + "]";
	}else if (comboBox_class->getValue().compare("none") == 0 || comboBox_class->getValue().compare("!none") == 0){
		selectedClass = comboBox_class->getValue();
	}else if(!std::regex_match(comboBox_class->getValue(), regex_def_classes)){
		selectedClass = comboBox_class->getValue();
		selectedClass += "-" + comboBox_intensity->currentText().toUTF8();
		selectedClass += "/" + comboBox_opacity->currentText().toUTF8();

	// std::cout << "\n\n selectedClass: " << selectedClass << "\n";
	// std::cout << "interity: " << comboBox_intensity->currentText().toUTF8() << "\n";
	// std::cout << "opacity: " << comboBox_opacity->currentText().toUTF8() << "\n";
	}else {
		selectedClass = comboBox_class->getValue();
	}
	return selectedClass;
}

void ComboBoxColors::setCustom(bool custom){
	if(custom){
 		comboBox_class->setCustom(custom);
		setCondition("custom-checkbox", true);
	}else {
		comboBox_class->setCustom(custom);
		setCondition("custom-checkbox", false);
	}
}

