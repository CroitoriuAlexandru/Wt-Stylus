#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxClassChanger.h"
#include "SelectionGroupClassChanger.h"
#include <Wt/WDialog.h>
#include <Wt/WPanel.h>
#include <Wt/WGroupBox.h>
#include <Wt/WButtonGroup.h>
#include <Wt/WRadioButton.h>

struct FlexAndGridData
{
	std::string order = "none";
	
	// flexbox
	std::string basis = "none";
	std::string direction = "none";
	std::string wrap = "none";
	std::string grow_shrink = "none";
	std::string grow = "none";
	std::string shrink = "none";
	std::string justify_content = "none";
	std::string justify_items = "none";
	std::string justify_self = "none";

	std::string align_content = "none";
	std::string align_items = "none";
	std::string align_self = "none";

	std::string place_content = "none";
	std::string place_items = "none";
	std::string place_self = "none";

	// grid
	std::string grid_template_columns = "none";
	std::string grid_cols_start = "none";
	std::string grid_cols_span = "none";
	std::string grid_cols_end = "none";
	std::string grid_template_rows = "none";
	std::string grid_rows_start = "none";
	std::string grid_rows_span = "none";
	std::string grid_rows_end = "none";
	std::string grid_auto_flow = "none";
	std::string grid_auto_columns = "none";
	std::string grid_auto_rows = "none";
	std::vector<std::string> gap;

};


class ElementFlexAndGridWidget : public Wt::WPanel
{
public:
	ElementFlexAndGridWidget(std::shared_ptr<Config> tailwindConfig);
	// margin and padding at the moment


	void setClasses(FlexAndGridData flexAndGridData);
    Wt::Signal<std::string>& styleChanged() { return styleChanged_; };
	
	std::string getStyles();
	void resetStyles();

	bool setOrder(std::string className);
	// flex
	bool setBasis(std::string className);
	bool setDirection(std::string className);
	bool setWrap(std::string className);
	bool setGrowShrink(std::string className);
	bool setGrow(std::string className);
	bool setShrink(std::string className);
	
	bool setJustifyContent(std::string className);
	bool setJustifyItems(std::string className);
	bool setJustifySelf(std::string className);

	bool setAlignContent(std::string className);
	bool setAlignItems(std::string className);
	bool setAlignSelf(std::string className);

	bool setPlaceContent(std::string className);
	bool setPlaceItems(std::string className);
	bool setPlaceSelf(std::string className);

	// grid
	bool setGridTemplateColumns(std::string className);
	bool setGridColsStart(std::string className);
	bool setGridColsSpan(std::string className);
	bool setGridColsEnd(std::string className);
	bool setGridTemplateRows(std::string className);
	bool setGridRowsStart(std::string className);
	bool setGridRowsSpan(std::string className);
	bool setGridRowsEnd(std::string className);
	bool setGridAutoFlow(std::string className);
	bool setGridAutoColumns(std::string className);
	bool setGridAutoRows(std::string className);
	bool setGap(std::string className);
	bool setGapX(std::string className);
	bool setGapY(std::string className);

	void setDisplayLayout(std::string layout);
private:
	Wt::WContainerWidget* 		flex_container;
	Wt::WContainerWidget* 		grid_container;


	ComboBoxClassChanger* 		order_widget_;

	// flex
	ComboBoxClassChanger* basis_widget_;
	ComboBoxClassChanger* direction_widget_;	
	ComboBoxClassChanger* wrap_widget_;
	ComboBoxClassChanger* grow_shrink_widget_;
	ComboBoxClassChanger* grow_widget_;
	ComboBoxClassChanger* shrink_widget_;
	
	ComboBoxClassChanger* justify_content_widget_;
	ComboBoxClassChanger* justify_items_widget_;
	ComboBoxClassChanger* justify_self_widget_;
	
	ComboBoxClassChanger* align_content_widget_;
	ComboBoxClassChanger* align_items_widget_;
	ComboBoxClassChanger* align_self_widget_;

	ComboBoxClassChanger* place_content_widget_;
	ComboBoxClassChanger* place_items_widget_;
	ComboBoxClassChanger* place_self_widget_;

	// grid
	ComboBoxClassChanger* grid_template_columns_widget_;
	ComboBoxClassChanger* grid_cols_start_widget_;
	ComboBoxClassChanger* grid_cols_span_widget_;
	ComboBoxClassChanger* grid_cols_end_widget_;
	ComboBoxClassChanger* grid_template_rows_widget_;
	ComboBoxClassChanger* grid_rows_start_widget_;
	ComboBoxClassChanger* grid_rows_span_widget_;
	ComboBoxClassChanger* grid_rows_end_widget_;
	ComboBoxClassChanger* grid_auto_flow_widget_;
	ComboBoxClassChanger* grid_auto_columns_widget_;
	ComboBoxClassChanger* grid_auto_rows_widget_;
	ComboBoxClassChanger* gap_widget_;
	ComboBoxClassChanger* gap_x_widget_;
	ComboBoxClassChanger* gap_y_widget_;


	std::string order_class = "none";

	// flex
	std::string basis_class = "none";
	std::string direction_class = "none";
	std::string wrap_class = "none";
	std::string grow_shrink_class = "none";
	std::string grow_class = "none";
	std::string shrink_class = "none";
	std::string justify_content_class = "none";
	std::string justify_items_class = "none";
	std::string justify_self_class = "none";

	std::string align_content_class = "none";
	std::string align_items_class = "none";
	std::string align_self_class = "none";

	std::string self_content_class = "none";
	std::string self_items_class = "none";
	std::string self_self_class = "none";

	std::string place_content_class = "none";
	std::string place_items_class = "none";
	std::string place_self_class = "none";

	// grid
	std::string grid_template_columns_class = "none";
	std::string grid_cols_start_class = "none";
	std::string grid_cols_span_class = "none";
	std::string grid_cols_end_class = "none";
	std::string grid_template_rows_class = "none";
	std::string grid_rows_start_class = "none";
	std::string grid_rows_span_class = "none";
	std::string grid_rows_end_class = "none";
	std::string grid_auto_flow_class = "none";
	std::string grid_auto_columns_class = "none";
	std::string grid_auto_rows_class = "none";
	std::string gap_class = "none";
	std::string gap_x_class = "none";
	std::string gap_y_class = "none";


	void setCustomTestValues();
	
	std::shared_ptr<Config> tailwindConfig_;
	
	Wt::Signal<std::string> styleChanged_;
};