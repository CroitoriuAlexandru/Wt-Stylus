#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxes.h"
#include <Wt/WDialog.h>
#include <Wt/WPanel.h>

struct SizingData
{
	std::string width = "none";
	std::string minWidth = "none";
	std::string maxWidth = "none";

	std::string height = "none";
	std::string minHeight = "none";
	std::string maxHeight = "none";
};


class ElementSizingWidget : public Wt::WPanel
{
public:
	ElementSizingWidget(std::shared_ptr<Config> tailwindConfig);
	// margin and padding at the moment

	void setClasses(SizingData sizing);
    Wt::Signal<>& styleChanged() { return styleChanged_; }
	std::string getStyles();
	void resetStyles();

private:
	void setCustomTestValues();
	
    std::shared_ptr<Config> tailwindConfig_;
	Wt::WTemplate* content_temp;

	ComboBoxClassWithCustoms* width_widget_;
	ComboBoxClassWithCustoms* minWidth_widget_;
	ComboBoxClassWithCustoms* maxWidth_widget_;

	ComboBoxClassWithCustoms* height_widget_;
	ComboBoxClassWithCustoms* minHeight_widget_;
	ComboBoxClassWithCustoms* maxHeight_widget_;

	Wt::Signal<> styleChanged_;

	// sizing custom regexp
	std::regex regex_custom_sizing =  std::regex("[!]?[w|h]-\\[[\\S]*\\]");
	std::regex regex_custom_min_max_sizing =  std::regex("[!]?[min|max]-w-\\[[\\S]*\\]");

};

