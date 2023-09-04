#include "include/ElementLayout.h"
#include <regex>
#include <string>
#include <Wt/WPopupMenu.h>
#include <Wt/WMenuItem.h>

ElementLayoutWidget::ElementLayoutWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig)
{


	setStyleClass("min-w-fit max-w-[300px] !border-x-0 !bg-neutral-700 !text-neutral-200 !border-neutral-900 px-1.5");
	setTitle("Layout");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-900 bg-neutral-800 ");
	setCollapsible(true);
	auto centralWidget = setCentralWidget(std::make_unique<Wt::WContainerWidget>());
	centralWidget->setStyleClass("flex flex-col w-full max-w-[300px]");

	// popup widget
	{
		auto popupMenu = std::make_unique<Wt::WPopupMenu>();
		std::string menuItemsStyles = "p-2 m-1 hover:bg-neutral-800 hover:text-neutral-200";
		popupMenu->addItem("set test classes")->setStyleClass(menuItemsStyles);
		popupMenu->addItem("reset styles")->setStyleClass(menuItemsStyles);
		popupMenu->addSeparator()->setStyleClass("border border-solid border-neutral-900");

		auto aspect_ratio_info = popupMenu->addItem("Info Aspect ratio");
		auto container_info = popupMenu->addItem("Info Container");
		auto columns_info = popupMenu->addItem("Info Columns");
		auto break_after_info = popupMenu->addItem("Info Break after");
		auto break_before_info = popupMenu->addItem("Info Break before");
		auto break_inside_info = popupMenu->addItem("Info Break inside");
		auto box_decoration_break_info = popupMenu->addItem("Info Box decoration break");
		auto box_sizing_info = popupMenu->addItem("Info Box sizing");
		auto display_info = popupMenu->addItem("Info Display");
		auto floats_info = popupMenu->addItem("Info Floats");
		auto clear_info = popupMenu->addItem("Info Clear");
		auto isolation_info = popupMenu->addItem("Info Isolation");
		auto object_fit_info = popupMenu->addItem("Info Object fit");
		auto object_position_info = popupMenu->addItem("Info Object position");
		auto overflow_info = popupMenu->addItem("Info Overflow");
		auto overflow_x_info = popupMenu->addItem("Info Overflow x");
		auto overflow_y_info = popupMenu->addItem("Info Overflow y");
		auto overscroll_behavior_info = popupMenu->addItem("Info Overscroll behavior");
		auto position_info = popupMenu->addItem("Info Position");
		auto position_top_left_bottom_right = popupMenu->addItem("Info Position T L B R");
		auto visibility_info = popupMenu->addItem("Info Visibility");
		auto z_index_info = popupMenu->addItem("Info Z index");

		aspect_ratio_info->setStyleClass(menuItemsStyles);
		container_info->setStyleClass(menuItemsStyles);
		columns_info->setStyleClass(menuItemsStyles);
		break_after_info->setStyleClass(menuItemsStyles);
		break_before_info->setStyleClass(menuItemsStyles);
		break_inside_info->setStyleClass(menuItemsStyles);
		box_decoration_break_info->setStyleClass(menuItemsStyles);
		box_sizing_info->setStyleClass(menuItemsStyles);
		display_info->setStyleClass(menuItemsStyles);
		floats_info->setStyleClass(menuItemsStyles);
		clear_info->setStyleClass(menuItemsStyles);
		isolation_info->setStyleClass(menuItemsStyles);
		object_fit_info->setStyleClass(menuItemsStyles);
		object_position_info->setStyleClass(menuItemsStyles);
		overflow_info->setStyleClass(menuItemsStyles);
		overflow_x_info->setStyleClass(menuItemsStyles);
		overflow_y_info->setStyleClass(menuItemsStyles);
		overscroll_behavior_info->setStyleClass(menuItemsStyles);
		position_info->setStyleClass(menuItemsStyles);
		position_top_left_bottom_right->setStyleClass(menuItemsStyles);
		visibility_info->setStyleClass(menuItemsStyles);
		z_index_info->setStyleClass(menuItemsStyles);

		Wt::WLink aspect_ratio_link = Wt::WLink(tailwindConfig_->layout.aspect_ratio.docsLink_);
		Wt::WLink container_link = Wt::WLink(tailwindConfig_->layout.container.docsLink_);
		Wt::WLink columns_link = Wt::WLink(tailwindConfig_->layout.columns.docsLink_);
		Wt::WLink break_after_link = Wt::WLink(tailwindConfig_->layout.break_after.docsLink_);
		Wt::WLink break_before_link = Wt::WLink(tailwindConfig_->layout.break_before.docsLink_);
		Wt::WLink break_inside_link = Wt::WLink(tailwindConfig_->layout.break_inside.docsLink_);
		Wt::WLink box_decoration_break_link = Wt::WLink(tailwindConfig_->layout.box_decoration_break.docsLink_);
		Wt::WLink box_sizing_link = Wt::WLink(tailwindConfig_->layout.box_sizing.docsLink_);
		Wt::WLink display_link = Wt::WLink(tailwindConfig_->layout.display.docsLink_);
		Wt::WLink floats_link = Wt::WLink(tailwindConfig_->layout.floats.docsLink_);
		Wt::WLink clear_link = Wt::WLink(tailwindConfig_->layout.clear.docsLink_);
		Wt::WLink isolation_link = Wt::WLink(tailwindConfig_->layout.isolation.docsLink_);
		Wt::WLink object_fit_link = Wt::WLink(tailwindConfig_->layout.object_fit.docsLink_);
		Wt::WLink object_position_link = Wt::WLink(tailwindConfig_->layout.object_position.docsLink_);
		Wt::WLink overflow_link = Wt::WLink(tailwindConfig_->layout.overflow.docsLink_);
		Wt::WLink overflow_x_link = Wt::WLink(tailwindConfig_->layout.overflow_x.docsLink_);
		Wt::WLink overflow_y_link = Wt::WLink(tailwindConfig_->layout.overflow_y.docsLink_);
		Wt::WLink overscroll_behavior_link = Wt::WLink(tailwindConfig_->layout.overscroll_behavior.docsLink_);
		Wt::WLink position_link = Wt::WLink(tailwindConfig_->layout.position.docsLink_);
		Wt::WLink position_top_left_bottom_right_link = Wt::WLink(tailwindConfig_->layout.position_bottom.docsLink_);
		Wt::WLink visibility_link = Wt::WLink(tailwindConfig_->layout.visibility.docsLink_);
		Wt::WLink z_index_link = Wt::WLink(tailwindConfig_->layout.z_index.docsLink_);

		aspect_ratio_link.setTarget(Wt::LinkTarget::NewWindow);
		container_link.setTarget(Wt::LinkTarget::NewWindow);
		columns_link.setTarget(Wt::LinkTarget::NewWindow);
		break_after_link.setTarget(Wt::LinkTarget::NewWindow);
		break_before_link.setTarget(Wt::LinkTarget::NewWindow);
		break_inside_link.setTarget(Wt::LinkTarget::NewWindow);
		box_decoration_break_link.setTarget(Wt::LinkTarget::NewWindow);
		box_sizing_link.setTarget(Wt::LinkTarget::NewWindow);
		display_link.setTarget(Wt::LinkTarget::NewWindow);
		floats_link.setTarget(Wt::LinkTarget::NewWindow);
		clear_link.setTarget(Wt::LinkTarget::NewWindow);
		isolation_link.setTarget(Wt::LinkTarget::NewWindow);
		object_fit_link.setTarget(Wt::LinkTarget::NewWindow);
		object_position_link.setTarget(Wt::LinkTarget::NewWindow);
		overflow_link.setTarget(Wt::LinkTarget::NewWindow);
		overflow_x_link.setTarget(Wt::LinkTarget::NewWindow);
		overflow_y_link.setTarget(Wt::LinkTarget::NewWindow);
		overscroll_behavior_link.setTarget(Wt::LinkTarget::NewWindow);
		position_link.setTarget(Wt::LinkTarget::NewWindow);
		position_top_left_bottom_right_link.setTarget(Wt::LinkTarget::NewWindow);
		visibility_link.setTarget(Wt::LinkTarget::NewWindow);
		z_index_link.setTarget(Wt::LinkTarget::NewWindow);
		
		aspect_ratio_info->setLink(aspect_ratio_link);
		container_info->setLink(container_link);
		columns_info->setLink(columns_link);
		break_after_info->setLink(break_after_link);
		break_before_info->setLink(break_before_link);
		break_inside_info->setLink(break_inside_link);
		box_decoration_break_info->setLink(box_decoration_break_link);
		box_sizing_info->setLink(box_sizing_link);
		display_info->setLink(display_link);
		floats_info->setLink(floats_link);
		clear_info->setLink(clear_link);
		isolation_info->setLink(isolation_link);
		object_fit_info->setLink(object_fit_link);
		object_position_info->setLink(object_position_link);
		overflow_info->setLink(overflow_link);
		overflow_x_info->setLink(overflow_x_link);
		overflow_y_info->setLink(overflow_y_link);
		overscroll_behavior_info->setLink(overscroll_behavior_link);
		position_info->setLink(position_link);
		position_top_left_bottom_right->setLink(position_top_left_bottom_right_link);
		visibility_info->setLink(visibility_link);
		z_index_info->setLink(z_index_link);

		popupMenu->setStyleClass("bg-neutral-700 text-neutral-200 border border-solid border-neutral-900");

		popupMenu->triggered().connect(this, [=](Wt::WMenuItem *item) {
			if(item->text().toUTF8().compare("set test classes") == 0){
				setCustomTestValues();
				styleChanged_.emit(getStyles());
			}else if(item->text().toUTF8().compare("reset styles") == 0){
				resetStyles();
				styleChanged_.emit(getStyles());
			}
		});

		auto popupBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WPushButton>());
		popupBtn->setStyleClass("p-3 bg-cover bg-[url(resources/icons/hamburger.svg)] !ml-auto mr-2");
		popupBtn->setMenu(std::move(popupMenu));
		// prevent the click event from propagating to the parent because it is located in the title bar witch expands and collapse on click
		popupBtn->clicked().preventPropagation();
	}
	
	
	auto display_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	display_wrapper->setStyleClass("flex space-x-2 whitespace-nowrap");
	display_wrapper->addWidget(std::make_unique<Wt::WText>("Display"))->setStyleClass("font-bold text-neutral-400");
	display_widget_ = display_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig->layout.display));
	{
		position_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.position, "Position", ""));

		auto positions_container = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
		positions_container->addWidget(std::make_unique<Wt::WText>("Inset"))->setStyleClass("font-bold text-neutral-400");
		position_inset_widget_ = positions_container->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig->layout.position_inset));
		auto inset_x_y_wrapper = positions_container->addWidget(std::make_unique<Wt::WContainerWidget>());
		
		position_inset_x_widget_ = inset_x_y_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig->layout.position_inset_x));
		position_inset_y_widget_ = inset_x_y_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig->layout.position_inset_y));
		
		auto directions_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto direction_top_wrapper = directions_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto direction_left_right_wrapper = directions_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto direction_bottom_wrapper = directions_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

		position_top_widget_ = direction_top_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig->layout.position_top));
		position_left_widget_ = direction_left_right_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig->layout.position_left));
		position_right_widget_ = direction_left_right_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig->layout.position_right));
		position_bottom_widget_ = direction_bottom_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig->layout.position_bottom));
		
		
		positions_container->setStyleClass("");
		inset_x_y_wrapper->setStyleClass("flex");
		directions_wrapper->setStyleClass("my-3 mx-auto px-4 min-h-[90px] w-4/5  border-[4px] border-dashed border-neutral-600 flex flex-col justify-between items-stretch");
		direction_top_wrapper->setStyleClass("flex mb-1 flex-col w-fit mx-auto -mt-3");
		direction_left_right_wrapper->setStyleClass("mb-1 flex justify-between -mx-12 space-x-6");
		direction_bottom_wrapper->setStyleClass("flex flex-col w-fit mx-auto -mb-3");

		position_inset_widget_->setCustomValueString("inset-");
		position_inset_x_widget_->setCustomValueString("inset-x-");
		position_inset_y_widget_->setCustomValueString("inset-y-");
		position_top_widget_->setCustomValueString("top-");
		position_left_widget_->setCustomValueString("left-");
		position_right_widget_->setCustomValueString("right-");
		position_bottom_widget_->setCustomValueString("bottom-");

	}

	columns_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.columns, "Columns", "columns-"));
	container_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.container, "Container", ""));
	aspect_ratio_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.aspect_ratio, "Aspect ratio", "aspect-"));
	break_after_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.break_after, "Break after", "break-after-"));
	break_before_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.break_before, "Break before", "break-before-"));
	break_inside_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.break_inside, "Break inside", "break-inside-"));
	box_decoration_break_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.box_decoration_break, "Box decoration break", "box-decoration-"));
	box_sizing_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.box_sizing, "Box sizing", "box-"));
	floats_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.floats, "Floats", "float-"));
	clear_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.clear, "Clear", "clear-"));
	isolation_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.isolation, "Isolation", ""));
	object_fit_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.object_fit, "Object fit", "object-"));
	object_position_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.object_position, "Object position", "object-"));
	overflow_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.overflow, "Overflow", "overflow-"));
	overflow_x_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.overflow_x, "Overflow x", "overflow-x-"));
	overflow_y_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.overflow_y, "Overflow y", "overflow-y-"));
	overscroll_behavior_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.overscroll_behavior, "Overscroll behavior", "overscroll-"));
	overscroll_behavior_x_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.overscroll_behavior_x, "Overscroll behavior x", "overscroll-x-"));
	overscroll_behavior_y_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.overscroll_behavior_y, "Overscroll behavior y", "overscroll-y-"));
	
	visibility_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.visibility, "Visibility", ""));
	z_index_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.z_index, "Z index", "z-"));

	object_fit_widget_->setTitle("object- (fit)");
	object_position_widget_->setTitle("object- (position)");
	
	// signals
	display_widget_->classChanged().connect(this, [=](std::string className) { display_class = className;styleChanged_.emit(getStyles()); });
	aspect_ratio_widget_->classChanged().connect(this, [=](std::string className) { aspect_ratio_class = className;styleChanged_.emit(getStyles()); });
	container_widget_->classChanged().connect(this, [=](std::string className) { container_class = className;styleChanged_.emit(getStyles()); });
	columns_widget_->classChanged().connect(this, [=](std::string className) { columns_class = className;styleChanged_.emit(getStyles()); });
	break_after_widget_->classChanged().connect(this, [=](std::string className) { break_after_class = className;styleChanged_.emit(getStyles()); });
	break_before_widget_->classChanged().connect(this, [=](std::string className) { break_before_class = className;styleChanged_.emit(getStyles()); });
	break_inside_widget_->classChanged().connect(this, [=](std::string className) { break_inside_class = className;styleChanged_.emit(getStyles()); });
	box_decoration_break_widget_->classChanged().connect(this, [=](std::string className) { box_decoration_break_class = className;styleChanged_.emit(getStyles()); });
	box_sizing_widget_->classChanged().connect(this, [=](std::string className) { box_sizing_class = className;styleChanged_.emit(getStyles()); });
	floats_widget_->classChanged().connect(this, [=](std::string className) { floats_class = className;styleChanged_.emit(getStyles()); });
	clear_widget_->classChanged().connect(this, [=](std::string className) { clear_class = className;styleChanged_.emit(getStyles()); });
	isolation_widget_->classChanged().connect(this, [=](std::string className) { isolation_class = className;styleChanged_.emit(getStyles()); });
	object_fit_widget_->classChanged().connect(this, [=](std::string className) { object_fit_class = className;styleChanged_.emit(getStyles()); });
	object_position_widget_->classChanged().connect(this, [=](std::string className) { object_position_class = className;styleChanged_.emit(getStyles()); });
	overflow_widget_->classChanged().connect(this, [=](std::string className) { overflow_class = className;styleChanged_.emit(getStyles()); });
	overflow_x_widget_->classChanged().connect(this, [=](std::string className) { overflow_x_class = className;styleChanged_.emit(getStyles()); });
	overflow_y_widget_->classChanged().connect(this, [=](std::string className) { overflow_y_class = className;styleChanged_.emit(getStyles()); });
	overscroll_behavior_widget_->classChanged().connect(this, [=](std::string className) { overscroll_behavior_class = className;styleChanged_.emit(getStyles()); });
	position_widget_->classChanged().connect(this, [=](std::string className) { position_class = className;styleChanged_.emit(getStyles()); });
	position_inset_widget_->classChanged().connect(this, [=](std::string className) { position_inset_class = className;styleChanged_.emit(getStyles()); });
	position_inset_x_widget_->classChanged().connect(this, [=](std::string className) { position_inset_x_class = className;styleChanged_.emit(getStyles()); });
	position_inset_y_widget_->classChanged().connect(this, [=](std::string className) { position_inset_y_class = className;styleChanged_.emit(getStyles()); });
	position_top_widget_->classChanged().connect(this, [=](std::string className) { position_top_class = className;styleChanged_.emit(getStyles()); });
	position_right_widget_->classChanged().connect(this, [=](std::string className) { position_right_class = className;styleChanged_.emit(getStyles()); });
	position_bottom_widget_->classChanged().connect(this, [=](std::string className) { position_bottom_class = className;styleChanged_.emit(getStyles()); });
	position_left_widget_->classChanged().connect(this, [=](std::string className) { position_left_class = className;styleChanged_.emit(getStyles()); });
	visibility_widget_->classChanged().connect(this, [=](std::string className) { visibility_class = className;styleChanged_.emit(getStyles()); });
	z_index_widget_->classChanged().connect(this, [=](std::string className) { z_index_class = className;styleChanged_.emit(getStyles()); });

};

