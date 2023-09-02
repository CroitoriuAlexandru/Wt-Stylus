#include "include/ElementLayout.h"
#include <regex>
#include <string>
#include <Wt/WPopupMenu.h>
#include <Wt/WMenuItem.h>

ElementLayoutWidget::ElementLayoutWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig),
	aspect_ratio_group(std::make_unique<Wt::WButtonGroup>()),
	container_group(std::make_unique<Wt::WButtonGroup>()),
	columns_group(std::make_unique<Wt::WButtonGroup>()),
	break_after_group(std::make_unique<Wt::WButtonGroup>()),
	break_before_group(std::make_unique<Wt::WButtonGroup>()),
	break_inside_group(std::make_unique<Wt::WButtonGroup>()),
	box_decoration_break_group(std::make_unique<Wt::WButtonGroup>()),
	box_sizing_group(std::make_unique<Wt::WButtonGroup>()),
	floats_group(std::make_unique<Wt::WButtonGroup>()),
	clear_group(std::make_unique<Wt::WButtonGroup>()),
	isolation_group(std::make_unique<Wt::WButtonGroup>()),
	object_fit_group(std::make_unique<Wt::WButtonGroup>()),
	object_position_group(std::make_unique<Wt::WButtonGroup>()),
	overflow_group(std::make_unique<Wt::WButtonGroup>()),
	overflow_x_group(std::make_unique<Wt::WButtonGroup>()),
	overflow_y_group(std::make_unique<Wt::WButtonGroup>()),
	overscroll_behavior_group(std::make_unique<Wt::WButtonGroup>()),
	overscroll_behavior_x_group(std::make_unique<Wt::WButtonGroup>()),
	overscroll_behavior_y_group(std::make_unique<Wt::WButtonGroup>()),
	position_group(std::make_unique<Wt::WButtonGroup>()),
	position_inset_group(std::make_unique<Wt::WButtonGroup>()),
	position_inset_x_group(std::make_unique<Wt::WButtonGroup>()),
	position_inset_y_group(std::make_unique<Wt::WButtonGroup>()),
	position_top_group(std::make_unique<Wt::WButtonGroup>()),
	position_right_group(std::make_unique<Wt::WButtonGroup>()),
	position_bottom_group(std::make_unique<Wt::WButtonGroup>()),
	position_left_group(std::make_unique<Wt::WButtonGroup>()),
	visibility_group(std::make_unique<Wt::WButtonGroup>()),
	z_index_group(std::make_unique<Wt::WButtonGroup>())
{


	setStyleClass("min-w-fit max-w-[300px] !border-x-0 !bg-neutral-700 !text-neutral-200 !border-neutral-900 px-1.5");
	setTitle("Layout");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-900 bg-neutral-800 ");
	setCollapsible(true);
	auto centralWidget = setCentralWidget(std::make_unique<Wt::WContainerWidget>());

	auto aspect_ratio_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig->layout.aspect_ratio, "Aspect ratio", "aspect-"));
	aspect_ratio_widget_->classChanged().connect(this, [=](std::string className) { 
		std::cout << "\n\n ------------ aspect_ratio changed " << className << "\n\n";
	});

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



	centralWidget->setStyleClass("flex flex-col w-full max-w-[300px]");

	auto aspect_ratio_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto container_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto columns_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto break_after_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto break_before_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto break_inside_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto box_decoration_break_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto box_sizing_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto display_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto floats_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto clear_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto isolation_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto object_fit_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto object_position_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overflow_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overflow_x_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overflow_y_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overscroll_behavior_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overscroll_behavior_x_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overscroll_behavior_y_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_inset_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_inset_x_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_inset_y_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_top_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_right_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_bottom_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_left_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_start_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_end_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto visibility_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto z_index_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

	auto aspect_ratio_header = aspect_ratio_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto container_header = container_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto columns_header = columns_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto break_after_header = break_after_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto break_before_header = break_before_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto break_inside_header = break_inside_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto box_decoration_break_header = box_decoration_break_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto box_sizing_header = box_sizing_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto display_header = display_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto floats_header = floats_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto clear_header = clear_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto isolation_header = isolation_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto object_fit_header = object_fit_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto object_position_header = object_position_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overflow_header = overflow_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overflow_x_header = overflow_x_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overflow_y_header = overflow_y_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overscroll_behavior_header = overscroll_behavior_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overscroll_behavior_x_header = overscroll_behavior_x_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overscroll_behavior_y_header = overscroll_behavior_y_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_header = position_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_inset_header = position_inset_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_inset_x_header = position_inset_x_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_inset_y_header = position_inset_y_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_top_header = position_top_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_right_header = position_right_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_bottom_header = position_bottom_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_left_header = position_left_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto visibility_header = visibility_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto z_index_header = z_index_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

	auto aspect_ratio_body = aspect_ratio_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto container_body = container_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto columns_body = columns_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto break_after_body = break_after_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto break_before_body = break_before_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto break_inside_body = break_inside_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto box_decoration_break_body = box_decoration_break_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto box_sizing_body = box_sizing_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto display_body = display_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto floats_body = floats_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto clear_body = clear_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto isolation_body = isolation_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto object_fit_body = object_fit_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto object_position_body = object_position_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overflow_body = overflow_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overflow_x_body = overflow_x_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overflow_y_body = overflow_y_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overscroll_behavior_body = overscroll_behavior_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overscroll_behavior_x_body = overscroll_behavior_x_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overscroll_behavior_y_body = overscroll_behavior_y_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_body = position_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_inset_body = position_inset_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_inset_x_body = position_inset_x_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_inset_y_body = position_inset_y_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_top_body = position_top_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_right_body = position_right_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_bottom_body = position_bottom_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_left_body = position_left_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto visibility_body = visibility_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto z_index_body = z_index_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

	std::string wrapper_classes = "flex flex-col border border-solid pb-1 border-neutral-900";
	aspect_ratio_wrapper->setStyleClass(wrapper_classes);
	container_wrapper->setStyleClass(wrapper_classes);
	columns_wrapper->setStyleClass(wrapper_classes);
	break_after_wrapper->setStyleClass(wrapper_classes);
	break_before_wrapper->setStyleClass(wrapper_classes);
	break_inside_wrapper->setStyleClass(wrapper_classes);
	box_decoration_break_wrapper->setStyleClass(wrapper_classes);
	box_sizing_wrapper->setStyleClass(wrapper_classes);
	display_wrapper->setStyleClass(wrapper_classes);
	floats_wrapper->setStyleClass(wrapper_classes);
	clear_wrapper->setStyleClass(wrapper_classes);
	isolation_wrapper->setStyleClass(wrapper_classes);
	object_fit_wrapper->setStyleClass(wrapper_classes);
	object_position_wrapper->setStyleClass(wrapper_classes);
	overflow_wrapper->setStyleClass(wrapper_classes);
	overflow_x_wrapper->setStyleClass(wrapper_classes);
	overflow_y_wrapper->setStyleClass(wrapper_classes);
	overscroll_behavior_wrapper->setStyleClass(wrapper_classes);
	overscroll_behavior_x_wrapper->setStyleClass(wrapper_classes);
	overscroll_behavior_y_wrapper->setStyleClass(wrapper_classes);
	position_wrapper->setStyleClass(wrapper_classes);
	position_inset_wrapper->setStyleClass(wrapper_classes);
	position_inset_x_wrapper->setStyleClass(wrapper_classes);
	position_inset_y_wrapper->setStyleClass(wrapper_classes);
	position_top_wrapper->setStyleClass(wrapper_classes);
	position_right_wrapper->setStyleClass(wrapper_classes);
	position_bottom_wrapper->setStyleClass(wrapper_classes);
	position_left_wrapper->setStyleClass(wrapper_classes);
	visibility_wrapper->setStyleClass(wrapper_classes);
	z_index_wrapper->setStyleClass(wrapper_classes);
	
	std::string header_classes = "flex font-bold text-neutral-400";
	aspect_ratio_header->setStyleClass(header_classes);
	container_header->setStyleClass(header_classes);
	columns_header->setStyleClass(header_classes);
	break_after_header->setStyleClass(header_classes);
	break_before_header->setStyleClass(header_classes);
	break_inside_header->setStyleClass(header_classes);
	box_decoration_break_header->setStyleClass(header_classes);
	box_sizing_header->setStyleClass(header_classes);
	display_header->setStyleClass(header_classes);
	floats_header->setStyleClass(header_classes);
	clear_header->setStyleClass(header_classes);
	isolation_header->setStyleClass(header_classes);
	object_fit_header->setStyleClass(header_classes);
	object_position_header->setStyleClass(header_classes);
	overflow_header->setStyleClass(header_classes);
	overflow_x_header->setStyleClass(header_classes);
	overflow_y_header->setStyleClass(header_classes);
	overscroll_behavior_header->setStyleClass(header_classes);
	overscroll_behavior_x_header->setStyleClass(header_classes);
	overscroll_behavior_y_header->setStyleClass(header_classes);
	position_header->setStyleClass(header_classes);
	position_inset_header->setStyleClass(header_classes);
	position_inset_x_header->setStyleClass(header_classes);
	position_inset_y_header->setStyleClass(header_classes);
	position_top_header->setStyleClass(header_classes);
	position_right_header->setStyleClass(header_classes);
	position_bottom_header->setStyleClass(header_classes);
	position_left_header->setStyleClass(header_classes);
	visibility_header->setStyleClass(header_classes);
	z_index_header->setStyleClass(header_classes);

	aspect_ratio_header->addWidget(std::make_unique<Wt::WText>("Aspect ratio"));
	container_header->addWidget(std::make_unique<Wt::WText>("Container"));
	columns_header->addWidget(std::make_unique<Wt::WText>("Columns"));
	break_after_header->addWidget(std::make_unique<Wt::WText>("Break after"));
	break_before_header->addWidget(std::make_unique<Wt::WText>("Break before"));
	break_inside_header->addWidget(std::make_unique<Wt::WText>("Break inside"));
	box_decoration_break_header->addWidget(std::make_unique<Wt::WText>("Box decoration break"));
	box_sizing_header->addWidget(std::make_unique<Wt::WText>("Box sizing"));
	display_header->addWidget(std::make_unique<Wt::WText>("Display"));
	floats_header->addWidget(std::make_unique<Wt::WText>("Floats"));
	clear_header->addWidget(std::make_unique<Wt::WText>("Clear"));
	isolation_header->addWidget(std::make_unique<Wt::WText>("Isolation"));
	object_fit_header->addWidget(std::make_unique<Wt::WText>("Object fit"));
	object_position_header->addWidget(std::make_unique<Wt::WText>("Object position"));
	overflow_header->addWidget(std::make_unique<Wt::WText>("Overflow"));
	overflow_x_header->addWidget(std::make_unique<Wt::WText>("Overflow x"));
	overflow_y_header->addWidget(std::make_unique<Wt::WText>("Overflow y"));
	overscroll_behavior_header->addWidget(std::make_unique<Wt::WText>("Overscroll behavior"));
	overscroll_behavior_x_header->addWidget(std::make_unique<Wt::WText>("Overscroll behavior x"));
	overscroll_behavior_y_header->addWidget(std::make_unique<Wt::WText>("Overscroll behavior y"));
	position_header->addWidget(std::make_unique<Wt::WText>("Position"));
	position_inset_header->addWidget(std::make_unique<Wt::WText>("Position inset"));
	position_inset_x_header->addWidget(std::make_unique<Wt::WText>("Position inset x"));
	position_inset_y_header->addWidget(std::make_unique<Wt::WText>("Position inset y"));
	position_top_header->addWidget(std::make_unique<Wt::WText>("Position top"));
	position_right_header->addWidget(std::make_unique<Wt::WText>("Position right"));
	position_bottom_header->addWidget(std::make_unique<Wt::WText>("Position bottom"));
	position_left_header->addWidget(std::make_unique<Wt::WText>("Position left"));
	visibility_header->addWidget(std::make_unique<Wt::WText>("Visibility"));
	z_index_header->addWidget(std::make_unique<Wt::WText>("Z index"));


	std::string class_indicator_classes = "ms-auto me-2";
	aspect_ratio_header->addWidget(std::make_unique<Wt::WText>("aspect-"))->setStyleClass(class_indicator_classes);;
	container_header->addWidget(std::make_unique<Wt::WText>(""))->setStyleClass(class_indicator_classes);;
	columns_header->addWidget(std::make_unique<Wt::WText>("columns-"))->setStyleClass(class_indicator_classes);;
	break_after_header->addWidget(std::make_unique<Wt::WText>("break-after-"))->setStyleClass(class_indicator_classes);;
	break_before_header->addWidget(std::make_unique<Wt::WText>("break-before-"))->setStyleClass(class_indicator_classes);;
	break_inside_header->addWidget(std::make_unique<Wt::WText>("break-inside-"))->setStyleClass(class_indicator_classes);;
	box_decoration_break_header->addWidget(std::make_unique<Wt::WText>("box-decoration-"))->setStyleClass(class_indicator_classes + " text-sm");;
	box_sizing_header->addWidget(std::make_unique<Wt::WText>("box-"))->setStyleClass(class_indicator_classes);;
	display_header->addWidget(std::make_unique<Wt::WText>(""))->setStyleClass(class_indicator_classes);;
	floats_header->addWidget(std::make_unique<Wt::WText>("float-"))->setStyleClass(class_indicator_classes);;
	clear_header->addWidget(std::make_unique<Wt::WText>("clear-"))->setStyleClass(class_indicator_classes);;
	isolation_header->addWidget(std::make_unique<Wt::WText>(""))->setStyleClass(class_indicator_classes);;
	object_fit_header->addWidget(std::make_unique<Wt::WText>("object-"))->setStyleClass(class_indicator_classes);;
	object_position_header->addWidget(std::make_unique<Wt::WText>("object-"))->setStyleClass(class_indicator_classes);;
	overflow_header->addWidget(std::make_unique<Wt::WText>("overflow-"))->setStyleClass(class_indicator_classes);;
	overflow_x_header->addWidget(std::make_unique<Wt::WText>("overflow-x-"))->setStyleClass(class_indicator_classes);;
	overflow_y_header->addWidget(std::make_unique<Wt::WText>("overflow-y-"))->setStyleClass(class_indicator_classes);;
	overscroll_behavior_header->addWidget(std::make_unique<Wt::WText>("overscroll-"))->setStyleClass(class_indicator_classes);;
	overscroll_behavior_x_header->addWidget(std::make_unique<Wt::WText>("overscroll-x-"))->setStyleClass(class_indicator_classes);;
	overscroll_behavior_y_header->addWidget(std::make_unique<Wt::WText>("overscroll-y-"))->setStyleClass(class_indicator_classes);;
	position_header->addWidget(std::make_unique<Wt::WText>(""))->setStyleClass(class_indicator_classes);;
	position_inset_header->addWidget(std::make_unique<Wt::WText>(""))->setStyleClass(class_indicator_classes);;
	position_inset_x_header->addWidget(std::make_unique<Wt::WText>(""))->setStyleClass(class_indicator_classes);;
	position_inset_y_header->addWidget(std::make_unique<Wt::WText>(""))->setStyleClass(class_indicator_classes);;
	position_top_header->addWidget(std::make_unique<Wt::WText>(""))->setStyleClass(class_indicator_classes);;
	position_right_header->addWidget(std::make_unique<Wt::WText>(""))->setStyleClass(class_indicator_classes);;
	position_bottom_header->addWidget(std::make_unique<Wt::WText>(""))->setStyleClass(class_indicator_classes);;
	position_left_header->addWidget(std::make_unique<Wt::WText>(""))->setStyleClass(class_indicator_classes);;
	visibility_header->addWidget(std::make_unique<Wt::WText>(""))->setStyleClass(class_indicator_classes);;
	z_index_header->addWidget(std::make_unique<Wt::WText>(""))->setStyleClass(class_indicator_classes);;

	std::string body_classes = "flex flex-wrap items-center";
	aspect_ratio_body->setStyleClass(body_classes);
	container_body->setStyleClass(body_classes);
	columns_body->setStyleClass(body_classes);
	break_after_body->setStyleClass(body_classes);
	break_before_body->setStyleClass(body_classes);
	break_inside_body->setStyleClass(body_classes);
	box_decoration_break_body->setStyleClass(body_classes);
	box_sizing_body->setStyleClass(body_classes);
	display_body->setStyleClass(body_classes);
	floats_body->setStyleClass(body_classes);
	clear_body->setStyleClass(body_classes);
	isolation_body->setStyleClass(body_classes);
	object_fit_body->setStyleClass(body_classes);
	object_position_body->setStyleClass(body_classes);
	overflow_body->setStyleClass(body_classes);
	overflow_x_body->setStyleClass(body_classes);
	overflow_y_body->setStyleClass(body_classes);
	overscroll_behavior_body->setStyleClass(body_classes);
	overscroll_behavior_x_body->setStyleClass(body_classes);
	overscroll_behavior_y_body->setStyleClass(body_classes);
	position_body->setStyleClass(body_classes);
	position_inset_body->setStyleClass(body_classes);
	position_inset_x_body->setStyleClass(body_classes);
	position_inset_y_body->setStyleClass(body_classes);
	position_top_body->setStyleClass(body_classes);
	position_right_body->setStyleClass(body_classes);
	position_bottom_body->setStyleClass(body_classes);
	position_left_body->setStyleClass(body_classes);
	visibility_body->setStyleClass(body_classes);
	z_index_body->setStyleClass(body_classes);

	std::string button_styles = 
	R"(
		flex w-fit h-fit cursor-pointer m-px p-px text-neutral-950 font-bold 
		[&>span]:bg-cover [&>input]:hidden [&>span]:m-px [&>span]:rounded-md [&>span]:px-1
		[&>span]:bg-neutral-500 [&>span]:hover:bg-neutral-400 [&>input:checked_+_span]:bg-neutral-400
	)";

	// aspect ratio buttons
	for(int index = 0; index < tailwindConfig_->layout.aspect_ratio.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig_->layout.aspect_ratio.styleClasses_[index];
		auto btn = aspect_ratio_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			btn->setText(style_class.className_.substr(7));
		}
		aspect_ratio_group->addButton(btn, index);
	}

	// container buttons
	for(int index = 0; index < tailwindConfig_->layout.container.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig_->layout.container.styleClasses_[index];
		auto btn = container_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			btn->setText(style_class.className_);
		}
		container_group->addButton(btn, index);
	}

	// columns buttons
	for(int index = 0; index < tailwindConfig_->layout.columns.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig_->layout.columns.styleClasses_[index];
		auto btn = columns_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			btn->setText(style_class.className_.substr(8));
		}
		columns_group->addButton(btn, index);
	}

	// break after buttons
	for(int index = 0; index < tailwindConfig_->layout.break_after.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig_->layout.break_after.styleClasses_[index];
		auto btn = break_after_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else{
			btn->setText(style_class.className_.substr(12));
		}
		break_after_group->addButton(btn, index);
	}

	// break before buttons
	for(int index = 0; index < tailwindConfig_->layout.break_before.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig_->layout.break_before.styleClasses_[index];
		auto btn = break_before_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else{
			btn->setText(style_class.className_.substr(13));
		}
		break_before_group->addButton(btn, index);
	}

	// break inside buttons
	for(int index = 0; index < tailwindConfig_->layout.break_inside.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig_->layout.break_inside.styleClasses_[index];
		auto btn = break_inside_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else{
			btn->setText(style_class.className_.substr(13));
		}
		break_inside_group->addButton(btn, index);
	}

	// box decoration break buttons
	for(int index = 0; index < tailwindConfig_->layout.box_decoration_break.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig_->layout.box_decoration_break.styleClasses_[index];
		auto btn = box_decoration_break_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else{
			btn->setText(style_class.className_.substr(15));
		}
		box_decoration_break_group->addButton(btn, index);
	}

	// box sizing buttons
	for(int index = 0; index < tailwindConfig_->layout.box_sizing.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig_->layout.box_sizing.styleClasses_[index];
		auto btn = box_sizing_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			btn->setText(style_class.className_.substr(4));
		}
		box_sizing_group->addButton(btn, index);
	}

	// display ComboBoxClassChanger
	display_widget_ = display_body->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->layout.display));

	// floats buttons
	for(int index = 0; index < tailwindConfig_->layout.floats.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig_->layout.floats.styleClasses_[index];
		auto btn = floats_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			btn->setText(style_class.className_.substr(6));
		}
		floats_group->addButton(btn, index);
	}

	// clear buttons
	for(int index = 0; index < tailwindConfig_->layout.clear.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig_->layout.clear.styleClasses_[index];
		auto btn = clear_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			btn->setText(style_class.className_.substr(6));
		}
		clear_group->addButton(btn, index);
	}

	// isolation buttons
	for(int index = 0; index < tailwindConfig_->layout.isolation.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig_->layout.isolation.styleClasses_[index];
		auto btn = isolation_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			btn->setText(style_class.className_);
		}
		isolation_group->addButton(btn, index);
	}

	// object fit buttons
	for(int index = 0; index < tailwindConfig_->layout.object_fit.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig_->layout.object_fit.styleClasses_[index];
		auto btn = object_fit_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			btn->setText(style_class.className_.substr(7));
		}
		object_fit_group->addButton(btn, index);
	}

	// object position buttons
	for(int index = 0; index < tailwindConfig_->layout.object_position.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig_->layout.object_position.styleClasses_[index];
		auto btn = object_position_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){ 
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			btn->setText(style_class.className_.substr(7));
		}
		object_position_group->addButton(btn, index);
	}

	// overflow buttons
	for(int index = 0; index < tailwindConfig_->layout.overflow.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig_->layout.overflow.styleClasses_[index];
		auto btn = overflow_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){ 
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			btn->setText(style_class.className_.substr(9));
		}
		overflow_group->addButton(btn, index);
	}

	// overflow x buttons
	for(int index = 0; index < tailwindConfig_->layout.overflow_x.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig_->layout.overflow.styleClasses_[index];
		auto btn = overflow_x_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){ 
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			btn->setText(style_class.className_.substr(9));
		}
		overflow_x_group->addButton(btn, index);
	}

	// overflow y buttons
	for(int index = 0; index < tailwindConfig_->layout.overflow_y.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig_->layout.overflow_y.styleClasses_[index];
		auto btn = overflow_y_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){ 
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			btn->setText(style_class.className_.substr(9));
		}
		overflow_y_group->addButton(btn, index);
	}

	// // overscroll behavior buttons
	// for(int index = 0; index < tailwindConfig_->layout.overscroll_behavior.styleClasses_.size(); ++index){
	// 	auto style_class = tailwindConfig_->layout.overscroll_behavior.styleClasses_[index];
	// 	auto btn = overscroll_behavior_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
	// 	btn->setStyleClass(button_styles);
	// 	if(style_class.className_.compare("none") != 0){ 
	// 		btn->setText(style_class.className_.substr(15));
	// 	}
	// 	overscroll_behavior_group->addButton(btn, index);
	// }

	// // overscroll behavior x buttons
	// for(int index = 0; index < tailwindConfig_->layout.overscroll_behavior_x.styleClasses_.size(); ++index){
	// 	auto style_class = tailwindConfig_->layout.overscroll_behavior_x.styleClasses_[index];
	// 	auto btn = overscroll_behavior_x_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
	// 	btn->setStyleClass(button_styles);
	// 	if(style_class.className_.compare("none") != 0){ 
	// 		btn->setText(style_class.className_.substr(17));
	// 	}
	// 	overscroll_behavior_x_group->addButton(btn, index);
	// }

	// // overscroll behavior y buttons
	// for(int index = 0; index < tailwindConfig_->layout.overscroll_behavior_y.styleClasses_.size(); ++index){
	// 	auto style_class = tailwindConfig_->layout.overscroll_behavior_y.styleClasses_[index];
	// 	auto btn = overscroll_behavior_y_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
	// 	btn->setStyleClass(button_styles);
	// 	if(style_class.className_.compare("mome") != 0){ 
	// 		btn->setText(style_class.className_.substr(17));
	// 	}
	// 	overscroll_behavior_y_group->addButton(btn, index);
	// }
	
	// gradient_group->button(0)->setChecked(true);
	// attachment_group->button(0)->setChecked(true);
	// clip_group->button(0)->setChecked(true);
	// origin_group->button(0)->setChecked(true);
	// position_group->button(0)->setChecked(true);
	// repeat_group->button(0)->setChecked(true);
	// size_group->button(0)->setChecked(true);

	// gradient_group->checkedChanged().connect(this, [=](){ 
	// 	int id = gradient_group->checkedId();
	// 	gradient_class = tailwindConfig_->backgrounds.background_image.styleClasses_[id].className_;
	// 	std::cout << "gradient_class: " << gradient_class << std::endl;
	// 	styleChanged_.emit(getStyles()); 
	// });
	// attachment_group->checkedChanged().connect(this, [=](){ 
	// 	int id = attachment_group->checkedId();
	// 	attachment_class = tailwindConfig_->backgrounds.background_attachment.styleClasses_[id].className_;
	// 	std::cout << "attachment_class: " << attachment_class << std::endl;
	// 	styleChanged_.emit(getStyles()); 
	// });
	// clip_group->checkedChanged().connect(this, [=](){ 
	// 	int id = clip_group->checkedId();
	// 	clip_class = tailwindConfig_->backgrounds.background_clip.styleClasses_[id].className_;
	// 	std::cout << "clip_class: " << clip_class << std::endl;
	// 	styleChanged_.emit(getStyles()); 
	// });
	// origin_group->checkedChanged().connect(this, [=](){ 
	// 	int id = origin_group->checkedId();
	// 	origin_class = tailwindConfig_->backgrounds.background_origin.styleClasses_[id].className_;
	// 	std::cout << "origin_class: " << origin_class << std::endl;
	// 	styleChanged_.emit(getStyles()); 
	// });
	// position_group->checkedChanged().connect(this, [=](){ 
	// 	int id = position_group->checkedId();
	// 	position_class = tailwindConfig_->backgrounds.background_position.styleClasses_[id].className_;
	// 	std::cout << "position_class: " << position_class << std::endl;
	// 	styleChanged_.emit(getStyles()); 
	// });
	// repeat_group->checkedChanged().connect(this, [=](){ 
	// 	int id = repeat_group->checkedId();
	// 	repeat_class = tailwindConfig_->backgrounds.background_repeat.styleClasses_[id].className_;
	// 	std::cout << "repeat_class: " << repeat_class << std::endl;
	// 	styleChanged_.emit(getStyles()); 
	// });
	// size_group->checkedChanged().connect(this, [=](){ 
	// 	int id = size_group->checkedId();
	// 	size_class = tailwindConfig_->backgrounds.background_size.styleClasses_[id].className_;
	// 	std::cout << "size_class: " << size_class << std::endl;
	// 	styleChanged_.emit(getStyles()); 
	// });


};

