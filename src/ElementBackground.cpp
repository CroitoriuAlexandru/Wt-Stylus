#include "include/ElementBackground.h"
#include <regex>
#include <string>

ElementBackgroundWidget::ElementBackgroundWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig),
	gradient_group(std::make_shared<Wt::WButtonGroup>())
{

	setStyleClass("min-w-fit max-w-[300px] !border-x-0 !bg-neutral-700 !text-neutral-200 !border-neutral-900 px-1.5");
	setTitle("Backgrounds");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-900");
	setCollapsible(true);
	// content_temp = setCentralWidget(std::make_unique<Wt::WTemplate>(tr("stylus-background-template")));
	
	
	auto resetBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());
	auto testBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());

	std::string iconStyles ="p-2 m-px bg-cover ";
	
	resetBtn->setStyleClass(iconStyles + "bg-[url(resources/icons/refresh.svg)] !ml-auto");
	testBtn->setStyleClass(iconStyles + "bg-[url(resources/icons/experimental-glass.svg)] !mr-2");

	resetBtn->clicked().connect([=](){ resetStyles(); styleChanged_.emit(); isCollapsed() ? expand() : collapse();});
	testBtn->clicked().connect([=](){ setCustomTestValues(); styleChanged_.emit(); isCollapsed() ? expand() : collapse(); });

	auto centralWidget = setCentralWidget(std::make_unique<Wt::WContainerWidget>());

	centralWidget->setStyleClass("flex flex-col w-full max-w-[300px]");


	auto gratient_wrapper = centralWidget->addWidget(std::make_unique<Wt::WGroupBox>("Gradient"));
	gratient_wrapper->setStyleClass("flex justify-start border border-solid pb-1 border-neutral-900");

	for(int index = 0; index < tailwindConfig->backgrounds.background_image.styleClasses_.size(); ++index){
		auto btn = gratient_wrapper->addWidget(std::make_unique<Wt::WRadioButton>(""));
		// get the text after the last -
		std::string gradient_name = tailwindConfig->backgrounds.background_image.styleClasses_[index].className_;
		std::string gradient_direction = gradient_name.substr(gradient_name.find_last_of("-")+1);

		btn->setStyleClass("flex w-fit h-fit cursor-pointer m-px mx-0.5 p-px");
		btn->addStyleClass("[&>span]:bg-cover [&>input]:hidden [&>span]:p-2.5 [&>span]:m-px [&>span]:rounded-md");
		btn->addStyleClass("[&>span]:bg-neutral-500 [&>span]:hover:bg-neutral-400 [&>input:checked_+_span]:bg-neutral-400 ");
		std::string tooltip_text;
		if(gradient_direction.compare("tl") == 0){
			tooltip_text = "To Top Left";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-left-up.svg)]");
		}else if (gradient_direction.compare("tr") == 0){
			tooltip_text = "To Top Right";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-right-up.svg)]");
		}else if (gradient_direction.compare("bl") == 0){
			tooltip_text = "To Bottom Left";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-left-down.svg)]");
		}else if (gradient_direction.compare("br") == 0){
			tooltip_text = "To Bottom Right";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-right-down.svg)]");
		}else if (gradient_direction.compare("t") == 0){
			tooltip_text = "To Top";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-up.svg)]");
		}else if (gradient_direction.compare("b") == 0){
			tooltip_text = "To Bottom";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-down.svg)]");
		}else if (gradient_direction.compare("l") == 0){
			tooltip_text = "To Left";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-left.svg)]");
		}else if (gradient_direction.compare("r") == 0){
			tooltip_text = "To Right";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-right.svg)]");
		}else if (gradient_name.compare("bg-none") == 0){
			btn->addStyleClass("[&>span]:!p-0.5 mr-auto text-xs [&>span]:bg-neutral-900 [&>span]:hover:bg-neutral-800 text-white [&>input:checked_+_span]:bg-neutral-400 [&>span]:text-center");
			tooltip_text = "No Background";
			btn->setText("bg none");
		}else {
			tooltip_text = "No style class applied";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] ");
		}
		btn->setToolTip(Wt::WString().tr("tooltip-styleClasses").arg(tooltip_text).arg(gradient_name), Wt::TextFormat::UnsafeXHTML);
		gradient_group->addButton(btn, index);
	}

	gradient_group->checkedChanged().connect(this, [=](){
		std::cout << "\n\n gradient changed to : <" << tailwindConfig->backgrounds.background_image.styleClasses_[gradient_group->checkedId()].className_ << ">\n\n";
		styleChanged_.emit();
	});


	comboBox_image = centralWidget->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig->backgrounds.background_image));
	comboBox_color = centralWidget->addWidget(std::make_unique<ColorsComboBox>(tailwindConfig->backgrounds.background_color));
	comboBox_color_from = centralWidget->addWidget(std::make_unique<ColorsComboBox>(tailwindConfig->backgrounds.background_color_from));
	comboBox_color_via = centralWidget->addWidget(std::make_unique<ColorsComboBox>(tailwindConfig->backgrounds.background_color_via));
	comboBox_color_to = centralWidget->addWidget(std::make_unique<ColorsComboBox>(tailwindConfig->backgrounds.background_color_to));

	comboBox_attachment = centralWidget->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig->backgrounds.background_attachment));
	comboBox_clip = centralWidget->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig->backgrounds.background_clip));
	comboBox_origin = centralWidget->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig->backgrounds.background_origin));
	comboBox_position = centralWidget->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig->backgrounds.background_position));
	comboBox_repeat = centralWidget->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig->backgrounds.background_repeat));
	comboBox_size = centralWidget->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig->backgrounds.background_size));

	comboBox_color->title->setText("Bg Color");
	comboBox_color_from->title->setText("From");
	comboBox_color_via->title->setText("Via");
	comboBox_color_to->title->setText("To");

	// set regular expresion for custom value w-[10px]
	comboBox_attachment->setCustomValueString("bg-");
	comboBox_clip->setCustomValueString("bg-clip-");
	comboBox_origin->setCustomValueString("bg-origin-");
	comboBox_position->setCustomValueString("bg-");
	comboBox_repeat->setCustomValueString("bg-");
	comboBox_size->setCustomValueString("bg-");
	comboBox_image->setCustomValueString("bg-");
	comboBox_color->setCustomValueString("bg-");
	comboBox_color_from->setCustomValueString("from-");
	comboBox_color_via->setCustomValueString("via-");
	comboBox_color_to->setCustomValueString("to-");

	// signals for default classes for tailwind
	comboBox_attachment->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_clip->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_origin->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_position->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_repeat->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_size->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_image->classChanged().connect([=](){ 
			if(comboBox_image->getValue().compare("none") == 0 || comboBox_image->getValue().compare("bg-none") == 0){
				comboBox_color->show();
				comboBox_color_from->hide();
				comboBox_color_via->hide();
				comboBox_color_to->hide();
			}else 
			{
				comboBox_color->hide();
				comboBox_color_from->show();
				comboBox_color_via->show();
				comboBox_color_to->show();
			}
			styleChanged_.emit();
		});
	comboBox_color->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_color_from->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_color_via->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_color_to->classChanged().connect([=](){ styleChanged_.emit(); });
};

