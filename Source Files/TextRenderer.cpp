#include "TextRenderer.h"

TextRenderer::TextRenderer(){

}

TextRenderer::~TextRenderer(){

}

void TextRenderer::InitOverlay(PlayerSpacecraft* p, Ogre::SceneManager* scene_manager){
	player = p;

 // Create and initialize the overlay system
    Ogre::OverlaySystem *os = new Ogre::OverlaySystem();
    scene_manager->addRenderQueueListener(os);

	Ogre::FontManager& font_manager = Ogre::FontManager::getSingleton();
	Ogre::ResourcePtr font = font_manager.create("MyFont", "General");
	font->setParameter("type", "truetype");
	font->setParameter("source", "arial.ttf");
	font->setParameter("size", "26");
	font->setParameter("resolution", "96");
	font->load();

    // Create a panel for the overlay
    Ogre::OverlayManager& overlay_manager = Ogre::OverlayManager::getSingleton();
	overlayManager = &overlay_manager;

	initPanel();
	initTextAreas();

	    // Create an overlay using the panel
    Ogre::Overlay* overlay = overlayManager->create("MyOverlay");
    overlay->add2D(panel);
    overlay->show();
}

void TextRenderer::initPanel(){
    panel = (Ogre::OverlayContainer*) overlayManager->createOverlayElement("Panel", "MyPanel");
    panel->setMetricsMode(Ogre::GMM_PIXELS);
    panel->setPosition(0, 0);
    panel->setDimensions(200, 100);

}

void TextRenderer::initTextAreas(){

	health = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea","Health"));
    health->setMetricsMode(Ogre::GMM_PIXELS);
	health->setPosition(10,970);
    health->setDimensions(200, 100);
    health->setFontName("MyFont");
	health->setCharHeight(30);
	health->setColour(Ogre::ColourValue(1.0,1.0,1.0));
    panel->addChild(health);

	fuel = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea","Fuel"));
    fuel->setMetricsMode(Ogre::GMM_PIXELS);
	fuel->setPosition(520,970);
    fuel->setDimensions(200, 100);
    fuel->setFontName("MyFont");
	fuel->setCharHeight(30);
	fuel->setColour(Ogre::ColourValue(1.0,1.0,1.0));
    panel->addChild(fuel);
	
	fuel_bkp = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea","fuel_bkp"));
    fuel_bkp->setMetricsMode(Ogre::GMM_PIXELS);
	fuel_bkp->setPosition(520,910);
    fuel_bkp->setDimensions(200, 100);
    fuel_bkp->setFontName("MyFont");
	fuel_bkp->setCharHeight(30);
	fuel_bkp->setColour(Ogre::ColourValue(1.0,1.0,1.0));
    panel->addChild(fuel_bkp);

	fuel_health = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea","fuel_health"));
    fuel_health->setMetricsMode(Ogre::GMM_PIXELS);
	fuel_health->setPosition(520,940);
    fuel_health->setDimensions(200, 100);
    fuel_health->setFontName("MyFont");
	fuel_health->setCharHeight(30);
	fuel_health->setColour(Ogre::ColourValue(1.0,1.0,1.0));
    panel->addChild(fuel_health);

	energy = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea","Energy"));
    energy->setMetricsMode(Ogre::GMM_PIXELS);
	energy->setPosition(1150,970);
    energy->setDimensions(200, 100);
    energy->setFontName("MyFont");
	energy->setCharHeight(30);
	energy->setColour(Ogre::ColourValue(1.0,1.0,1.0));
    panel->addChild(energy);

	energy_bkp = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea","energy_bkp"));
    energy_bkp->setMetricsMode(Ogre::GMM_PIXELS);
	energy_bkp->setPosition(1150,910);
    energy_bkp->setDimensions(200, 100);
    energy_bkp->setFontName("MyFont");
	energy_bkp->setCharHeight(30);
	energy_bkp->setColour(Ogre::ColourValue(1.0,1.0,1.0));
    panel->addChild(energy_bkp);

	artillery_health = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea","ARTILLERYHEALTH"));
    artillery_health->setMetricsMode(Ogre::GMM_PIXELS);
	artillery_health->setPosition(1150,940);
    artillery_health->setDimensions(200, 100);
    artillery_health->setFontName("MyFont");
	artillery_health->setCharHeight(30);
	artillery_health->setColour(Ogre::ColourValue(1.0,1.0,1.0));
    panel->addChild(artillery_health);

	speed = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea","Speed"));
    speed->setMetricsMode(Ogre::GMM_PIXELS);
	speed->setPosition(1650,970);
    speed->setDimensions(200, 100);
    speed->setFontName("MyFont");
	speed->setCharHeight(30);
	speed->setColour(Ogre::ColourValue(1.0,1.0,1.0));
    panel->addChild(speed);

	defense = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea","defense"));
    defense->setMetricsMode(Ogre::GMM_PIXELS);
	defense->setPosition(260,970);
    defense->setDimensions(200, 100);
    defense->setFontName("MyFont");
	defense->setCharHeight(30);
	defense->setColour(Ogre::ColourValue(1.0,1.0,1.0));
    panel->addChild(defense);

	defense_bkp = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea","defense_bkp"));
    defense_bkp->setMetricsMode(Ogre::GMM_PIXELS);
	defense_bkp->setPosition(260,940);
    defense_bkp->setDimensions(200, 100);
    defense_bkp->setFontName("MyFont");
	defense_bkp->setCharHeight(30);
	defense_bkp->setColour(Ogre::ColourValue(1.0,1.0,1.0));
    panel->addChild(defense_bkp);

	navigation = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea","navigation"));
    navigation->setMetricsMode(Ogre::GMM_PIXELS);
	navigation->setPosition(850,970);
    navigation->setDimensions(200, 100);
    navigation->setFontName("MyFont");
	navigation->setCharHeight(30);
	navigation->setColour(Ogre::ColourValue(1.0,1.0,1.0));
    panel->addChild(navigation);

	navigation_bkp = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea","navigation_bkp"));
    navigation_bkp->setMetricsMode(Ogre::GMM_PIXELS);
	navigation_bkp->setPosition(850,940);
    navigation_bkp->setDimensions(200, 100);
    navigation_bkp->setFontName("MyFont");
	navigation_bkp->setCharHeight(30);
	navigation_bkp->setColour(Ogre::ColourValue(1.0,1.0,1.0));
    panel->addChild(navigation_bkp);

	FPS = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea","FPS"));
    FPS->setMetricsMode(Ogre::GMM_PIXELS);
	FPS->setPosition(1500,30);
    FPS->setDimensions(200, 100);
    FPS->setFontName("MyFont");
	FPS->setCharHeight(30);
	FPS->setColour(Ogre::ColourValue(1.0,1.0,1.0));
    panel->addChild(FPS);

}