std::string ElementLayoutWidget::getStyles()
{
	bool activeClasses = false;
	std::string elementClasses;

	// if(gradient_class.compare("none") != 0){
	// 	activeClasses = true; 
	// 	elementClasses += gradient_class + " ";
	// }
	// if(attachment_class.compare("none") != 0){
	// 	activeClasses = true; 
	// 	elementClasses += attachment_class + " ";
	// }
	// if(clip_class.compare("none") != 0){
	// 	activeClasses = true; 
	// 	elementClasses += clip_class + " ";
	// }
	// if(origin_class.compare("none") != 0){
	// 	activeClasses = true; 
	// 	elementClasses += origin_class + " ";
	// }
	// if(position_class.compare("none") != 0){
	// 	activeClasses = true; 
	// 	elementClasses += position_class + " ";
	// }
	// if(repeat_class.compare("none") != 0){
	// 	activeClasses = true; 
	// 	elementClasses += repeat_class + " ";
	// }
	// if(size_class.compare("none") != 0){
	// 	activeClasses = true; 
	// 	elementClasses += size_class + " ";
	// }


	if(activeClasses) expand();

	return elementClasses;
}



void ElementLayoutWidget::setClasses(LayoutData layoutData)
{
	// resetStyles();
	// bool activeClasses;
	// activeClasses = setGradient(bgData. gradient);
	// activeClasses = setAttachment(bgData.attachment);
	// activeClasses = setClip(bgData.clip);
	// activeClasses = setOrigin(bgData.origin);
	// activeClasses = setPosition(bgData.position);
	// activeClasses = setRepeat(bgData.repeat);
	// activeClasses = setSize(bgData.size);

	// if(!activeClasses) collapse();
}

