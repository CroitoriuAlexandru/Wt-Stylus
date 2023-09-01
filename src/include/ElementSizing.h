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
    Wt::Signal<std::string>& styleChanged() { return styleChanged_; }
	std::string getStyles();
	void resetStyles();



	bool setWidth(std::string className);
	bool setHeight(std::string className);
	bool setMinWidth(std::string className);
	bool setMinHeight(std::string className);
	bool setMaxWidth(std::string className);
	bool setMaxHeight(std::string className);
	
	
private:
	ComboBoxClassChanger* width_widget_;
	ComboBoxClassChanger* minWidth_widget_;
	ComboBoxClassChanger* maxWidth_widget_;

	ComboBoxClassChanger* height_widget_;
	ComboBoxClassChanger* minHeight_widget_;
	ComboBoxClassChanger* maxHeight_widget_;
	
	std::string width_class = "none";
	std::string minWidth_class = "none";
	std::string maxWidth_class = "none";
	std::string height_class = "none";
	std::string minHeight_class = "none";
	std::string maxHeight_class = "none";

	void setCustomTestValues();
	
    std::shared_ptr<Config> tailwindConfig_;

	Wt::Signal<std::string> styleChanged_;

	// sizing custom regexp
	std::regex regex_custom_sizing =  std::regex("[!]?[w|h]-\\[[\\S]*\\]");
	std::regex regex_custom_min_max_sizing =  std::regex("[!]?[min|max]-w-\\[[\\S]*\\]");

};

