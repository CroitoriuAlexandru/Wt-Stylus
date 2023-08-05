#include "include/ElementBackground.h"
#include <regex>
#include <string>

BackgroundStyleClasses::BackgroundStyleClasses() {
	auto def_classes = {
		"inherit", "current", "transparent", "black", "white"
	};

	color_intensity = {
		"50", "100", "200", "300", "400", "500", "600", "700", "800", "900", "950"
	};

	color_opacity = {
		"0", "5", "10", "20", "25", "30", "40", 
		"50", "60", "70", "75", "80", "90", "95", "100"
	};

	bg_attachment_classes = {
		"none", "bg-fixed", "bg-local", "bg-scroll"
	};

	bg_clip_classes = {
		"none", "bg-clip-border", "bg-clip-padding", "bg-clip-content", "bg-clip-text"
	};

	auto colors = {
		"slate", "gray", "zinc", "neutral", "stone", "red", "orange", "amber", "yellow", "lime", "green", "emerald", "teal", "cyan", "sky", "blue", "indigo", "violet", "purple", "fuchsia", "pink", "rose"
	};

	bg_origin_classes = {
		"none", "bg-origin-border", "bg-origin-padding", "bg-origin-content"
	};

	bg_position_classes = {
		"none", "bg-bottom", "bg-center", "bg-left", "bg-left-bottom", "bg-left-top", "bg-right", "bg-right-bottom", "bg-right-top", "bg-top"
	};

	bg_repeat_classes = {
		"none", "bg-repeat", "bg-no-repeat", "bg-repeat-x", "bg-repeat-y", "bg-repeat-round", "bg-repeat-space"
	};

	bg_size_classes = {
		"none", "bg-auto", "bg-cover", "bg-contain"
	};

	bg_image_classes = {
		"none", "bg-gradient-to-t", "bg-gradient-to-tr", "bg-gradient-to-r", "bg-gradient-to-br", "bg-gradient-to-b", "bg-gradient-to-bl", "bg-gradient-to-l", "bg-gradient-to-tl"
	};

	gradient_step = {
		"0%", "5%", "10%", "15%", "20%", "25%", "30%", "35%", "40%", "45%", "50%", "55%", "60%", "65%", "70%", "75%", "80%", "85%", "90%", "95%", "100%"
	};

	

	

	for(auto styleClass : def_classes){
		bg_color_classes.push_back("bg-" + std::string(styleClass));
		bg_color_from_classes.push_back("from-" + std::string(styleClass));
		bg_color_via_classes.push_back("via-" + std::string(styleClass));
		bg_color_to_classes.push_back("to-" + std::string(styleClass));
	}
	bg_color_classes.push_back("none");
	bg_color_from_classes.push_back("none");
	bg_color_via_classes.push_back("none");
	bg_color_to_classes.push_back("none");

	for(auto styleClass : colors){
		bg_color_classes.push_back("bg-" + std::string(styleClass));
		bg_color_from_classes.push_back("from-" + std::string(styleClass));
		bg_color_via_classes.push_back("via-" + std::string(styleClass));
		bg_color_to_classes.push_back("to-" + std::string(styleClass));
	}

	for(auto step : gradient_step){
		bg_gradient_step_from_classes.push_back("from-" + std::string(step));
		bg_gradient_step_via_classes.push_back("via-" + std::string(step));
		bg_gradient_step_to_classes.push_back("to-" + std::string(step));
	}

}