void ElementLayoutWidget::resetStyles()
{
	// gradient_group->setCheckedButton(gradient_group->button(0));
	// attachment_group->setCheckedButton(attachment_group->button(0));
	// clip_group->setCheckedButton(clip_group->button(0));
	// origin_group->setCheckedButton(origin_group->button(0));
	// position_group->setCheckedButton(position_group->button(0));
	// repeat_group->setCheckedButton(repeat_group->button(0));
	// size_group->setCheckedButton(size_group->button(0));

	// gradient_class = "none";
	// attachment_class = "none";
	// clip_class = "none";
	// origin_class = "none";
	// position_class = "none";
	// repeat_class = "none";
	// size_class = "none";
}

void ElementLayoutWidget::setCustomTestValues()
{
	// gradient_group->setCheckedButton(gradient_group->button(3));
	// attachment_group->setCheckedButton(attachment_group->button(3));
	// clip_group->setCheckedButton(clip_group->button(3));
	// origin_group->setCheckedButton(origin_group->button(3));
	// position_group->setCheckedButton(position_group->button(3));
	// repeat_group->setCheckedButton(repeat_group->button(3));
	// size_group->setCheckedButton(size_group->button(3));

	// gradient_group->checkedChanged().emit(gradient_group->checkedButton());
	// attachment_group->checkedChanged().emit(attachment_group->checkedButton());
	// clip_group->checkedChanged().emit(clip_group->checkedButton());
	// origin_group->checkedChanged().emit(origin_group->checkedButton());
	// position_group->checkedChanged().emit(position_group->checkedButton());
	// repeat_group->checkedChanged().emit(repeat_group->checkedButton());
	// size_group->checkedChanged().emit(size_group->checkedButton());
}

