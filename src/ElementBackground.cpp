#include "include/ElementBackground.h"
#include <regex>
#include <string>

ElementBackgroundWidget::ElementBackgroundWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig)
{

	setStyleClass("min-w-fit max-w-[300px] !border-x-0 text-center !bg-neutral-700 !text-neutral-200 relative");
	setTitle("Backgrounds");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-500");
	setCollapsible(true);
	content_temp = setCentralWidget(std::make_unique<Wt::WTemplate>(tr("stylus-background-template")));
	
	
	auto resetBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());
	auto testBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());

	std::string buttons_styles ="p-2 m-px bg-cover ";
	
	resetBtn->setStyleClass(buttons_styles + "bg-[url(resources/icons/refresh.svg)] !ml-auto");
	testBtn->setStyleClass(buttons_styles + "bg-[url(resources/icons/experimental-glass.svg)] !mr-2");

	resetBtn->clicked().connect([=](){ resetStyles(); styleChanged_.emit(); isCollapsed() ? expand() : collapse();});
	testBtn->clicked().connect([=](){ setCustomTestValues(); styleChanged_.emit(); isCollapsed() ? expand() : collapse(); });



	content_temp->bindString("color-title","Color");
	comboBox_attachment = content_temp->bindWidget("combobox-attachment", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->backgrounds.background_attachment));
	comboBox_clip = content_temp->bindWidget("combobox-clip", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->backgrounds.background_clip));
	comboBox_origin = content_temp->bindWidget("combobox-origin", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->backgrounds.background_origin));
	comboBox_position = content_temp->bindWidget("combobox-position", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->backgrounds.background_position));
	comboBox_repeat = content_temp->bindWidget("combobox-repeat", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->backgrounds.background_repeat));
	comboBox_size = content_temp->bindWidget("combobox-size", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->backgrounds.background_size));
	comboBox_image = content_temp->bindWidget("combobox-image", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->backgrounds.background_image));
	comboBox_color = content_temp->bindWidget("color-widget", std::make_unique<BackgroundColorWidget>(
		tailwindConfig->backgrounds.background_color, 
		tailwindConfig_->backgrounds.gradient_stops_from));
	comboBox_color_via = content_temp->bindWidget("combobox-color-via", std::make_unique<BackgroundColorWidget>(
		tailwindConfig_->backgrounds.background_color_via, 
		tailwindConfig_->backgrounds.gradient_stops_via));
	comboBox_color_to = content_temp->bindWidget("combobox-color-to", std::make_unique<BackgroundColorWidget>(
		tailwindConfig_->backgrounds.background_color_to, 
		tailwindConfig_->backgrounds.gradient_stops_to));

	// DISABLE GRADIENT BECAUSE IT NEEDS MORE WORK LATER AFTER IMLEMENTING COLORS IN OTHER PARTS 
	comboBox_image->disable(true);

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


	// comboBox_color->setStepOptions(colors.bg_gradient_step_from_classes);
	// comboBox_color_via->setStepOptions(colors.bg_gradient_step_via_classes);
	// comboBox_color_to->setStepOptions(colors.bg_gradient_step_to_classes);

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
				// comboBox_color->comboBox_color->setOptions(colors.bg_color_from_classes);
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
			// comboBox_color->comboBox_color->setOptions(colors.bg_color_classes);
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
		// comboBox_color->comboBox_color->setOptions(colors.bg_color_from_classes);
		// std::cout << " ---- ---------bgData.bg_color_from = " << bgData.bg_color_class << "\n";
		// std::cout << " ---- ---------bgData.bg_color_from_step = " << bgData.bg_color_from_step << "\n";
		// std::cout << " ---- ---------bgData.bg_color_via = " << bgData.bg_color_via << "\n";
		// std::cout << " ---- ---------bgData.bg_color_via_step = " << bgData.bg_color_via_step << "\n";
		// std::cout << " ---- ---------bgData.bg_color_to = " << bgData.bg_color_to << "\n";
		// std::cout << " ---- ---------bgData.bg_color_to_step = " << bgData.bg_color_to_step << "\n";
		comboBox_color->setValue(bgData.bg_color_class);
		comboBox_color_via->setValue(bgData.bg_color_via);
		comboBox_color_to->setValue(bgData.bg_color_to);
		// comboBox_color->comboBox_gradient_step->setValue(bgData.bg_color_from_step);
		// comboBox_color_via->comboBox_gradient_step->setValue(bgData.bg_color_via_step);
		// comboBox_color_to->comboBox_gradient_step->setValue(bgData.bg_color_to_step);
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

void ElementBackgroundWidget::setCustomTestValues()
{
	comboBox_attachment->setValue("bg-fixed");
	comboBox_clip->setValue("bg-clip-border");
	comboBox_origin->setValue("bg-origin-border");
	comboBox_position->setValue("bg-center");
	comboBox_repeat->setValue("bg-repeat");
	comboBox_size->setValue("bg-auto");
	comboBox_color->setValue("bg-red-500");
}
