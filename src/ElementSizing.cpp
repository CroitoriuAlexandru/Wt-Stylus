#include "include/ElementSizing.h"
#include <regex>


SizingStyleClasses::SizingStyleClasses()

{
	sizingSize = { 
		"screen", "0", "px", "0.5", "1", "1.5", "2", "2.5", "3", "3.5", "4",
		"5", "6", "7", "8", "9", 
		"10", "11", "12", "14", "16", "20", "24", "28", "32", "36", "40", "44", "48", "52", "56", "60", "64", "72", "80", "96", 
		"fit", "min", "max", "auto", "full",
		"1/2", 
		"2/3", "1/3",
		"1/4", "2/4", "3/4",
		"1/5", "2/5", "3/5", "4/5",
		"1/6", "2/6", "3/6", "4/6", "5/6"
	};
	extraSizingWidth = {"1/12", "2/12", "3/12", "4/12", "5/12", "6/12", "7/12", "8/12", "9/12", "10/12", "11/12"};

	// we have min width and height togather because they are the same except that max-height has the min-height-screen class
	minSizing = {
		"0", "full", "min", "max", "fit"
	};

	maxWidthSizing = {
		"0", "xs", "sm", "md", "lg", "xl", "2xl", "3xl", "4xl", "5xl", "6xl", "7xl", "full", "min", "max", "fit", "prose", "none", 
		"screen-sm", "screen-md", "screen-lg", "screen-xl", "screen-2x"
	};

	maxHeightSizing = {
		"0", "px", "0.5", "1", "1.5", "2", "2.5", "3", "3.5", "4",
		"5", "6", "7", "8", "9", "10", "11", "12", "14", "16", "20", "24", "28", "32", "36", "40", "44", "48", "52", "56", "60", "64", "72", "80", "96",
		"none", "full", "screen", "min", "max", "fit"
	};

	// width and height classes
	// width_classes.push_back("none");
	// height_classes.push_back("none");
	for (auto& size : sizingSize) {
		width_classes.push_back("w-" + size);
		height_classes.push_back("h-" + size);
		if(size.compare("full") == 0){
			width_classes.push_back("none");
			height_classes.push_back("none");
		}
	}

	for(auto& size : extraSizingWidth){
		width_classes.push_back("w-" + size);
	}

	// min width and height classes
	min_width_classes.push_back("none");
	min_height_classes.push_back("none");
	for (auto& size : minSizing) {

		min_width_classes.push_back("min-w-" + size);
		min_height_classes.push_back("min-h-" + size);
	}
	min_height_classes.push_back("min-h-screen");

	// max width and height classes
	max_width_classes.push_back("none");
	for(auto& size : maxWidthSizing){
		max_width_classes.push_back("max-w-" + size);
	}

	max_height_classes.push_back("none");
	for(auto& size : maxHeightSizing){
		max_height_classes.push_back("max-h-" + size);
	}

	std::cout << "\n\n";

	// std::cout << "width classes:\n ";
	// for (auto& widthClass : width_classes) {
	// 	std::cout << widthClass << " ";
	// }
	// std::cout << "\n\nmin width classes:\n ";
	// for(auto& minWidthClass : min_width_classes){
	// 	std::cout << minWidthClass << " ";
	// }
	// std::cout << "\n\nmax width classes: \n";
	// for(auto& maxWidthClass : max_width_classes){
	// 	std::cout << maxWidthClass << " ";
	// }
	// std::cout << "\n\nheight classes: \n";
	// for (auto& heightClass : height_classes) {
	// 	std::cout << heightClass << " ";
	// }
	// std::cout << "\n\nmin height classes: \n";
	// for(auto& minHeightClass : min_height_classes){
	// 	std::cout << minHeightClass << " ";
	// }
	// std::cout << "\n\nmax height classes: \n";
	// for(auto& maxHeightClass : max_height_classes){
	// 	std::cout << maxHeightClass << " ";
	// }
	// std::cout << "\n\n";

};

