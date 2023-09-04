#include "include/ElementFlexAndGrid.h"
#include <regex>
#include <string>
#include <Wt/WPopupMenu.h>
#include <Wt/WMenuItem.h>

ElementFlexAndGridWidget::ElementFlexAndGridWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig)
{


	setStyleClass("min-w-fit max-w-[300px] !border-x-0 !bg-neutral-700 !text-neutral-200 !border-neutral-900 px-1.5");
	setTitle("Flex & Grid");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-900 bg-neutral-800 ");
	setCollapsible(true);
	auto centralWidget = setCentralWidget(std::make_unique<Wt::WContainerWidget>());
	centralWidget->setStyleClass("flex flex-col w-full max-w-[300px]");

	// popup menu
	{

		auto popupMenu = std::make_unique<Wt::WPopupMenu>();
		std::string menuItemsStyles = "p-2 m-1 hover:bg-neutral-800 hover:text-neutral-200";
		popupMenu->addItem("set test classes")->setStyleClass(menuItemsStyles);
		popupMenu->addItem("reset styles")->setStyleClass(menuItemsStyles);
		popupMenu->addSeparator()->setStyleClass("border border-solid border-neutral-900");

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

	// links to docs
		
		Wt::WLink order_link = Wt::WLink(tailwindConfig_->flexbox.order.docsLink_);
		Wt::WLink basis_link = Wt::WLink(tailwindConfig_->flexbox.basis.docsLink_);
		Wt::WLink direction_link = Wt::WLink(tailwindConfig_->flexbox.direction.docsLink_);
		Wt::WLink wrap_link = Wt::WLink(tailwindConfig_->flexbox.wrap.docsLink_);
		Wt::WLink flex_link = Wt::WLink(tailwindConfig_->flexbox.grow_skrink.docsLink_);
		Wt::WLink grow_link = Wt::WLink(tailwindConfig_->flexbox.grow.docsLink_);
		Wt::WLink shrink_link = Wt::WLink(tailwindConfig_->flexbox.shrink.docsLink_);
		Wt::WLink justify_content_link = Wt::WLink(tailwindConfig_->flexbox.justify_content.docsLink_);
		Wt::WLink justify_self_link = Wt::WLink(tailwindConfig_->flexbox.justify_self.docsLink_);
		Wt::WLink justify_items_link = Wt::WLink(tailwindConfig_->flexbox.justify_items.docsLink_);
		Wt::WLink align_content_link = Wt::WLink(tailwindConfig_->flexbox.align_content.docsLink_);
		Wt::WLink align_self_link = Wt::WLink(tailwindConfig_->flexbox.align_self.docsLink_);
		Wt::WLink align_items_link = Wt::WLink(tailwindConfig_->flexbox.align_items.docsLink_);
		Wt::WLink place_content_link = Wt::WLink(tailwindConfig_->flexbox.place_content.docsLink_);
		Wt::WLink place_self_link = Wt::WLink(tailwindConfig_->flexbox.place_self.docsLink_);
		Wt::WLink place_items_link = Wt::WLink(tailwindConfig_->flexbox.place_items.docsLink_);
		Wt::WLink grid_template_columns_link = Wt::WLink(tailwindConfig_->grid.grid_template_columns.docsLink_);
		Wt::WLink grid_cols_start_link = Wt::WLink(tailwindConfig_->grid.grid_cols_start.docsLink_);
		Wt::WLink grid_cols_span_link = Wt::WLink(tailwindConfig_->grid.grid_cols_span.docsLink_);
		Wt::WLink grid_cols_end_link = Wt::WLink(tailwindConfig_->grid.grid_cols_end.docsLink_);
		Wt::WLink grid_template_rows_link = Wt::WLink(tailwindConfig_->grid.grid_template_rows.docsLink_);
		Wt::WLink grid_rows_start_link = Wt::WLink(tailwindConfig_->grid.grid_rows_start.docsLink_);
		Wt::WLink grid_rows_span_link = Wt::WLink(tailwindConfig_->grid.grid_rows_span.docsLink_);
		Wt::WLink grid_rows_end_link = Wt::WLink(tailwindConfig_->grid.grid_rows_end.docsLink_);
		Wt::WLink grid_auto_flow_link = Wt::WLink(tailwindConfig_->grid.grid_auto_flow.docsLink_);
		Wt::WLink grid_auto_columns_link = Wt::WLink(tailwindConfig_->grid.grid_auto_columns.docsLink_);
		Wt::WLink grid_auto_rows_link = Wt::WLink(tailwindConfig_->grid.grid_auto_rows.docsLink_);
		Wt::WLink gap_link = Wt::WLink(tailwindConfig_->grid.gap.docsLink_);

		order_link.setTarget(Wt::LinkTarget::NewWindow);
		basis_link.setTarget(Wt::LinkTarget::NewWindow);
		direction_link.setTarget(Wt::LinkTarget::NewWindow);
		wrap_link.setTarget(Wt::LinkTarget::NewWindow);
		flex_link.setTarget(Wt::LinkTarget::NewWindow);
		grow_link.setTarget(Wt::LinkTarget::NewWindow);
		shrink_link.setTarget(Wt::LinkTarget::NewWindow);
		justify_content_link.setTarget(Wt::LinkTarget::NewWindow);
		justify_self_link.setTarget(Wt::LinkTarget::NewWindow);
		justify_items_link.setTarget(Wt::LinkTarget::NewWindow);
		align_content_link.setTarget(Wt::LinkTarget::NewWindow);
		align_self_link.setTarget(Wt::LinkTarget::NewWindow);
		align_items_link.setTarget(Wt::LinkTarget::NewWindow);
		place_content_link.setTarget(Wt::LinkTarget::NewWindow);
		place_self_link.setTarget(Wt::LinkTarget::NewWindow);
		place_items_link.setTarget(Wt::LinkTarget::NewWindow);
		grid_template_columns_link.setTarget(Wt::LinkTarget::NewWindow);
		grid_cols_start_link.setTarget(Wt::LinkTarget::NewWindow);
		grid_cols_span_link.setTarget(Wt::LinkTarget::NewWindow);
		grid_cols_end_link.setTarget(Wt::LinkTarget::NewWindow);
		grid_template_rows_link.setTarget(Wt::LinkTarget::NewWindow);
		grid_rows_start_link.setTarget(Wt::LinkTarget::NewWindow);
		grid_rows_span_link.setTarget(Wt::LinkTarget::NewWindow);
		grid_rows_end_link.setTarget(Wt::LinkTarget::NewWindow);
		grid_auto_flow_link.setTarget(Wt::LinkTarget::NewWindow);
		grid_auto_columns_link.setTarget(Wt::LinkTarget::NewWindow);
		grid_auto_rows_link.setTarget(Wt::LinkTarget::NewWindow);
		gap_link.setTarget(Wt::LinkTarget::NewWindow);
		

	std::string wrapper_styles = "flex space-x-2 whitespace-nowrap";

	// order
	auto order_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	order_wrapper->setStyleClass(wrapper_styles);


	flex_container = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	grid_container = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	// grid_container->hide();
	// flex_container->hide();
	
	// flex wrappers
	auto basis_wrapper = flex_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto direction_wrapper = flex_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto wrap_wrapper = flex_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grow_shrink_wrapper = flex_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grow_wrapper = flex_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto shrink_wrapper = flex_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto justify_content_wrapper = flex_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto justify_items_wrapper = flex_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto justify_self_wrapper = flex_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto align_content_wrapper = flex_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto align_items_wrapper = flex_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto align_self_wrapper = flex_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto place_content_wrapper = flex_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto place_items_wrapper = flex_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto place_self_wrapper = flex_container->addWidget(std::make_unique<Wt::WContainerWidget>());

	// grid wrappers
	auto grid_template_columns_wrapper = grid_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_cols_start_wrapper = grid_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_cols_span_wrapper = grid_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_cols_end_wrapper = grid_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_template_rows_wrapper = grid_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_rows_start_wrapper = grid_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_rows_span_wrapper = grid_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_rows_end_wrapper = grid_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_auto_flow_wrapper = grid_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_auto_columns_wrapper = grid_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_auto_rows_wrapper = grid_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto gap_wrapper = grid_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto gap_x_wrapper = grid_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto gap_y_wrapper = grid_container->addWidget(std::make_unique<Wt::WContainerWidget>());


	basis_wrapper->setStyleClass(wrapper_styles);
	direction_wrapper->setStyleClass(wrapper_styles);
	wrap_wrapper->setStyleClass(wrapper_styles);
	grow_shrink_wrapper->setStyleClass(wrapper_styles);
	grow_wrapper->setStyleClass(wrapper_styles);
	shrink_wrapper->setStyleClass(wrapper_styles);
	justify_content_wrapper->setStyleClass(wrapper_styles);
	justify_items_wrapper->setStyleClass(wrapper_styles);
	justify_self_wrapper->setStyleClass(wrapper_styles);
	align_content_wrapper->setStyleClass(wrapper_styles);
	align_items_wrapper->setStyleClass(wrapper_styles);
	align_self_wrapper->setStyleClass(wrapper_styles);
	place_content_wrapper->setStyleClass(wrapper_styles);
	place_items_wrapper->setStyleClass(wrapper_styles);
	place_self_wrapper->setStyleClass(wrapper_styles);

	grid_template_columns_wrapper->setStyleClass(wrapper_styles);
	grid_cols_start_wrapper->setStyleClass(wrapper_styles);
	grid_cols_span_wrapper->setStyleClass(wrapper_styles);
	grid_cols_end_wrapper->setStyleClass(wrapper_styles);
	grid_template_rows_wrapper->setStyleClass(wrapper_styles);
	grid_rows_start_wrapper->setStyleClass(wrapper_styles);
	grid_rows_span_wrapper->setStyleClass(wrapper_styles);
	grid_rows_end_wrapper->setStyleClass(wrapper_styles);
	grid_auto_flow_wrapper->setStyleClass(wrapper_styles);
	grid_auto_columns_wrapper->setStyleClass(wrapper_styles);
	grid_auto_rows_wrapper->setStyleClass(wrapper_styles);
	gap_wrapper->setStyleClass(wrapper_styles);
	gap_x_wrapper->setStyleClass(wrapper_styles);
	gap_y_wrapper->setStyleClass(wrapper_styles);

	std::string title_classes = "font-bold text-neutral-400 hover:text-blue-100";

	order_wrapper->addWidget(std::make_unique<Wt::WAnchor>(order_link, "Order"))->setStyleClass(title_classes);
	basis_wrapper->addWidget(std::make_unique<Wt::WAnchor>(basis_link, "Basis"))->setStyleClass(title_classes);
	direction_wrapper->addWidget(std::make_unique<Wt::WAnchor>(direction_link, "Direction"))->setStyleClass(title_classes);
	wrap_wrapper->addWidget(std::make_unique<Wt::WAnchor>(wrap_link, "Wrap"))->setStyleClass(title_classes);
	grow_shrink_wrapper->addWidget(std::make_unique<Wt::WAnchor>(flex_link, "Grow Shrink"))->setStyleClass(title_classes);
	grow_wrapper->addWidget(std::make_unique<Wt::WAnchor>(grow_link, "Grow"))->setStyleClass(title_classes);
	shrink_wrapper->addWidget(std::make_unique<Wt::WAnchor>(shrink_link, "Shrink"))->setStyleClass(title_classes);
	justify_content_wrapper->addWidget(std::make_unique<Wt::WAnchor>(justify_content_link, "Justify Content"))->setStyleClass(title_classes);
	justify_items_wrapper->addWidget(std::make_unique<Wt::WAnchor>(justify_items_link, "Justify Content"))->setStyleClass(title_classes);
	justify_self_wrapper->addWidget(std::make_unique<Wt::WAnchor>(justify_self_link, "Justify Self"))->setStyleClass(title_classes);
	align_content_wrapper->addWidget(std::make_unique<Wt::WAnchor>(align_content_link, "Align Content"))->setStyleClass(title_classes);
	align_items_wrapper->addWidget(std::make_unique<Wt::WAnchor>(align_items_link, "Align Items"))->setStyleClass(title_classes);
	align_self_wrapper->addWidget(std::make_unique<Wt::WAnchor>(align_self_link, "Align Self"))->setStyleClass(title_classes);
	place_content_wrapper->addWidget(std::make_unique<Wt::WAnchor>(place_content_link, "Place Content"))->setStyleClass(title_classes);
	place_items_wrapper->addWidget(std::make_unique<Wt::WAnchor>(place_items_link, "Place Items"))->setStyleClass(title_classes);
	place_self_wrapper->addWidget(std::make_unique<Wt::WAnchor>(place_self_link, "Place Self"))->setStyleClass(title_classes);

	grid_template_columns_wrapper->addWidget(std::make_unique<Wt::WAnchor>(grid_template_columns_link, "Temp Cols"))->setStyleClass(title_classes);
	grid_cols_start_wrapper->addWidget(std::make_unique<Wt::WAnchor>(grid_cols_start_link, "Cols Start"))->setStyleClass(title_classes);
	grid_cols_span_wrapper->addWidget(std::make_unique<Wt::WAnchor>(grid_cols_span_link, "Cols Span"))->setStyleClass(title_classes);
	grid_cols_end_wrapper->addWidget(std::make_unique<Wt::WAnchor>(grid_cols_end_link, "Cols End"))->setStyleClass(title_classes);
	grid_template_rows_wrapper->addWidget(std::make_unique<Wt::WAnchor>(grid_template_rows_link, "Temp Rows"))->setStyleClass(title_classes);
	grid_rows_start_wrapper->addWidget(std::make_unique<Wt::WAnchor>(grid_rows_start_link, "Rows Start"))->setStyleClass(title_classes);
	grid_rows_span_wrapper->addWidget(std::make_unique<Wt::WAnchor>(grid_rows_span_link, "Rows Span"))->setStyleClass(title_classes);
	grid_rows_end_wrapper->addWidget(std::make_unique<Wt::WAnchor>(grid_rows_end_link, "Rows End"))->setStyleClass(title_classes);
	grid_auto_flow_wrapper->addWidget(std::make_unique<Wt::WAnchor>(grid_auto_flow_link, "Auto Flow"))->setStyleClass(title_classes);
	grid_auto_columns_wrapper->addWidget(std::make_unique<Wt::WAnchor>(grid_auto_columns_link, "Auto Columns"))->setStyleClass(title_classes);
	grid_auto_rows_wrapper->addWidget(std::make_unique<Wt::WAnchor>(grid_auto_rows_link, "Auto Rows"))->setStyleClass(title_classes);
	gap_wrapper->addWidget(std::make_unique<Wt::WAnchor>(gap_link, "Gap"))->setStyleClass(title_classes);
	gap_x_wrapper->addWidget(std::make_unique<Wt::WAnchor>(gap_link, "Gap X"))->setStyleClass(title_classes);
	gap_y_wrapper->addWidget(std::make_unique<Wt::WAnchor>(gap_link, "Gap Y"))->setStyleClass(title_classes);


	order_widget_ = order_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->flexbox.order.styleClasses_));

	// flex
	basis_widget_ = basis_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->flexbox.basis.styleClasses_));
	direction_widget_ = direction_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->flexbox.direction.styleClasses_));
	wrap_widget_ = wrap_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->flexbox.wrap.styleClasses_));
	grow_shrink_widget_ = grow_shrink_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->flexbox.grow_skrink.styleClasses_));
	grow_widget_ = grow_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->flexbox.grow.styleClasses_));
	shrink_widget_ = shrink_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->flexbox.shrink.styleClasses_));
	
	justify_content_widget_ = justify_content_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->flexbox.justify_content.styleClasses_));
	justify_items_widget_ = justify_items_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->flexbox.justify_items.styleClasses_));
	justify_self_widget_ = justify_self_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->flexbox.justify_self.styleClasses_));

	align_content_widget_ = align_content_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->flexbox.align_content.styleClasses_));
	align_items_widget_ = align_items_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->flexbox.align_items.styleClasses_));
	align_self_widget_ = align_self_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->flexbox.align_self.styleClasses_));

	place_content_widget_ = place_content_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->flexbox.place_content.styleClasses_));
	place_items_widget_ = place_items_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->flexbox.place_items.styleClasses_));
	place_self_widget_ = place_self_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->flexbox.place_self.styleClasses_));

	// grid
	grid_template_columns_widget_ = grid_template_columns_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->grid.grid_template_columns.styleClasses_));
	grid_cols_start_widget_ = grid_cols_start_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->grid.grid_cols_start.styleClasses_));
	grid_cols_span_widget_ = grid_cols_span_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->grid.grid_cols_span.styleClasses_));
	grid_cols_end_widget_ = grid_cols_end_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->grid.grid_cols_end.styleClasses_));
	grid_template_rows_widget_ = grid_template_rows_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->grid.grid_template_rows.styleClasses_));
	grid_rows_start_widget_ = grid_rows_start_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->grid.grid_rows_start.styleClasses_));
	grid_rows_span_widget_ = grid_rows_span_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->grid.grid_rows_span.styleClasses_)); // 

	grid_rows_end_widget_ = grid_rows_end_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->grid.grid_rows_end.styleClasses_));
	grid_auto_flow_widget_ = grid_auto_flow_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->grid.grid_auto_flow.styleClasses_));
	grid_auto_columns_widget_ = grid_auto_columns_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->grid.grid_auto_columns.styleClasses_));
	grid_auto_rows_widget_ = grid_auto_rows_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->grid.grid_auto_rows.styleClasses_	));

	gap_wrapper->setStyleClass(wrapper_styles);
	gap_x_wrapper->setStyleClass(wrapper_styles);
	gap_y_wrapper->setStyleClass(wrapper_styles);


	gap_widget_ = gap_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig->grid.gap.styleClasses_));
	gap_x_widget_ = gap_x_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig->grid.gap_x.styleClasses_));
	gap_y_widget_ = gap_y_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig->grid.gap_y.styleClasses_));


	// Signals
	order_widget_->classChanged().connect(this, [=](std::string className) {order_class = className; styleChanged_.emit(getStyles()); });
	//flex
	basis_widget_->classChanged().connect(this, [=](std::string className) {basis_class = className; styleChanged_.emit(getStyles()); });
	direction_widget_->classChanged().connect(this, [=](std::string className) {direction_class = className; styleChanged_.emit(getStyles()); });
	wrap_widget_->classChanged().connect(this, [=](std::string className) {wrap_class = className; styleChanged_.emit(getStyles()); });
	grow_shrink_widget_->classChanged().connect(this, [=](std::string className) {grow_shrink_class = className; styleChanged_.emit(getStyles()); });
	grow_widget_->classChanged().connect(this, [=](std::string className) {grow_class = className; styleChanged_.emit(getStyles()); });
	shrink_widget_->classChanged().connect(this, [=](std::string className) {shrink_class = className; styleChanged_.emit(getStyles()); });
	justify_content_widget_->classChanged().connect(this, [=](std::string className) {justify_content_class = className; styleChanged_.emit(getStyles()); });
	justify_items_widget_->classChanged().connect(this, [=](std::string className) {justify_items_class = className; styleChanged_.emit(getStyles()); });
	justify_self_widget_->classChanged().connect(this, [=](std::string className) {justify_self_class = className; styleChanged_.emit(getStyles()); });
	align_content_widget_->classChanged().connect(this, [=](std::string className) {align_content_class = className; styleChanged_.emit(getStyles()); });
	align_items_widget_->classChanged().connect(this, [=](std::string className) {align_items_class = className; styleChanged_.emit(getStyles()); });
	align_self_widget_->classChanged().connect(this, [=](std::string className) {align_self_class = className; styleChanged_.emit(getStyles()); });
	place_content_widget_->classChanged().connect(this, [=](std::string className) {place_content_class = className; styleChanged_.emit(getStyles()); });
	place_items_widget_->classChanged().connect(this, [=](std::string className) {place_items_class = className; styleChanged_.emit(getStyles()); });
	place_self_widget_->classChanged().connect(this, [=](std::string className) {place_self_class = className; styleChanged_.emit(getStyles()); });

	// grid
	grid_template_columns_widget_->classChanged().connect(this, [=](std::string className) {grid_template_columns_class = className; styleChanged_.emit(getStyles()); });
	grid_cols_start_widget_->classChanged().connect(this, [=](std::string className) {grid_cols_start_class = className; styleChanged_.emit(getStyles()); });
	grid_cols_span_widget_->classChanged().connect(this, [=](std::string className) {grid_cols_span_class = className; styleChanged_.emit(getStyles()); });
	grid_cols_end_widget_->classChanged().connect(this, [=](std::string className) {grid_cols_end_class = className; styleChanged_.emit(getStyles()); });
	grid_template_rows_widget_->classChanged().connect(this, [=](std::string className) {grid_template_rows_class = className; styleChanged_.emit(getStyles()); });
	grid_rows_start_widget_->classChanged().connect(this, [=](std::string className) {grid_rows_start_class = className; styleChanged_.emit(getStyles()); });
	grid_rows_span_widget_->classChanged().connect(this, [=](std::string className) {grid_rows_span_class = className; styleChanged_.emit(getStyles()); });
	grid_rows_end_widget_->classChanged().connect(this, [=](std::string className) {grid_rows_end_class = className; styleChanged_.emit(getStyles()); });
	grid_auto_flow_widget_->classChanged().connect(this, [=](std::string className) {grid_auto_flow_class = className; styleChanged_.emit(getStyles()); });
	grid_auto_columns_widget_->classChanged().connect(this, [=](std::string className) {grid_auto_columns_class = className; styleChanged_.emit(getStyles()); });
	grid_auto_rows_widget_->classChanged().connect(this, [=](std::string className) {grid_auto_rows_class = className; styleChanged_.emit(getStyles()); });
	gap_widget_->classChanged().connect(this, [=](std::string className) {gap_class = className; styleChanged_.emit(getStyles()); });
	gap_x_widget_->classChanged().connect(this, [=](std::string className) {gap_x_class = className; styleChanged_.emit(getStyles()); });
	gap_y_widget_->classChanged().connect(this, [=](std::string className) {gap_y_class = className; styleChanged_.emit(getStyles()); });


	
};