std::string ElementLayoutWidget::getStyles()
{
	bool activeClasses = false;
	std::string elementClasses;

	if(aspect_ratio_class.compare("none") != 0){ activeClasses = true; elementClasses += aspect_ratio_class + " "; }
	if(container_class.compare("none") != 0){ activeClasses = true; elementClasses += container_class + " "; }
	if(columns_class.compare("none") != 0){ activeClasses = true; elementClasses += columns_class + " "; }
	if(break_after_class.compare("none") != 0){ activeClasses = true; elementClasses += break_after_class + " "; }
	if(break_before_class.compare("none") != 0){ activeClasses = true; elementClasses += break_before_class + " "; }
	if(break_inside_class.compare("none") != 0){ activeClasses = true; elementClasses += break_inside_class + " "; }
	if(box_decoration_break_class.compare("none") != 0){ activeClasses = true; elementClasses += box_decoration_break_class + " "; }
	if(box_sizing_class.compare("none") != 0){ activeClasses = true; elementClasses += box_sizing_class + " "; }
	if(floats_class.compare("none") != 0){ activeClasses = true; elementClasses += floats_class + " "; }
	if(clear_class.compare("none") != 0){ activeClasses = true; elementClasses += clear_class + " "; }
	if(isolation_class.compare("none") != 0){ activeClasses = true; elementClasses += isolation_class + " "; }
	if(object_fit_class.compare("none") != 0){ activeClasses = true; elementClasses += object_fit_class + " "; }
	if(object_position_class.compare("none") != 0){ activeClasses = true; elementClasses += object_position_class + " "; }
	if(overflow_class.compare("none") != 0){ activeClasses = true; elementClasses += overflow_class + " "; }
	if(overflow_x_class.compare("none") != 0){ activeClasses = true; elementClasses += overflow_x_class + " "; }
	if(overflow_y_class.compare("none") != 0){ activeClasses = true; elementClasses += overflow_y_class + " "; }
	if(overscroll_behavior_class.compare("none") != 0){ activeClasses = true; elementClasses += overscroll_behavior_class + " "; }
	if(position_class.compare("none") != 0){ activeClasses = true; elementClasses += position_class + " "; }
	if(position_inset_class.compare("none") != 0){ activeClasses = true; elementClasses += position_inset_class + " "; }
	if(position_inset_x_class.compare("none") != 0){ activeClasses = true; elementClasses += position_inset_x_class + " "; }
	if(position_inset_y_class.compare("none") != 0){ activeClasses = true; elementClasses += position_inset_y_class + " "; }
	if(position_top_class.compare("none") != 0){ activeClasses = true; elementClasses += position_top_class + " "; }
	if(position_right_class.compare("none") != 0){ activeClasses = true; elementClasses += position_right_class + " "; }
	if(position_bottom_class.compare("none") != 0){ activeClasses = true; elementClasses += position_bottom_class + " "; }
	if(position_left_class.compare("none") != 0){ activeClasses = true; elementClasses += position_left_class + " "; }
	if(visibility_class.compare("none") != 0){ activeClasses = true; elementClasses += visibility_class + " "; }
	if(z_index_class.compare("none") != 0){ activeClasses = true; elementClasses += z_index_class + " "; }
	if(display_class.compare("none") != 0){ activeClasses = true; elementClasses += display_class + " "; }


	if(activeClasses) expand();
	return elementClasses;
}