ElementSizingWidget::ElementSizingWidget(std::string templateName)
	: WDialog("Sizing")
{
	setModal(false);
	setResizable(false);
	setStyleClass("min-w-fit bg-neutral-700 text-neutral-400");

	titleBar()->clear();
	contents()->clear();

	auto content_temp = titleBar()->addWidget(std::make_unique<Wt::WTemplate>(Wt::WString::tr(templateName)));

	width_widget_ = content_temp->bindWidget("width.control", std::make_unique<ComboBoxClassWithCustoms>());
	height_widget_ = content_temp->bindWidget("height.control", std::make_unique<ComboBoxClassWithCustoms>());

	minWidth_widget_ = content_temp->bindWidget("width.min.control", std::make_unique<ComboBoxClassWithCustoms>());
	minHeight_widget_ = content_temp->bindWidget("height.min.control", std::make_unique<ComboBoxClassWithCustoms>());

	maxWidth_widget_ = content_temp->bindWidget("width.max.control", std::make_unique<ComboBoxClassWithCustoms>());
	maxHeight_widget_ = content_temp->bindWidget("height.max.control", std::make_unique<ComboBoxClassWithCustoms>());

	// set syzes for comboboxes
	width_widget_->comboBox_class->addStyleClass("!w-[60px]");
	height_widget_->comboBox_class->addStyleClass("!w-[60px]");
	minWidth_widget_->comboBox_class->addStyleClass("!w-[60px]");
	minHeight_widget_->comboBox_class->addStyleClass("!w-[60px]");
	maxWidth_widget_->comboBox_class->addStyleClass("!w-[60px]");
	maxHeight_widget_->comboBox_class->addStyleClass("!w-[60px]");


	// set regular expresion for custom value w-[10px]
	width_widget_->setCustomValueString("w-");
	height_widget_->setCustomValueString("h-");

	minWidth_widget_->setCustomValueString("min-w-");
	minHeight_widget_->setCustomValueString("min-h-");

	maxWidth_widget_->setCustomValueString("max-w-");
	maxHeight_widget_->setCustomValueString("max-h-");

	// set combo box values
	width_widget_->setComboBoxValues(sizingClasses_.width_classes);
	height_widget_->setComboBoxValues(sizingClasses_.height_classes);
	
	minWidth_widget_->setComboBoxValues(sizingClasses_.min_width_classes);
	minHeight_widget_->setComboBoxValues(sizingClasses_.min_height_classes);

	maxWidth_widget_->setComboBoxValues(sizingClasses_.max_width_classes);
	maxHeight_widget_->setComboBoxValues(sizingClasses_.max_height_classes);


	// signals for default classes for tailwind
	width_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	height_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });

	minWidth_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	minHeight_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });

	maxWidth_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	maxHeight_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
};

std::string ElementSizingWidget::getStyles()
{
	std::string elementClasses;

	if(width_widget_->getValue().compare("none") != 0){ elementClasses += width_widget_->getValue() + " "; }
	if(minWidth_widget_->getValue().compare("none") != 0){ elementClasses += minWidth_widget_->getValue() + " "; }
	if(maxWidth_widget_->getValue().compare("none") != 0){ elementClasses += maxWidth_widget_->getValue() + " "; }
	 
	if(height_widget_->getValue().compare("none") != 0){ elementClasses += height_widget_->getValue() + " "; }
	if(minHeight_widget_->getValue().compare("none") != 0){ elementClasses += minHeight_widget_->getValue() + " "; }
	if(maxHeight_widget_->getValue().compare("none") != 0){ elementClasses += maxHeight_widget_->getValue() + " "; }

	return elementClasses;
}

void ElementSizingWidget::setClasses(SizingData sizing)
{
	resetStyles();
	// std::cout << "Element S I Z I N G Widget setStyleClasses -----------------------------------------\n";
	if(sizing.width.compare("") != 0) width_widget_->setValue(sizing.width);
	if(sizing.minWidth.compare("") != 0) minWidth_widget_->setValue(sizing.minWidth);
	if(sizing.maxWidth.compare("") != 0) maxWidth_widget_->setValue(sizing.maxWidth);

	if(sizing.height.compare("") != 0) height_widget_->setValue(sizing.height);
	if(sizing.minHeight.compare("") != 0) minHeight_widget_->setValue(sizing.minHeight);
	if(sizing.maxHeight.compare("") != 0) maxHeight_widget_->setValue(sizing.maxHeight);
}

void ElementSizingWidget::resetStyles()
{
	width_widget_->setValue();
	minWidth_widget_->setValue();
	maxWidth_widget_->setValue();

	height_widget_->setValue();
	minHeight_widget_->setValue();
	maxHeight_widget_->setValue();
}