std::string ElementFlexAndGridWidget::getStyles()
{
	bool activeClasses = false;
	std::string elementClasses;

	if(order_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += order_class + " ";
	}
	// flex
	if(basis_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += basis_class + " ";
	}
	if(direction_class.compare("none") != 0){
		std::cout << "direction_class: " << direction_class << std::endl;
		elementClasses += direction_class + " ";
		if(!activeClasses) activeClasses = true;
	}
	if(wrap_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += wrap_class + " ";
	}
	if(grow_shrink_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += grow_shrink_class + " ";
	}
	if(grow_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += grow_class + " ";
	}
	if(shrink_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += shrink_class + " ";
	}
	if(justify_content_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += justify_content_class + " ";
	}
	if(justify_items_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += justify_items_class + " ";
	}
	if(justify_self_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += justify_self_class + " ";
	}
	if(align_content_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += align_content_class + " ";
	}
	if(align_items_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += align_items_class + " ";
	}
	if(align_self_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += align_self_class + " ";
	}
	if(place_content_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += place_content_class + " ";
	}
	if(place_items_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += place_items_class + " ";
	}
	if(place_self_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += place_self_class + " ";
	}

	// grid
	if(grid_template_columns_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += grid_template_columns_class + " ";
	}
	if(grid_cols_start_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += grid_cols_start_class + " ";
	}
	if(grid_cols_span_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += grid_cols_span_class + " ";
	}
	if(grid_cols_end_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += grid_cols_end_class + " ";
	}
	if(grid_template_rows_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += grid_template_rows_class + " ";
	}
	if(grid_rows_start_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += grid_rows_start_class + " ";
	}
	if(grid_rows_span_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += grid_rows_span_class + " ";
	}
	if(grid_rows_end_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += grid_rows_end_class + " ";
	}	
	if(grid_auto_flow_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += grid_auto_flow_class + " ";
	}
	if(grid_auto_columns_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += grid_auto_columns_class + " ";
	}
	if(grid_auto_rows_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += grid_auto_rows_class + " ";
	}
	if(gap_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += gap_class + " ";
	}
	if(gap_x_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += gap_x_class + " ";
	}
	if(gap_y_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += gap_y_class + " ";
	}

	// if(activeClasses) expand();

	return elementClasses;
}