void TextRenderer::updateUI(){
	health->setCaption("HEALTH: " + std::to_string((int)player->getHealth())+ "%");

	fuel->setCaption("FUEL: " + std::to_string((int)player->getActiveSystem(SystemComponent::SYSTEM_FUEL)->getValue())+ "%");
	fuel_health->setCaption("FUEL HEALTH: " + std::to_string((int)player->getActiveSystem(SystemComponent::SYSTEM_FUEL)->getHealth())+ "%");
	fuel_bkp->setCaption("BACKUPS: " + std::to_string((int)player->getNumSystemBackups(SystemComponent::SYSTEM_FUEL)));


	energy->setCaption("ENERGY: " + std::to_string((int)player->getActiveSystem(SystemComponent::SYSTEM_ARTILLERY)->getValue())+ "%");
	artillery_health->setCaption("ARTILLERY HEALTH: " + std::to_string((int)player->getActiveSystem(SystemComponent::SYSTEM_ARTILLERY)->getHealth())+ "%");
	energy_bkp->setCaption("BACKUPS: " + std::to_string((int)player->getNumSystemBackups(SystemComponent::SYSTEM_ARTILLERY)));


	defense->setCaption("DEFENSE: " +std::to_string((int)player->getActiveSystem(SystemComponent::SYSTEM_DEFENSE)->getHealth()) + "%");
	defense_bkp->setCaption("BACKUPS: " +std::to_string((int)player->getNumSystemBackups(SystemComponent::SYSTEM_DEFENSE)));
	
	navigation->setCaption("NAVIGATION: " +std::to_string((int)player->getActiveSystem(SystemComponent::SYSTEM_NAVIGATIONAL)->getHealth()) + "%");
	navigation_bkp->setCaption("BACKUPS: " +std::to_string((int)player->getNumSystemBackups(SystemComponent::SYSTEM_NAVIGATIONAL)));

	speed->setCaption("SPEED: " + std::to_string((int)player->getSpeed())+ "AU/h");
}

void TextRenderer::updateFPS(int ff){
	FPS->setCaption("FPS: " + std::to_string(ff));
}