void ElementLayoutWidget::setClasses(LayoutData layoutData)
{
	resetStyles();
	bool activeClasses = false;
	std::cout << " layout display: " << layoutData.display << "\n";
	activeClasses = setDisplay(layoutData.display);
	activeClasses = setAspectRatio(layoutData.aspect_ratio);
	activeClasses = setContainer(layoutData.container);
	activeClasses = setColumns(layoutData.columns);
	activeClasses = setBreakAfter(layoutData.break_after);
	activeClasses = setBreakBefore(layoutData.break_before);
	activeClasses = setBreakInside(layoutData.break_inside);
	activeClasses = setBoxDecorationBreak(layoutData.box_decoration_break);
	activeClasses = setBoxSizing(layoutData.box_sizing);
	activeClasses = setFloats(layoutData.floats);
	activeClasses = setClear(layoutData.clear);
	activeClasses = setIsolation(layoutData.isolation);
	activeClasses = setObjectFit(layoutData.object_fit);
	activeClasses = setObjectPosition(layoutData.object_position);

	for(auto className : layoutData.overflow){
		if(className.find("-x-") != std::string::npos){
			activeClasses = setOverflowX(className);
		}else if (className.find("-y-") != std::string::npos){
			activeClasses = setOverflowY(className);
		}else {
			activeClasses = setOverflow(className);
		}
	}

	for(auto className : layoutData.overscroll_behavior){
		if(className.find("-x-") != std::string::npos){
			activeClasses = setOverscrollBehaviorX(className);
		}else if (className.find("-y-") != std::string::npos){
			activeClasses = setOverscrollBehaviorY(className);
		}else {
			activeClasses = setOverscrollBehavior(className);
		}
	}

	activeClasses = setPosition(layoutData.position);
	
	for(auto className : layoutData.position_inset){
		if (className.find("-x-") != std::string::npos){
			activeClasses = setPositionInsetX(className);
		}else if (className.find("-y-") != std::string::npos){
			activeClasses = setPositionInsetY(className);
		}else {
			activeClasses = setPositionInset(className);
		}
	}

	for(auto className : layoutData.position_sides){
		if (className.find("top-") != std::string::npos){
			activeClasses = setPositionTop(className);
		}else if (className.find("right-") != std::string::npos){
			activeClasses = setPositionRight(className);
		}else if (className.find("bottom-") != std::string::npos){
			activeClasses = setPositionBottom(className);
		}else if (className.find("left-") != std::string::npos){
			activeClasses = setPositionLeft(className);
		}

		activeClasses = setVisibility(layoutData.visibility);
		activeClasses = setZIndex(layoutData.z_index);
	}

	collapse();
}