void ElementFlexAndGridWidget::setDisplayLayout(std::string layout)
{
	if(layout.compare("flex") == 0){
		show();
		flex_container->show();
		grid_container->hide();
	}else if (layout.compare("grid") == 0){
		show();
		flex_container->hide();
		grid_container->show();
	}else {
		hide();
	}
}


void ElementFlexAndGridWidget::setClasses(FlexAndGridData flexAndGridData)
{
	resetStyles();
	bool activeClasses;

	if(flexAndGridData.order.compare("none") != 0){ setOrder(flexAndGridData.order); if(!activeClasses) true; }
	// flex
	if(flexAndGridData.basis.compare("none") != 0){ setBasis(flexAndGridData.basis); if(!activeClasses) true; }
	if(flexAndGridData.direction.compare("none") != 0){ setDirection(flexAndGridData.direction); if(!activeClasses) true; }
	if(flexAndGridData.wrap.compare("none") != 0){ setWrap(flexAndGridData.wrap); if(!activeClasses) true; }
	if(flexAndGridData.grow_shrink.compare("none") != 0){ setGrowShrink(flexAndGridData.grow_shrink); if(!activeClasses) true; }
	if(flexAndGridData.grow.compare("none") != 0){ setGrow(flexAndGridData.grow); if(!activeClasses) true; }
	if(flexAndGridData.shrink.compare("none") != 0){ setShrink(flexAndGridData.shrink); if(!activeClasses) true; }
	if(flexAndGridData.justify_content.compare("none") != 0){ setJustifyContent(flexAndGridData.justify_content); if(!activeClasses) true; }
	if(flexAndGridData.justify_items.compare("none") != 0){ setJustifyItems(flexAndGridData.justify_items); if(!activeClasses) true; }
	if(flexAndGridData.justify_self.compare("none") != 0){ setJustifySelf(flexAndGridData.justify_self); if(!activeClasses) true; }
	if(flexAndGridData.align_content.compare("none") != 0){ setAlignContent(flexAndGridData.align_content); if(!activeClasses) true; }
	if(flexAndGridData.align_items.compare("none") != 0){ setAlignItems(flexAndGridData.align_items); if(!activeClasses) true; }
	if(flexAndGridData.align_self.compare("none") != 0){ setAlignSelf(flexAndGridData.align_self); if(!activeClasses) true; }
	if(flexAndGridData.place_content.compare("none") != 0){ setPlaceContent(flexAndGridData.place_content); if(!activeClasses) true; }
	if(flexAndGridData.place_items.compare("none") != 0){ setPlaceItems(flexAndGridData.place_items); if(!activeClasses) true; }
	if(flexAndGridData.place_self.compare("none") != 0){ setPlaceSelf(flexAndGridData.place_self); if(!activeClasses) true; }

	// grid
	if(flexAndGridData.grid_template_columns.compare("none") != 0){ setGridTemplateColumns(flexAndGridData.grid_template_columns); if(!activeClasses) true; }
	if(flexAndGridData.grid_cols_start.compare("none") != 0){ setGridColsStart(flexAndGridData.grid_cols_start); if(!activeClasses) true; }
	if(flexAndGridData.grid_cols_span.compare("none") != 0){ setGridColsSpan(flexAndGridData.grid_cols_span); if(!activeClasses) true; }
	if(flexAndGridData.grid_cols_end.compare("none") != 0){ setGridColsEnd(flexAndGridData.grid_cols_end); if(!activeClasses) true; }
	if(flexAndGridData.grid_template_rows.compare("none") != 0){ setGridTemplateRows(flexAndGridData.grid_template_rows); if(!activeClasses) true; }
	if(flexAndGridData.grid_rows_start.compare("none") != 0){ setGridRowsStart(flexAndGridData.grid_rows_start); if(!activeClasses) true; }
	if(flexAndGridData.grid_rows_span.compare("none") != 0){ setGridRowsSpan(flexAndGridData.grid_rows_span); if(!activeClasses) true; }
	if(flexAndGridData.grid_rows_end.compare("none") != 0){ setGridRowsEnd(flexAndGridData.grid_rows_end); if(!activeClasses) true; }
	if(flexAndGridData.grid_auto_flow.compare("none") != 0){ setGridAutoFlow(flexAndGridData.grid_auto_flow); if(!activeClasses) true; }
	if(flexAndGridData.grid_auto_columns.compare("none") != 0){ setGridAutoColumns(flexAndGridData.grid_auto_columns); if(!activeClasses) true; }
	if(flexAndGridData.grid_auto_rows.compare("none") != 0){ setGridAutoRows(flexAndGridData.grid_auto_rows); if(!activeClasses) true; }

	for(auto gap : flexAndGridData.gap){
		
		if(gap.find("-x-") == 0) 		setGapX(gap);
		else if(gap.find("-y-") == 0) 	setGapY(gap);
		else 							setGap(gap);

	}


	if(!activeClasses) collapse();
}