std::string ElementBackgroundWidget::getStyles()
{
	bool activeClasses = false;
	std::string elementClasses;
	gradient_group->checkedId();
	std::string gradient_name = tailwindConfig_->backgrounds.background_image.styleClasses_[gradient_group->checkedId()].className_;
	if(gradient_name.compare("none") != 0){
		activeClasses = true; 
		elementClasses += comboBox_image->getValue() + " ";
		if(comboBox_color_from->getValue().compare("none") != 0){ elementClasses += comboBox_color_from->getValue() + " "; }
		if(comboBox_color_via->getValue().compare("none") != 0){ elementClasses += comboBox_color_via->getValue() + " "; }
		if(comboBox_color_to->getValue().compare("none") != 0){ elementClasses += comboBox_color_to->getValue() + " "; }
	}else {
		if(comboBox_color->getValue().compare("none") != 0){ elementClasses += comboBox_color->getValue() + " "; activeClasses = true; }
	}
	if(comboBox_attachment->getValue().compare("none") != 0){ elementClasses += comboBox_attachment->getValue() + " "; activeClasses = true; }
	if(comboBox_clip->getValue().compare("none") != 0){ elementClasses += comboBox_clip->getValue() + " "; activeClasses = true; }
	if(comboBox_origin->getValue().compare("none") != 0){ elementClasses += comboBox_origin->getValue() + " "; activeClasses = true; }
	if(comboBox_position->getValue().compare("none") != 0){ elementClasses += comboBox_position->getValue() + " "; activeClasses = true; }
	if(comboBox_repeat->getValue().compare("none") != 0){ elementClasses += comboBox_repeat->getValue() + " "; activeClasses = true; }
	if(comboBox_size->getValue().compare("none") != 0){ elementClasses += comboBox_size->getValue() + " "; activeClasses = true; }

	// if(activeClasses) expand();
	// else collapse();
	
	return elementClasses;
}

int ElementBackgroundWidget::getIndesOfStringInVector(std::string str, std::vector<StyleClass> vec){
	for(int index = 0; index < vec.size(); ++index){
		if(vec[index].className_.compare(str) == 0) return index;
	}
	return 0;
}


