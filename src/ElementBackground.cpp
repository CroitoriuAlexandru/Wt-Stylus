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
		"100", "95", "90", "85", "80", "75", "70", "65", "60", "55",
		"50", "45", "40", "35", "30", "25", "20", "15", "10", "5",
		"0"
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

	for(auto styleClass : def_classes){
		color_classes.push_back(styleClass);
	}
	color_classes.push_back("none");

	for(auto styleClass : colors){
		color_classes.push_back(styleClass);
	}

}



ElementBackgroundWidget::ElementBackgroundWidget(std::string templateName)
	: WDialog("Background")
{

	setModal(false);
	setResizable(false);
	setStyleClass("min-w-fit bg-neutral-700 text-neutral-400");
	titleBar()->clear();
	contents()->clear();
	BackgroundStyleClasses colors = BackgroundStyleClasses();

	content_temp = contents()->addWidget(std::make_unique<Wt::WTemplate>(Wt::WString::tr(templateName)));
	content_temp->bindString("color-title","Color");
	comboBox_attachment = content_temp->bindWidget("combobox-attachment", std::make_unique<ComboBoxClassWithCustoms>(colors.bg_attachment_classes));
	comboBox_clip = content_temp->bindWidget("combobox-clip", std::make_unique<ComboBoxClassWithCustoms>(colors.bg_clip_classes));
	comboBox_color = content_temp->bindWidget("color-widget", std::make_unique<ComboBoxColors>(colors.color_classes, colors.color_intensity, colors.color_opacity));
	comboBox_origin = content_temp->bindWidget("combobox-origin", std::make_unique<ComboBoxClassWithCustoms>(colors.bg_origin_classes));
	comboBox_position = content_temp->bindWidget("combobox-position", std::make_unique<ComboBoxClassWithCustoms>(colors.bg_position_classes));
	comboBox_repeat = content_temp->bindWidget("combobox-repeat", std::make_unique<ComboBoxClassWithCustoms>(colors.bg_repeat_classes));
	comboBox_size = content_temp->bindWidget("combobox-size", std::make_unique<ComboBoxClassWithCustoms>(colors.bg_size_classes));
	comboBox_image = content_temp->bindWidget("combobox-image", std::make_unique<ComboBoxClassWithCustoms>(colors.bg_image_classes));
	comboBox_color_via = content_temp->bindWidget("combobox-color-via", std::make_unique<ComboBoxColors>(colors.color_classes, colors.color_intensity, colors.color_opacity));
	comboBox_color_to = content_temp->bindWidget("combobox-color-to", std::make_unique<ComboBoxColors>(colors.color_classes, colors.color_intensity, colors.color_opacity));

	// set regular expresion for custom value w-[10px]
	comboBox_attachment->setCustomValueString("bg-");
	comboBox_clip->setCustomValueString("bg-clip-");
	comboBox_color->setCustomValueString("bg-");
	comboBox_origin->setCustomValueString("bg-origin-");
	comboBox_position->setCustomValueString("bg-");
	comboBox_repeat->setCustomValueString("bg-");
	comboBox_size->setCustomValueString("bg-");
	comboBox_image->setCustomValueString("bg-");
	comboBox_color_via->setCustomValueString("via-");
	comboBox_color_to->setCustomValueString("to-");


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
	comboBox_color->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_origin->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_position->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_repeat->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_size->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_image->classChanged().connect([=](){ 
		auto value = comboBox_image->getValue();
		// background_image_regex
		if(comboBox_image->comboBox_class->currentIndex() != 0){
			content_temp->setCondition("bg-gradient", true);
			content_temp->bindString("color-title", "From");
		}else {
			content_temp->setCondition("bg-gradient", false);
			content_temp->bindString("color-title", "Color");
		}
		styleChanged_.emit(); 
		});
	comboBox_color_via->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_color_to->classChanged().connect([=](){ styleChanged_.emit(); });
};

std::string ElementBackgroundWidget::getStyles()
{
	std::string elementClasses;
	auto imageGradient = comboBox_image->getValue();
	if(imageGradient.compare("none") != 0){ elementClasses += comboBox_image->getValue() + " "; }
	if(comboBox_color->getValue().compare("none") != 0){ 
		auto style = comboBox_color->getValue();
		// replace bg with from
		if(imageGradient.compare("none") != 0){
			style = std::regex_replace(style, std::regex("bg-"), "from-");
		}
		elementClasses += style + " ";
	}
	if(comboBox_color_via->getValue().compare("none") != 0){ 
		auto style = comboBox_color_via->getValue();
		// replace bg with via
		style = std::regex_replace(style, std::regex("bg-"), "via-");
		elementClasses += style + " ";
	}
	if(comboBox_color_to->getValue().compare("none") != 0){ 
		auto style = comboBox_color_to->getValue();
		// replace bg with to
		style = std::regex_replace(style, std::regex("bg-"), "to-");
		elementClasses += style + " ";
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

	comboBox_attachment->setValue(bgData.bg_attachment);
	comboBox_clip->setValue(bgData.bg_clip);
	comboBox_color->setValue(bgData.bg_color_class);
	comboBox_origin->setValue(bgData.bg_origin);
	comboBox_position->setValue(bgData.bg_position);
	comboBox_repeat->setValue(bgData.bg_repeat);
	comboBox_size->setValue(bgData.bg_size);
	comboBox_image->setValue(bgData.bg_image);


	if(bgData.bg_image != ""){
		content_temp->bindString("color-title", "From");
		comboBox_color->setValue(bgData.bg_color_class);
		comboBox_color_via->setValue(bgData.bg_color_via);
		comboBox_color_to->setValue(bgData.bg_color_to);
		std::cout << "bgData.bg_color_from = " << bgData.bg_color_class << "\n";
		std::cout << "bgData.bg_color_via = " << bgData.bg_color_via << "\n";
		std::cout << "bgData.bg_color_to = " << bgData.bg_color_to << "\n";
	}

}

void ElementBackgroundWidget::resetStyles()
{
	comboBox_attachment->setValue();
	comboBox_clip->setValue();
	comboBox_color->setValue();
	comboBox_origin->setValue();
	comboBox_position->setValue();
	comboBox_repeat->setValue();
	comboBox_size->setValue();
	comboBox_image->setValue();
	
	comboBox_color_via->setValue();
	comboBox_color_to->setValue();
}