void ElementFlexAndGridWidget::resetStyles()
{
	order_class = "none";
	// flex
	basis_class = "none";
	direction_class = "none";
	wrap_class = "none";
	grow_shrink_class = "none";
	grow_class = "none";
	shrink_class = "none";
	justify_content_class = "none";
	justify_items_class = "none";
	justify_self_class = "none";
	align_content_class = "none";
	align_items_class = "none";
	align_self_class = "none";
	place_content_class = "none";
	place_items_class = "none";
	place_self_class = "none";

	// grid
	grid_template_columns_class = "none";
	grid_cols_start_class = "none";
	grid_cols_span_class = "none";
	grid_cols_end_class = "none";
	grid_template_rows_class = "none";
	grid_rows_start_class = "none";
	grid_rows_span_class = "none";
	grid_rows_end_class = "none";
	grid_auto_flow_class = "none";
	grid_auto_columns_class = "none";
	grid_auto_rows_class = "none";
	gap_class = "none";
	gap_x_class = "none";
	gap_y_class = "none";

	setOrder(order_class);
	// flex
	setBasis(basis_class);
	setDirection(direction_class);
	setWrap(wrap_class);
	setGrowShrink(grow_shrink_class);
	setGrow(grow_class);
	setShrink(shrink_class);
	setJustifyContent(justify_content_class);
	setJustifyItems(justify_items_class);
	setJustifySelf(justify_self_class);
	setAlignContent(align_content_class);
	setAlignItems(align_items_class);
	setAlignSelf(align_self_class);
	setPlaceContent(place_content_class);
	setPlaceItems(place_items_class);
	setPlaceSelf(place_self_class);

	// grid
	setGridTemplateColumns(grid_template_columns_class);
	setGridColsStart(grid_cols_start_class);
	setGridColsSpan(grid_cols_span_class);
	setGridColsEnd(grid_cols_end_class);
	setGridTemplateRows(grid_template_rows_class);
	setGridRowsStart(grid_rows_start_class);
	setGridRowsSpan(grid_rows_span_class);
	setGridRowsEnd(grid_rows_end_class);
	setGridAutoFlow(grid_auto_flow_class);
	setGridAutoColumns(grid_auto_columns_class);
	setGridAutoRows(grid_auto_rows_class);
	setGap(gap_class);
	setGapX(gap_x_class);
	setGapY(gap_y_class);

}