void ElementBackgroundWidget::setClasses(BackgroundData bgData)
{
	bool activeClasses = false;
	resetStyles();

	// comboBox_color->comboBox_color->setOptions(colors.bg_color_from_classes);
	std::cout << " ---- ---------bgData.bg_image = <" << bgData.bg_image << ">\n";
	// std::cout << " ---- ---------bgData.bg_color_from = <" << bgData.bg_color_class << ">\n";
	// std::cout << " ---- ---------bgData.bg_color_from_step = " << bgData.bg_color_from_step << "\n";
	// std::cout << " ---- ---------bgData.bg_color_via = " << bgData.bg_color_via << "\n";
	// std::cout << " ---- ---------bgData.bg_color_via_step = " << bgData.bg_color_via_step << "\n";
	// std::cout << " ---- ---------bgData.bg_color_to = " << bgData.bg_color_to << "\n";
	// std::cout << " ---- ---------bgData.bg_color_to_step = " << bgData.bg_color_to_step << "\n";

	if(bgData.bg_image.compare("none") != 0){
		int gradientIndex = getIndesOfStringInVector(bgData.bg_image, tailwindConfig_->backgrounds.background_image.styleClasses_);
		if(gradientIndex != 0){ gradient_group->button(gradientIndex)->setChecked(true); }

		if(bgData.bg_color_class.compare("none") != 0) {comboBox_color->setValue(bgData.bg_color_class); }
		if(bgData.bg_color_from.compare("none") != 0) comboBox_color_from->setValue(bgData.bg_color_from);
		if(bgData.bg_color_via.compare("none") != 0) comboBox_color_via->setValue(bgData.bg_color_via);
		if(bgData.bg_color_to.compare("none") != 0) comboBox_color_to->setValue(bgData.bg_color_to);
		if(bgData.bg_color_from_step.compare("none") != 0) comboBox_color_from->setValue(bgData.bg_color_from_step);
		if(bgData.bg_color_via_step.compare("none") != 0) comboBox_color_via->setValue(bgData.bg_color_via_step);
		if(bgData.bg_color_to_step.compare("none") != 0) comboBox_color_to->setValue(bgData.bg_color_to_step);
		
		comboBox_color->hide();
		comboBox_color_from->show();
		comboBox_color_via->show();
		comboBox_color_to->show();
	} else {
		activeClasses = true;

		comboBox_color->setValue(bgData.bg_color_class);
		comboBox_color_from->setValue("none");
		comboBox_color_via->setValue("none");
		comboBox_color_to->setValue("none");
		comboBox_color->show();
		comboBox_color_from->hide();
		comboBox_color_via->hide();
		comboBox_color_to->hide();

	}

	if(bgData.bg_attachment.compare("none") != 0) { comboBox_attachment->setValue(bgData.bg_attachment); activeClasses = true; }
	if(bgData.bg_clip.compare("none") != 0) { comboBox_clip->setValue(bgData.bg_clip); activeClasses = true; }
	if(bgData.bg_origin.compare("none") != 0) { comboBox_origin->setValue(bgData.bg_origin); activeClasses = true; }
	if(bgData.bg_position.compare("none") != 0) { comboBox_position->setValue(bgData.bg_position); activeClasses = true; }
	if(bgData.bg_repeat.compare("none") != 0) { comboBox_repeat->setValue(bgData.bg_repeat); activeClasses = true; }
	if(bgData.bg_size.compare("none") != 0) { comboBox_size->setValue(bgData.bg_size); activeClasses = true; }


	if(activeClasses) expand();
	else collapse();
}

void ElementBackgroundWidget::resetStyles()
{
	gradient_group->button(0)->setChecked(true);
	comboBox_attachment->setValue("none");
	comboBox_clip->setValue("none");
	comboBox_origin->setValue("none");
	comboBox_position->setValue("none");
	comboBox_repeat->setValue("none");
	comboBox_size->setValue("none");
	comboBox_image->setValue("none");
	comboBox_color->setValue("none");

	comboBox_color_from->setValue("none");
	comboBox_color_via->setValue("none");
	comboBox_color_to->setValue("none");
}

void ElementBackgroundWidget::setCustomTestValues()
{
	gradient_group->button(5)->setChecked(true);
	comboBox_attachment->setValue("bg-fixed");
	comboBox_clip->setValue("bg-clip-border");
	comboBox_origin->setValue("bg-origin-border");
	comboBox_position->setValue("bg-center");
	comboBox_repeat->setValue("bg-repeat");
	comboBox_size->setValue("bg-auto");
	comboBox_color->setValue("bg-red-500");
}
