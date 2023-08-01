#include "include/ElementBackground.h"
#include "include/ComboBoxes.h"
#include <iostream>
#include <regex>

ComboBoxClassWithCustoms::ComboBoxClassWithCustoms()
	: WTemplate(tr("stylus.class.changer.widget"))
{
	bindEmpty("other");
	setStyleClass("flex justify-betwen items-center w-full");

	btn_reset_ = bindWidget("refresh-button", std::make_unique<Wt::WPushButton>("↺"));
	select_temp_ = bindWidget("select-combobox", std::make_unique<Wt::WTemplate>(tr("stylus.class.changer.select.template")));
	custom_temp_ = bindWidget("custom-lineedit", std::make_unique<Wt::WTemplate>(tr("stylus.class.changer.custom.template")));
	checkbox_custom_value_ = bindWidget("checkbox-select-custom", std::make_unique<Wt::WCheckBox>());

	btn_prev_ = select_temp_->bindWidget("prev-button", std::make_unique<Wt::WPushButton>("<"));
	comboBox_class = select_temp_->bindWidget("class-combobox", std::make_unique<Wt::WComboBox>());
	btn_next_ = select_temp_->bindWidget("next-button", std::make_unique<Wt::WPushButton>(">"));
	lineEdit_size_custom_ = custom_temp_->bindWidget("lineedit", std::make_unique<Wt::WLineEdit>());

	btn_prev_->setThemeStyleEnabled(false);
	btn_next_->setThemeStyleEnabled(false);
	btn_reset_->setThemeStyleEnabled(false);

	// std::string wrappers_styles = "flex w-full border border-gray-600 border-solid rounded-md overflow-hidden";
	// select_temp_->setStyleClass(wrappers_styles);
	// custom_temp_->setStyleClass(wrappers_styles);
	btn_prev_->setStyleClass("rounded-r-none rounded-l-md border-r border-gray-600 border-solid px-1 bg-neutral-800 hover:bg-neutral-900");
	btn_next_->setStyleClass("rounded-l-none rounded-r-md border-l border-gray-600 border-solid px-1 bg-neutral-800 hover:bg-neutral-900");
	btn_reset_->setStyleClass("rounded-none pr-1 m-0");
	// comboBox_class->setStyleClass("p-px w-full rounded-none m-0 h-full w-full bg-neutral-800 appearance-none focus-visible:outline-none hover:bg-neutral-900");
	// lineEdit_size_custom_->setStyleClass("p-px w-full ps-1 rounded-none m-0 h-full bg-neutral-800 w-full text-center appearance-none ps-1 focus-visible:outline-none hover:bg-neutral-900");
	// checkbox_custom_value_->setStyleClass("ml-1");
	// // iterate over classnames and add them to the combobox
	
	btn_prev_->clicked().connect(this, [=](){
		comboBox_class->setCurrentIndex(comboBox_class->currentIndex() - 1);
		comboBox_class->activated().emit(comboBox_class->currentIndex());
	});
	btn_next_->clicked().connect(this, [=](){
		comboBox_class->setCurrentIndex(comboBox_class->currentIndex() + 1);
		comboBox_class->activated().emit(comboBox_class->currentIndex());
	});
	btn_reset_->clicked().connect(this, [=](){
		checkbox_custom_value_->setChecked(false);
		checkbox_custom_value_->clicked().emit(Wt::WMouseEvent());
		comboBox_class->setCurrentIndex(comboBox_class->findText("none", Wt::MatchFlag::StringExactly));
		comboBox_class->activated().emit(comboBox_class->currentIndex());
	});


	custom_temp_->toggleStyleClass("hidden", true, true);
	checkbox_custom_value_->clicked().connect(this, [=](){
		if(checkbox_custom_value_->isChecked()){
			select_temp_->toggleStyleClass("hidden", true, true);
			custom_temp_->toggleStyleClass("hidden", false, true);
		}else{
			select_temp_->toggleStyleClass("hidden", false, true);
			custom_temp_->toggleStyleClass("hidden", true, true);
		}
	});

	// emit signal when something changes
	comboBox_class->activated().connect(this, [=](){
		classChanged_.emit();
	});
	lineEdit_size_custom_->enterPressed().connect(this, [=](){
		classChanged_.emit();
	});
}

void ComboBoxClassWithCustoms::setComboBoxValues(std::vector<std::string> classNames)
{
	for(auto& className : classNames){
		comboBox_class->addItem(className);
	}
	if(comboBox_class->findText("none", Wt::MatchFlag::StringExactly) == -1){
		std::cout << "\n\n none not found ========================================== \n\n";
	}
	setValue("none");
}

std::string ComboBoxClassWithCustoms::getValue()
{
	std::string selectedClass = "";

	if(checkbox_custom_value_->isChecked() && lineEdit_size_custom_->text().toUTF8() != ""){
		selectedClass = custom_start_.toUTF8() + "[" + lineEdit_size_custom_->valueText().toUTF8() + "]";
	}else{
		selectedClass = comboBox_class->currentText().toUTF8();
	}
	// std::cout << "\n selectedClass: " << selectedClass << "\n";
return selectedClass;
}