// bool ElementLayoutWidget::setGradient(std::string className)
// {
// 	int gradientIndex = getIndesOfStringInVector(className, tailwindConfig_->backgrounds.background_image.styleClasses_);
// 	if(gradientIndex >= 0){
// 		gradient_group->button(gradientIndex)->setChecked(true);
// 		if(gradientIndex > 0) {
// 			expand();
// 			return true;
// 		}
// 	}
// 	return false;
// }

// bool ElementLayoutWidget::setAttachment(std::string className)
// {
// 	int attachmentIndex = getIndesOfStringInVector(className, tailwindConfig_->backgrounds.background_attachment.styleClasses_);
// 	if(attachmentIndex >= 0){
// 		attachment_group->button(attachmentIndex)->setChecked(true);
// 		if(attachmentIndex > 0) {
// 			expand();
// 			return true;
// 		}
// 	}
// 	return false;
// }

// bool ElementLayoutWidget::setClip(std::string className)
// {
// 	int clipIndex = getIndesOfStringInVector(className, tailwindConfig_->backgrounds.background_clip.styleClasses_);
// 	if(clipIndex >= 0){
// 		clip_group->button(clipIndex)->setChecked(true);
// 		if(clipIndex > 0) {
// 			expand();
// 			return true;
// 		}
// 	}
// 	return false;
// }