void ElementLayoutWidget::resetStyles()
{
	aspect_ratio_widget_->setValue("none");
	container_widget_->setValue("none");
	columns_widget_->setValue("none");
	break_after_widget_->setValue("none");
	break_before_widget_->setValue("none");
	break_inside_widget_->setValue("none");
	box_decoration_break_widget_->setValue("none");
	box_sizing_widget_->setValue("none");
	floats_widget_->setValue("none");
	clear_widget_->setValue("none");
	isolation_widget_->setValue("none");
	object_fit_widget_->setValue("none");
	object_position_widget_->setValue("none");
	overflow_widget_->setValue("none");
	overflow_x_widget_->setValue("none");
	overflow_y_widget_->setValue("none");
	overscroll_behavior_widget_->setValue("none");
	overscroll_behavior_x_widget_->setValue("none");
	overscroll_behavior_y_widget_->setValue("none");
	position_widget_->setValue("none");
	position_inset_widget_->setValue("none");
	position_inset_x_widget_->setValue("none");
	position_inset_y_widget_->setValue("none");
	position_top_widget_->setValue("none");
	position_right_widget_->setValue("none");
	position_bottom_widget_->setValue("none");
	position_left_widget_->setValue("none");
	visibility_widget_->setValue("none");
	z_index_widget_->setValue("none");
	display_widget_->setValue("none");

	aspect_ratio_class = "none";
	container_class = "none";
	columns_class = "none";
	break_after_class = "none";
	break_before_class = "none";
	break_inside_class = "none";
	box_decoration_break_class = "none";
	box_sizing_class = "none";
	floats_class = "none";
	clear_class = "none";
	isolation_class = "none";
	object_fit_class = "none";
	object_position_class = "none";
	overflow_class = "none";
	overflow_x_class = "none";
	overflow_y_class = "none";
	overscroll_behavior_class = "none";
	overscroll_behavior_x_class = "none";
	overscroll_behavior_y_class = "none";
	position_class = "none";
	position_inset_class = "none";
	position_inset_x_class = "none";
	position_inset_y_class = "none";
	position_top_class = "none";
	position_right_class = "none";
	position_bottom_class = "none";
	position_left_class = "none";
	visibility_class = "none";
	z_index_class = "none";
	display_class = "none";


}

