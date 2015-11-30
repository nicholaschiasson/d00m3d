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
	fuel->setPosition(500,970);
    fuel->setDimensions(200, 100);
    fuel->setFontName("MyFont");
	fuel->setCharHeight(30);
	fuel->setColour(Ogre::ColourValue(1.0,1.0,1.0));
    panel->addChild(fuel);

	energy = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea","Energy"));
    energy->setMetricsMode(Ogre::GMM_PIXELS);
	energy->setPosition(1000,970);
    energy->setDimensions(200, 100);
    energy->setFontName("MyFont");
	energy->setCharHeight(30);
	energy->setColour(Ogre::ColourValue(1.0,1.0,1.0));
    panel->addChild(energy);

	speed = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea","Speed"));
    speed->setMetricsMode(Ogre::GMM_PIXELS);
	speed->setPosition(1500,970);
    speed->setDimensions(200, 100);
    speed->setFontName("MyFont");
	speed->setCharHeight(30);
	speed->setColour(Ogre::ColourValue(1.0,1.0,1.0));
    panel->addChild(speed);

}

void TextRenderer::updateUI(){
	health->setCaption("HEALTH: " + std::to_string((int)player->getHealth())+ "%");
	fuel->setCaption("FUEL: " + std::to_string((int)player->getFuel())+ "%");
    energy->setCaption("ENERGY: " + std::to_string((int)player->getEnergy())+ "%");
	speed->setCaption("SPEED: " + std::to_string((int)player->getSpeed())+ "mph");
}

void TextRenderer::CreateTextArea(std::string caption, int textSize, Ogre::ColourValue textColour, std::string uniqueTextID,Ogre::Vector2 textPosition){       
    // Create a text area and add it to the panel
    text_area = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea",uniqueTextID));
    text_area->setMetricsMode(Ogre::GMM_PIXELS);
	text_area->setPosition(textPosition.x,textPosition.y);
    text_area->setDimensions(200.0f, 100.0f);
    text_area->setFontName("MyFont");
	text_area->setCaption(caption);
	text_area->setCharHeight((float)textSize);
	text_area->setColour(textColour);

    panel->addChild(text_area);

}

void TextRenderer::CreateTextArea(Ogre::TextAreaOverlayElement* text_area,std::string caption, int textSize, Ogre::ColourValue textColour, std::string uniqueTextID,Ogre::Vector2 textPosition){       
    // Create a text area and add it to the panel
    text_area = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea",uniqueTextID));
    text_area->setMetricsMode(Ogre::GMM_PIXELS);
	text_area->setPosition(textPosition.x,textPosition.y);
    text_area->setDimensions(200, 100);
    text_area->setFontName("MyFont");
	text_area->setCaption(caption);
	text_area->setCharHeight((float)textSize);
	text_area->setColour(textColour);

    panel->addChild(text_area);

}