ElementBackgroundWidget::ElementBackgroundWidget(std::string templateName)
	: WDialog("Background"),
	colors()
{

	setModal(false);
	setResizable(false);
	setStyleClass("min-w-fit max-w-[300px] bg-neutral-700 text-neutral-400");
	titleBar()->clear();
	contents()->clear();

	content_temp = contents()->addWidget(std::make_unique<Wt::WTemplate>(Wt::WString::tr(templateName)));
	content_temp->bindString("color-title","Color");
	comboBox_attachment = content_temp->bindWidget("combobox-attachment", std::make_unique<ComboBoxClassWithCustoms>(colors.bg_attachment_classes));
	comboBox_clip = content_temp->bindWidget("combobox-clip", std::make_unique<ComboBoxClassWithCustoms>(colors.bg_clip_classes));
	comboBox_origin = content_temp->bindWidget("combobox-origin", std::make_unique<ComboBoxClassWithCustoms>(colors.bg_origin_classes));
	comboBox_position = content_temp->bindWidget("combobox-position", std::make_unique<ComboBoxClassWithCustoms>(colors.bg_position_classes));
	comboBox_repeat = content_temp->bindWidget("combobox-repeat", std::make_unique<ComboBoxClassWithCustoms>(colors.bg_repeat_classes));
	comboBox_size = content_temp->bindWidget("combobox-size", std::make_unique<ComboBoxClassWithCustoms>(colors.bg_size_classes));
	comboBox_image = content_temp->bindWidget("combobox-image", std::make_unique<ComboBoxClassWithCustoms>(colors.bg_image_classes));
	comboBox_color = content_temp->bindWidget("color-widget", std::make_unique<ComboBoxColors>(colors.bg_color_classes, colors.color_intensity, colors.color_opacity));
	comboBox_color_via = content_temp->bindWidget("combobox-color-via", std::make_unique<ComboBoxColors>(colors.bg_color_via_classes, colors.color_intensity, colors.color_opacity));
	comboBox_color_to = content_temp->bindWidget("combobox-color-to", std::make_unique<ComboBoxColors>(colors.bg_color_to_classes, colors.color_intensity, colors.color_opacity));

	// set regular expresion for custom value w-[10px]
	comboBox_attachment->setCustomValueString("bg-");
	comboBox_clip->setCustomValueString("bg-clip-");
	comboBox_origin->setCustomValueString("bg-origin-");
	comboBox_position->setCustomValueString("bg-");
	comboBox_repeat->setCustomValueString("bg-");
	comboBox_size->setCustomValueString("bg-");
	comboBox_color->setCustomValueString("bg-");
	comboBox_image->setCustomValueString("bg-");
	comboBox_color_via->setCustomValueString("via-");
	comboBox_color_to->setCustomValueString("to-");


	comboBox_color->setStepOptions(colors.bg_gradient_step_from_classes);
	comboBox_color_via->setStepOptions(colors.bg_gradient_step_via_classes);
	comboBox_color_to->setStepOptions(colors.bg_gradient_step_to_classes);

	comboBox_color->comboBox_gradient_step->setDefaultValue("from-0%");
	comboBox_color_via->comboBox_gradient_step->setDefaultValue("via-50%");
	comboBox_color_to->comboBox_gradient_step->setDefaultValue("to-100%");

	// deactivate custom checkbox
	comboBox_attachment->setCondition("custom-checkbox", false);
	comboBox_clip->setCondition("custom-checkbox", false);
	comboBox_origin->setCondition("custom-checkbox", false);
	comboBox_repeat->setCondition("custom-checkbox", false);
	comboBox_size->setCondition("custom-checkbox", false);
	comboBox_position->setCondition("custom-checkbox", false);
	comboBox_image->setCondition("custom-checkbox", false);

	// signals for default classes for tailwind
	comboBox_attachment->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_clip->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_origin->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_position->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_repeat->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_size->classChanged().connect([=](){ styleChanged_.emit(); });

	comboBox_image->classChanged().connect([=](){ 
		auto value = comboBox_image->getValue();
		// std::cout << "\n\n value: <" << value << ">\n";

		// background_image_regex
		if(comboBox_image->comboBox_class->currentIndex() != 0){
			// std::cout << " ---- ---------cusotm start = " << comboBox_color->custom_start_ << ">-----------------------\n";
			content_temp->setCondition("bg-gradient", true);
			if(comboBox_color->custom_start_.compare("from-") != 0){
				comboBox_color->setValue();
				styleChanged_.emit();
				content_temp->bindString("color-title", "from");
				comboBox_color->custom_start_ = "from-";
				comboBox_color->comboBox_color->setOptions(colors.bg_color_from_classes);
				comboBox_color->comboBox_color->setCustomValueString("from-");
				comboBox_color->comboBox_gradient_step->setHidden(false);
				comboBox_color_to->comboBox_gradient_step->setHidden(false);
				comboBox_color_via->comboBox_gradient_step->setHidden(false);
			}
		}else {
			comboBox_color->custom_start_ = "bg-";
			content_temp->setCondition("bg-gradient", false);
			content_temp->bindString("color-title", "Color");
			comboBox_color->comboBox_color->setCustomValueString("bg-");
			comboBox_color->comboBox_color->setOptions(colors.bg_color_classes);
			comboBox_color->setValue();
			comboBox_color->comboBox_gradient_step->setHidden(true);
			comboBox_color_to->comboBox_gradient_step->setHidden(true);
			comboBox_color_via->comboBox_gradient_step->setHidden(true);
		}
		styleChanged_.emit();
	});
	comboBox_color->classChanged().connect([=](){
		styleChanged_.emit(); 
	});
		
	comboBox_color_via->classChanged().connect([=](){ 
		styleChanged_.emit(); 
	});

	comboBox_color_to->classChanged().connect([=](){ 
		styleChanged_.emit();
	});
};