void ElementLayoutWidget::setCustomTestValues()
{
	setDisplay("block");
	setAspectRatio("aspect-nonauto");
	setContainer("container");
	setColumns("columns-3");
	setBreakAfter("break-after-avoid");
	setBreakBefore("break-before-auto");
	setBreakInside("break-inside-avoid");
	setBoxDecorationBreak("box-decoration-clone");
	setBoxSizing("box-border");
	setFloats("float-right");
	setClear("clear-both");
	setIsolation("isolate");
	setObjectFit("object-contain");
	setObjectPosition("object-bottom");
	setOverflow("overflow-auto");
	setOverflowX("overflow-x-auto");
	setOverflowY("overflow-y-auto");
	setOverscrollBehavior("overscroll-auto");
	setOverscrollBehaviorX("overscroll-x-auto");
	setOverscrollBehaviorY("overscroll-y-auto");
	setPosition("absolute");
	setPositionInset("inset-0");
	setPositionInsetX("inset-x-0");
	setPositionInsetY("inset-y-0");
	setPositionTop("top-0");
	setPositionRight("right-0");
	setPositionBottom("bottom-0");
	setPositionLeft("left-0");
	setVisibility("visible");
	setZIndex("z-0");


}

bool ElementLayoutWidget::setDisplay(std::string className)
{
	display_widget_->setValue(className);
	display_class = display_widget_->getValue();
	if(className.compare("none") == 0) return false;
	else { expand(); return true; }
}