void ElementFlexAndGridWidget::setCustomTestValues()
{

}

bool ElementFlexAndGridWidget::setOrder(std::string className)
{
	order_widget_->setValue(className);
	order_class = order_widget_->getValue();

	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}
// flex
bool ElementFlexAndGridWidget::setBasis(std::string className)
{
	basis_widget_->setValue(className);
	basis_class = basis_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}




// bool ElementSizingWidget::setWidth(std::string className)
// {

// 	width_widget_->setValue(className);
// 	width_class = width_widget_->getValue();

// 	if(className.compare("none") == 0) return false;
// 	else {expand();return true;}
// }

bool ElementFlexAndGridWidget::setDirection(std::string className)
{
	direction_widget_->setValue(className);
	direction_class = direction_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setWrap(std::string className)
{
	wrap_widget_->setValue(className);
	wrap_class = wrap_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setGrowShrink(std::string className)
{
	grow_shrink_widget_->setValue(className);
	grow_shrink_class = grow_shrink_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setGrow(std::string className)
{
	grow_widget_->setValue(className);
	grow_class = grow_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setShrink(std::string className)
{
	shrink_widget_->setValue(className);
	shrink_class = shrink_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setJustifyContent(std::string className)
{
	justify_content_widget_->setValue(className);
	justify_content_class = justify_content_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setJustifyItems(std::string className)
{
	justify_items_widget_->setValue(className);
	justify_items_class = justify_items_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setJustifySelf(std::string className)
{
	justify_self_widget_->setValue(className);
	justify_self_class = justify_self_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setAlignContent(std::string className)
{
	align_content_widget_->setValue(className);
	align_content_class = align_content_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setAlignItems(std::string className)
{
	align_items_widget_->setValue(className);
	align_items_class = align_items_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setAlignSelf(std::string className)
{
	align_self_widget_->setValue(className);
	align_self_class = align_self_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setPlaceContent(std::string className)
{
	place_content_widget_->setValue(className);
	place_content_class = place_content_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setPlaceItems(std::string className)
{
	place_items_widget_->setValue(className);
	place_items_class = place_items_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setPlaceSelf(std::string className)
{
	place_self_widget_->setValue(className);
	place_self_class = place_self_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

// grid
bool ElementFlexAndGridWidget::setGridTemplateColumns(std::string className)
{
	grid_template_columns_widget_->setValue(className);
	grid_template_columns_class = grid_template_columns_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setGridColsStart(std::string className)
{
	grid_cols_start_widget_->setValue(className);
	grid_cols_start_class = grid_cols_start_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setGridColsSpan(std::string className)
{
	grid_cols_span_widget_->setValue(className);
	grid_cols_span_class = grid_cols_span_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setGridColsEnd(std::string className)
{
	grid_cols_end_widget_->setValue(className);
	grid_cols_end_class = grid_cols_end_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setGridTemplateRows(std::string className)
{
	grid_template_rows_widget_->setValue(className);
	grid_template_rows_class = grid_template_rows_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setGridRowsStart(std::string className)
{
	grid_rows_start_widget_->setValue(className);
	grid_rows_start_class = grid_rows_start_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setGridRowsSpan(std::string className)
{
	grid_rows_span_widget_->setValue(className);
	grid_rows_span_class = grid_rows_span_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setGridRowsEnd(std::string className)
{
	grid_rows_end_widget_->setValue(className);
	grid_rows_end_class = grid_rows_end_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setGridAutoFlow(std::string className)
{
	grid_auto_flow_widget_->setValue(className);
	grid_auto_flow_class = grid_auto_flow_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setGridAutoColumns(std::string className)
{
	grid_auto_columns_widget_->setValue(className);
	grid_auto_columns_class = grid_auto_columns_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setGridAutoRows(std::string className)
{
	grid_auto_rows_widget_->setValue(className);
	grid_auto_rows_class = grid_auto_rows_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setGap(std::string className)
{
	gap_widget_->setValue(className);
	gap_class = gap_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setGapX(std::string className)
{
	gap_x_widget_->setValue(className);
	gap_x_class = gap_x_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementFlexAndGridWidget::setGapY(std::string className)
{
	gap_y_widget_->setValue(className);
	gap_y_class = gap_y_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}
