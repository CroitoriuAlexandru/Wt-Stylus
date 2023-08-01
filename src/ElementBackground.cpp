#include "include/ElementBackground.h"
#include <regex>
#include <string>

BackgroundStyleClasses::BackgroundStyleClasses() {
	auto normal_classes = {
		"inherit", "current", "transparent", "black", "white"
	};

	auto color_classes = {
		"slate", "gray", "zinc", "neutral", "stone", "red", "orange", "amber", "yellow", "lime", "green", "emerald", "teal", "cyan", "sky", "blue", "indigo", "violet", "purple", "fuchsia", "pink", "rose"
	};

	color_intensity = {
		"50", "100", "200", "300", "400", "500", "600", "700", "800", "900", "950"
	};

	opacity = {
		"0", "5", "10", "15", "20", "25", "30", "35", "40", "45", 
		"50", "55", "60", "65", "70", "75", "80", "85", "90", "95", 
		"100"
	};


	for(auto styleClass : normal_classes){
		color_classes_.push_back(styleClass);
	}
	color_classes_.push_back("none");
	for(auto styleClass : color_classes){
		color_classes_.push_back(styleClass);
	}

}


ElementBackgroundWidget::ElementBackgroundWidget(std::string templateName)
	: WDialog("Background")
{

	setModal(false);
	setResizable(false);
	setStyleClass("min-w-fit bg-neutral-700 transition-spacing duration-300 ease-in-out text-neutral-400 flex flex-col justify-start items-stretch");

	contents()->setStyleClass("pb-1");
	titleBar()->setStyleClass("cursor-pointer text-center text-md text-neutral-300");

	auto content_temp = contents()->addWidget(std::make_unique<Wt::WTemplate>(Wt::WString::tr(templateName)));

	comboBox_color = content_temp->bindWidget("test-colors-widget", std::make_unique<ComboBoxColors>());

	// set regular expresion for custom value w-[10px]
	comboBox_color->setCustomValueString("bg-");

	// set combo box values
	BackgroundStyleClasses colors = BackgroundStyleClasses();
	comboBox_color->setComboBoxValues(colors.color_classes_);

	// comboBox_color->setComboBoxValues(colors.color_classes_);

	// signals for default classes for tailwind
	comboBox_color->classChanged().connect([=](){ styleChanged_.emit(); });
};

std::string ElementBackgroundWidget::getStyles()
{
	std::string elementClasses;

	if(comboBox_color->getValue().compare("none") != 0){ elementClasses += comboBox_color->getValue() + " "; }

	// if(width_widget_->getValue().compare("none") != 0){ elementClasses += width_widget_->getValue() + " "; }
	// if(minWidth_widget_->getValue().compare("none") != 0){ elementClasses += minWidth_widget_->getValue() + " "; }
	// if(maxWidth_widget_->getValue().compare("none") != 0){ elementClasses += maxWidth_widget_->getValue() + " "; }
	 
	// if(height_widget_->getValue().compare("none") != 0){ elementClasses += height_widget_->getValue() + " "; }
	// if(minHeight_widget_->getValue().compare("none") != 0){ elementClasses += minHeight_widget_->getValue() + " "; }
	// if(maxHeight_widget_->getValue().compare("none") != 0){ elementClasses += maxHeight_widget_->getValue() + " "; }

	return elementClasses;
}

void ElementBackgroundWidget::setClasses(std::vector<std::string> styleClasses)
{
	resetStyles();
	
	// std::cout << "Element S I Z I N G Widget setStyleClasses -----------------------------------------\n";
	// if(sizing.width.compare("") != 0) width_widget_->setValue(sizing.width);
	// if(sizing.minWidth.compare("") != 0) minWidth_widget_->setValue(sizing.minWidth);
	// if(sizing.maxWidth.compare("") != 0) maxWidth_widget_->setValue(sizing.maxWidth);

	// if(sizing.height.compare("") != 0) height_widget_->setValue(sizing.height);
	// if(sizing.minHeight.compare("") != 0) minHeight_widget_->setValue(sizing.minHeight);
	// if(sizing.maxHeight.compare("") != 0) maxHeight_widget_->setValue(sizing.maxHeight);
}

void ElementBackgroundWidget::resetStyles()
{
	// width_widget_->setValue();
	// minWidth_widget_->setValue();
	// maxWidth_widget_->setValue();

	// height_widget_->setValue();
	// minHeight_widget_->setValue();
	// maxHeight_widget_->setValue();
}