bool ElementLayoutWidget::setPosition(std::string className)
{
	int positionIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.position.styleClasses_);
	if(positionIndex >= 0){
		position_widget_->setValue(className);
		position_class = position_widget_->getValue();
		if(position_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setPositionInset(std::string className)
{

	position_inset_widget_->setValue(className);
	position_inset_class = position_inset_widget_->getValue();
	std::cout << "position_inset_class: " << position_inset_class << std::endl;
	if(position_inset_class.compare("none") == 0) return false;
	else { expand(); return true; }
}

bool ElementLayoutWidget::setPositionInsetX(std::string className)
{
	position_inset_x_widget_->setValue(className);
	position_inset_x_class = position_inset_x_widget_->getValue();
	if(position_inset_x_class.compare("none") == 0) return false;
	else { expand(); return true; }
}

bool ElementLayoutWidget::setPositionInsetY(std::string className)
{
	position_inset_y_widget_->setValue(className);
	position_inset_y_class = position_inset_y_widget_->getValue();
	if(position_inset_y_class.compare("none") == 0) return false;
	else { expand(); return true; }
}

bool ElementLayoutWidget::setPositionTop(std::string className)
{
	std::cout << "position_top_class: " << position_top_class << std::endl;
	position_top_widget_->setValue(className);
	position_top_class = position_top_widget_->getValue();
	if(position_top_class.compare("none") == 0) return false;
	else { expand(); return true; }
}

bool ElementLayoutWidget::setPositionRight(std::string className)
{	
	position_right_widget_->setValue(className);
	position_right_class = position_right_widget_->getValue();
	if(position_right_class.compare("none") == 0) return false;
	else { expand(); return true; }
}

bool ElementLayoutWidget::setPositionBottom(std::string className)
{	
	position_bottom_widget_->setValue(className);
	position_bottom_class = position_bottom_widget_->getValue();
	if(position_bottom_class.compare("none") == 0) return false;
	else { expand(); return true; }
}

bool ElementLayoutWidget::setPositionLeft(std::string className)
{	
	position_left_widget_->setValue(className);
	position_left_class = position_left_widget_->getValue();
	if(position_left_class.compare("none") == 0) return false;
	else { expand(); return true; }
}

bool ElementLayoutWidget::setAspectRatio(std::string className)
{
	int aspectRatioIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.aspect_ratio.styleClasses_);
	if(aspectRatioIndex >= 0){
		aspect_ratio_widget_->setValue(className);
		aspect_ratio_class = aspect_ratio_widget_->getValue();
		if(aspect_ratio_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setContainer(std::string className)
{
	int containerIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.container.styleClasses_);
	if(containerIndex >= 0){
		container_widget_->setValue(className);
		container_class = container_widget_->getValue();
		if(container_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setColumns(std::string className)
{
	int columnsIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.columns.styleClasses_);
	if(columnsIndex >= 0){
		columns_widget_->setValue(className);
		columns_class = columns_widget_->getValue();
		if(columns_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setBreakAfter(std::string className)
{
	int breakAfterIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.break_after.styleClasses_);
	if(breakAfterIndex >= 0){
		break_after_widget_->setValue(className);
		break_after_class = break_after_widget_->getValue();
		if(break_after_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setBreakBefore(std::string className)
{
	int breakBeforeIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.break_before.styleClasses_);
	if(breakBeforeIndex >= 0){
		break_before_widget_->setValue(className);
		break_before_class = break_before_widget_->getValue();
		if(break_before_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setBreakInside(std::string className)
{
	int breakInsideIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.break_inside.styleClasses_);
	if(breakInsideIndex >= 0){
		break_inside_widget_->setValue(className);
		break_inside_class = break_inside_widget_->getValue();
		if(break_inside_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setBoxDecorationBreak(std::string className)
{
	int boxDecorationBreakIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.box_decoration_break.styleClasses_);
	if(boxDecorationBreakIndex >= 0){
		box_decoration_break_widget_->setValue(className);
		box_decoration_break_class = box_decoration_break_widget_->getValue();
		if(box_decoration_break_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setBoxSizing(std::string className)
{
	int boxSizingIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.box_sizing.styleClasses_);
	if(boxSizingIndex >= 0){
		box_sizing_widget_->setValue(className);
		box_sizing_class = box_sizing_widget_->getValue();
		if(box_sizing_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setFloats(std::string className)
{
	int floatsIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.floats.styleClasses_);
	if(floatsIndex >= 0){
		floats_widget_->setValue(className);
		floats_class = floats_widget_->getValue();
		if(floats_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setClear(std::string className)
{
	int clearIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.clear.styleClasses_);
	if(clearIndex >= 0){
		clear_widget_->setValue(className);
		clear_class = clear_widget_->getValue();
		if(clear_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setIsolation(std::string className)
{
	int isolationIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.isolation.styleClasses_);
	if(isolationIndex >= 0){
		isolation_widget_->setValue(className);
		isolation_class = isolation_widget_->getValue();
		if(isolation_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setObjectFit(std::string className)
{
	int objectFitIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.object_fit.styleClasses_);
	if(objectFitIndex >= 0){
		object_fit_widget_->setValue(className);
		object_fit_class = object_fit_widget_->getValue();
		if(object_fit_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setObjectPosition(std::string className)
{
	int objectPositionIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.object_position.styleClasses_);
	if(objectPositionIndex >= 0){
		object_position_widget_->setValue(className);
		object_position_class = object_position_widget_->getValue();
		if(object_position_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setOverflow(std::string className)
{
	int overflowIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.overflow.styleClasses_);
	if(overflowIndex >= 0){
		overflow_widget_->setValue(className);
		overflow_class = overflow_widget_->getValue();
		if(overflow_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setOverflowX(std::string className)
{
	int overflowXIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.overflow_x.styleClasses_);
	if(overflowXIndex >= 0){
		overflow_x_widget_->setValue(className);
		overflow_x_class = overflow_x_widget_->getValue();
		if(overflow_x_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setOverflowY(std::string className)
{
	int overflowYIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.overflow_y.styleClasses_);
	if(overflowYIndex >= 0){
		overflow_y_widget_->setValue(className);
		overflow_y_class = overflow_y_widget_->getValue();
		if(overflow_y_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setOverscrollBehavior(std::string className)
{
	int overscrollBehaviorIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.overscroll_behavior.styleClasses_);
	if(overscrollBehaviorIndex >= 0){
		overscroll_behavior_widget_->setValue(className);
		overscroll_behavior_class = overscroll_behavior_widget_->getValue();
		if(overscroll_behavior_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setOverscrollBehaviorX(std::string className)
{
	int overscrollBehaviorXIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.overscroll_behavior_x.styleClasses_);
	if(overscrollBehaviorXIndex >= 0){
		overscroll_behavior_x_widget_->setValue(className);
		overscroll_behavior_x_class = overscroll_behavior_x_widget_->getValue();
		if(overscroll_behavior_x_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setOverscrollBehaviorY(std::string className)
{
	int overscrollBehaviorYIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.overscroll_behavior_y.styleClasses_);
	if(overscrollBehaviorYIndex >= 0){
		overscroll_behavior_y_widget_->setValue(className);
		overscroll_behavior_y_class = overscroll_behavior_y_widget_->getValue();
		if(overscroll_behavior_y_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setVisibility(std::string className)
{
	int visibilityIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.visibility.styleClasses_);
	if(visibilityIndex >= 0){
		visibility_widget_->setValue(className);
		visibility_class = visibility_widget_->getValue();
		if(visibility_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

bool ElementLayoutWidget::setZIndex(std::string className)
{
	int zIndexIndex = tailwindConfig_->getIndesOfStringInVector(className, tailwindConfig_->layout.z_index.styleClasses_);
	if(zIndexIndex >= 0){
		z_index_widget_->setValue(className);
		z_index_class = z_index_widget_->getValue();
		if(z_index_class.compare("none") == 0) return false;
		else { expand(); return true; }
	}
return false;
}