void ComboBoxClassWithCustoms::setValue(std::string className)
{
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


ComboBoxColors::ComboBoxColors()
	: WTemplate(tr("stylus.colors.widget"))
{
	setStyleClass("flex justify-betwen items-center w-full");
	comboBox_class = bindWidget("combobox-1", std::make_unique<ComboBoxClassWithCustoms>());
	auto option_container = comboBox_class->bindWidget("other", std::make_unique<Wt::WContainerWidget>());
	
	auto intensity_temp = option_container->addWidget(std::make_unique<Wt::WTemplate>(Wt::WString::tr("stylus.colors.intensity-opacity.template")));
	option_container->addWidget(std::make_unique<Wt::WText>(" / "));
	auto opacity_temp = option_container->addWidget(std::make_unique<Wt::WTemplate>(Wt::WString::tr("stylus.colors.intensity-opacity.template")));
	option_container->setStyleClass("flex");


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

	intensity_btn_up->clicked().connect(this, [=](){
		std::cout << "\n\n intensity_btn_up \n\n";
		comboBox_intensity->setCurrentIndex(comboBox_intensity->currentIndex() + 1);
		comboBox_intensity->activated().emit(comboBox_intensity->currentIndex());
	});

	intensity_btn_down->clicked().connect(this, [=](){
		std::cout << "\n\n intensity_btn_down \n\n";
		comboBox_intensity->setCurrentIndex(comboBox_intensity->currentIndex() - 1);
		comboBox_intensity->activated().emit(comboBox_intensity->currentIndex());
	});

	opacity_btn_up->clicked().connect(this, [=](){
		std::cout << "\n\n opacity_btn_up \n\n";
		comboBox_opacity->setCurrentIndex(comboBox_opacity->currentIndex() - 1);
		comboBox_opacity->activated().emit(comboBox_opacity->currentIndex());
	});

	opacity_btn_down->clicked().connect(this, [=](){
		std::cout << "\n\n opacity_btn_down \n\n";
		comboBox_opacity->setCurrentIndex(comboBox_opacity->currentIndex() + 1);
		comboBox_opacity->activated().emit(comboBox_opacity->currentIndex());
	});

	// set styles
	std::string comboBox_styles = "apearance-none bg-neutral-800 hover:bg-neutral-900 p-px w-full rounded-none m-0 h-full w-full text-center focus-visible:outline-none";
	comboBox_intensity->setStyleClass(comboBox_styles);
	comboBox_opacity->setStyleClass(comboBox_styles);

	// comboBox signals
	comboBox_class->classChanged().connect(this, [=](){ classChanged_.emit(); });
	comboBox_intensity->activated().connect(this, [=](){ classChanged_.emit(); });
	comboBox_opacity->activated().connect(this, [=](){ classChanged_.emit(); });

}

void ComboBoxColors::setValue(std::string className)
{
	if(className.find("]") != std::string::npos) {
		std::cout << "\n\n custom value :" << className << "\n\n";
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
		comboBox_class->checkbox_custom_value_->setChecked(true);
		comboBox_class->checkbox_custom_value_->clicked().emit(Wt::WMouseEvent());
	}else {
		std::cout << "\n\n selectable value :" << className << "\n\n";
		// checkbox_custom_value_->setChecked(false);
		// checkbox_custom_value_->clicked().emit(Wt::WMouseEvent());
		// comboBox_class->setCurrentIndex(comboBox_class->findText(className, Wt::MatchFlag::StringExactly));
		comboBox_class->setValue(className);
	}
}


void ComboBoxColors::setComboBoxValues(std::vector<std::string> classNames)
{
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
	comboBox_class->setComboBoxValues(color_classes);
	auto color_intensity = {
		"50", "100", "200", "300", "400", "500", "600", "700", "800", "900", "950"
	};

	auto opacity = {
		"100", "95", "90", "85", "80", "75", "70", "65", "60", "55",
		"50", "45", "40", "35", "30", "25", "20", "15", "10", "5",
		"0"
		// "50", "55", "60", "65", "70", "75", "80", "85", "90", "95", 
	};
	
	// set intensity and opacity values
	for(auto& intensity : color_intensity){
		comboBox_intensity->addItem(intensity);
	}
	for(auto& opacity : opacity){
		comboBox_opacity->addItem(opacity);
	}
}

std::string ComboBoxColors::getValue()
{
	std::string selectedClass = "";
	if(comboBox_class->checkbox_custom_value_->isChecked() && lineEdit_color_custom_->text().toUTF8() != ""){
		selectedClass = custom_start_.toUTF8() + "[" + lineEdit_color_custom_->valueText().toUTF8() + "]";
	}else if (comboBox_class->getValue().compare("none") != 0){
		selectedClass = comboBox_class->getValue();
	}else {
		selectedClass = comboBox_class->getValue();
		selectedClass += "-" + comboBox_intensity->currentText().toUTF8();
		selectedClass += "/" + comboBox_opacity->currentText().toUTF8();
	}
	return selectedClass;
}
