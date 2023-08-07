#include "include/App.h"
#include "include/Stylus.h"
#include "include/StylusTemplates.h"
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/DomElement.h>

#include "include/TailwindTheme.h"
#include <Wt/WBootstrap5Theme.h>
#include <Wt/WBootstrap2Theme.h>
#include <Wt/WTimer.h>

App::App(const Wt::WEnvironment &env)
	: Wt::WApplication(env)
{
	setTitle("Starter Wt Application");
	messageResourceBundle().use(appRoot() + "resources/xmlTest/Defoult-Styles/Elements");

	auto stylus_edditor = root()->addChild(std::make_unique<StylusEdditor>("resources/xmlTest/"));

	// auto wtCss = Wt::WLink("resources/themes/default/wt.css");
	auto defStyles = Wt::WLink("resources/themes/someDefaultStyles.css");

	// setCssTheme("polished");setCssFileCheckTimer
	// auto theme = std::make_shared<TailwindTheme>("polished");
	// theme->setCssFileCheckTimer();
	// theme->cssFileChanged().connect([=](){
	// 	Wt::WApplication::instance()->removeStyleSheet(Wt::WLink("resources/themes/tailwind/dist/tailwind.css"));
	// 	Wt::WApplication::instance()->refresh();
	// 	auto addStylesTimer = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WTimer>());
	// 	addStylesTimer->setInterval(std::chrono::milliseconds(3000));
	// 	addStylesTimer->setSingleShot(true);
	// 	addStylesTimer->timeout().connect([=](){
	// 		Wt::WApplication::instance()->useStyleSheet(Wt::WLink("resources/themes/tailwind/dist/tailwind.css"));
	// 		Wt::WApplication::instance()->refresh();
	// 	});
	// 	addStylesTimer->start();
	// });
	setCssTheme("default");
	// setTheme(std::move(theme));

	useStyleSheet(defStyles);
	
	// setTheme(std::make_shared<Wt::WBootstrap2Theme>());
	// removeStyleSheet(cssLink);
	// removeStyleSheet(tailwindCss);
	// useStyleSheet(tailwindCss);

	// add custom javascript files
	require("https://cdn.jsdelivr.net/npm/alpinejs@3.x.x/dist/cdn.min.js"); // testing for future integration with stylus
	require("https://cdn.tailwindcss.com");	// tailwind cdn for instant refresh of styles
	require("resources/Js/Utility.js"); // tailwind theme styles customize from here
	// add mesage resource bundle from templates
	std::vector<std::string> resources = stylus_edditor->getXmlFils();
	for(auto& resource : resources){
		messageResourceBundle().use(appRoot() + resource);
	}

	stylus_edditor->setTemplate("", "Application.xml", "app-root", "template");

	auto appDev = root()->addWidget(stylus_edditor->createDevApp());
	appDevId = appDev->id();
	stylus_edditor->appDevChanged().connect(this, [=](){
		root()->findById(appDevId)->removeFromParent();
		auto appDev = root()->addWidget(stylus_edditor->createDevApp());
		appDevId = appDev->id();
	});


	instance()->setInternalPath("/");


}

