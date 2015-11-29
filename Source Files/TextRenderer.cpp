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
	//CreateTextArea(caption,textSize,textColour,uniqueTextID,textPosition);
	CreateTextArea(std::to_string(player->getHealth()), 30, Ogre::ColourValue(1.0,1.0,1.0),"Heap",Ogre::Vector2(130.0,980));

}

void TextRenderer::updateUI(){
	text_area->setCaption("HEALTH: " + std::to_string((int)player->getHealth())+ "%");
	

}

void TextRenderer::CreateTextArea(std::string caption, int textSize, Ogre::ColourValue textColour, std::string uniqueTextID,Ogre::Vector2 textPosition){       
    // Create a text area and add it to the panel
    text_area = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea",uniqueTextID));
    text_area->setMetricsMode(Ogre::GMM_PIXELS);
	text_area->setPosition(textPosition.x,textPosition.y);
    text_area->setDimensions(200, 100);
    text_area->setFontName("MyFont");
	text_area->setCaption(caption);
	text_area->setCharHeight(textSize);
	text_area->setColour(textColour);
    panel->addChild(text_area);

}