// bool ElementLayoutWidget::setOrigin(std::string className)
// {
// 	int originIndex = getIndesOfStringInVector(className, tailwindConfig_->backgrounds.background_origin.styleClasses_);
// 	if(originIndex >= 0){
// 		origin_group->button(originIndex)->setChecked(true);
// 		if(originIndex > 0) {
// 			expand();
// 			return true;
// 		}
// 	}
// 	return false;
// }

// bool ElementLayoutWidget::setPosition(std::string className)
// {
// 	int positionIndex = getIndesOfStringInVector(className, tailwindConfig_->backgrounds.background_position.styleClasses_);
// 	if(positionIndex >= 0){
// 		position_group->button(positionIndex)->setChecked(true);
// 		if(positionIndex > 0) {
// 			expand();
// 			return true;
// 		}
// 	}
// 	return false;
// }

// bool ElementLayoutWidget::setRepeat(std::string className)
// {
// 	int repeatIndex = getIndesOfStringInVector(className, tailwindConfig_->backgrounds.background_repeat.styleClasses_);
// 	if(repeatIndex >= 0){
// 		repeat_group->button(repeatIndex)->setChecked(true);
// 		if(repeatIndex > 0) {
// 			expand();
// 			return true;
// 		}
// 	}
// 	return false;
// }

// bool ElementLayoutWidget::setSize(std::string className)
// {
// 	int sizeIndex = getIndesOfStringInVector(className, tailwindConfig_->backgrounds.background_size.styleClasses_);
// 	if(sizeIndex >= 0){
// 		size_group->button(sizeIndex)->setChecked(true);
// 		if(sizeIndex > 0) {
// 			expand();
// 			return true;
// 		}
// 	}
// 	return false;
// }