std::string ElementBackgroundWidget::getStyles()
{
	std::string elementClasses;

	if(comboBox_image->getValue().compare("none") != 0){ 
		elementClasses += comboBox_image->getValue() + " ";
		if(comboBox_color->getValue().compare("none") != 0){ elementClasses += comboBox_color->getValue() + " " + comboBox_color->comboBox_gradient_step->getValue() + " "; }
		if(comboBox_color_via->getValue().compare("none") != 0){ elementClasses += comboBox_color_via->getValue() + " " + comboBox_color_via->comboBox_gradient_step->getValue() + " "; }
		if(comboBox_color_to->getValue().compare("none") != 0){ elementClasses += comboBox_color_to->getValue() + " " + comboBox_color_to->comboBox_gradient_step->getValue() + " "; }
	}else {
		if(comboBox_color->getValue().compare("none") != 0){ elementClasses += comboBox_color->getValue() + " "; }
	}
	if(comboBox_attachment->getValue().compare("none") != 0){ elementClasses += comboBox_attachment->getValue() + " "; }
	if(comboBox_clip->getValue().compare("none") != 0){ elementClasses += comboBox_clip->getValue() + " "; }
	if(comboBox_origin->getValue().compare("none") != 0){ elementClasses += comboBox_origin->getValue() + " "; }
	if(comboBox_position->getValue().compare("none") != 0){ elementClasses += comboBox_position->getValue() + " "; }
	if(comboBox_repeat->getValue().compare("none") != 0){ elementClasses += comboBox_repeat->getValue() + " "; }
	if(comboBox_size->getValue().compare("none") != 0){ elementClasses += comboBox_size->getValue() + " "; }

	return elementClasses;
}

void ElementBackgroundWidget::setClasses(BackgroundData bgData)
{
	resetStyles();

	// std::cout << "\n\n ElementBackgroundWidget::setClasses \n";
	// std::cout << "attachment class = " << bgData.bg_attachment << "\n";
	// std::cout << "clip class = " << bgData.bg_clip << "\n";
	// std::cout << "color class = " << bgData.bg_color_class << "\n";
	// std::cout << "origin class = " << bgData.bg_origin << "\n";
	// std::cout << "position class = " << bgData.bg_position << "\n";
	// std::cout << "repeat class = " << bgData.bg_repeat << "\n";
	// std::cout << "size class = " << bgData.bg_size << "\n";
	// std::cout << "image class = " << bgData.bg_image << "\n";
	// std::cout << "color via class = " << bgData.bg_color_via << "\n";
	// std::cout << "color to class = " << bgData.bg_color_to << "\n";

	comboBox_attachment->setValue(bgData.bg_attachment);
	comboBox_clip->setValue(bgData.bg_clip);
	comboBox_origin->setValue(bgData.bg_origin);
	comboBox_position->setValue(bgData.bg_position);
	comboBox_repeat->setValue(bgData.bg_repeat);
	comboBox_size->setValue(bgData.bg_size);
	comboBox_image->setValue(bgData.bg_image);


	if(bgData.bg_image.compare("") != 0){
		content_temp->setCondition("bg-gradient", true);
		content_temp->bindString("color-title", "From");
		comboBox_color->comboBox_color->setOptions(colors.bg_color_from_classes);
		// std::cout << " ---- ---------bgData.bg_color_from = " << bgData.bg_color_class << "\n";
		// std::cout << " ---- ---------bgData.bg_color_from_step = " << bgData.bg_color_from_step << "\n";
		// std::cout << " ---- ---------bgData.bg_color_via = " << bgData.bg_color_via << "\n";
		// std::cout << " ---- ---------bgData.bg_color_via_step = " << bgData.bg_color_via_step << "\n";
		// std::cout << " ---- ---------bgData.bg_color_to = " << bgData.bg_color_to << "\n";
		// std::cout << " ---- ---------bgData.bg_color_to_step = " << bgData.bg_color_to_step << "\n";
		comboBox_color->setValue(bgData.bg_color_class);
		comboBox_color_via->setValue(bgData.bg_color_via);
		comboBox_color_to->setValue(bgData.bg_color_to);
		comboBox_color->comboBox_gradient_step->setValue(bgData.bg_color_from_step);
		comboBox_color_via->comboBox_gradient_step->setValue(bgData.bg_color_via_step);
		comboBox_color_to->comboBox_gradient_step->setValue(bgData.bg_color_to_step);
		comboBox_color->comboBox_gradient_step->setHidden(false);
		comboBox_color_to->comboBox_gradient_step->setHidden(false);
		comboBox_color_via->comboBox_gradient_step->setHidden(false);
	}else {
		content_temp->setCondition("bg-gradient", false);
		comboBox_color->setValue(bgData.bg_color_class);
		comboBox_color->comboBox_gradient_step->setHidden(true);
		comboBox_color_to->comboBox_gradient_step->setHidden(true);
		comboBox_color_via->comboBox_gradient_step->setHidden(true);
	}

}

void ElementBackgroundWidget::resetStyles()
{
	comboBox_attachment->setValue();
	comboBox_clip->setValue();
	comboBox_origin->setValue();
	comboBox_position->setValue();
	comboBox_repeat->setValue();
	comboBox_size->setValue();
	comboBox_image->setValue();
	comboBox_color->setValue();

	
	comboBox_color_via->setValue();
	comboBox_color_to->setValue();
}

