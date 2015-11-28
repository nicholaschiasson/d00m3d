#include "TextRenderer.h"

TextRenderer::TextRenderer(){

}

TextRenderer::~TextRenderer(){

}

 void TextRenderer::InitOverlay(Ogre::SceneManager* scene_manager){

    // Create and initialize the overlay system
    Ogre::OverlaySystem *os = new Ogre::OverlaySystem();
	
    scene_manager->addRenderQueueListener(os);

    // Initialize a font: assumes a standard Windows system
    Ogre::ResourceGroupManager& resource_group_manager = Ogre::ResourceGroupManager::getSingleton();
    resource_group_manager.addResourceLocation("C:\\Windows\\Fonts", "FileSystem");
    Ogre::FontManager& font_manager = Ogre::FontManager::getSingleton();
    Ogre::ResourcePtr font = font_manager.create("MyFont", "General");
    font->setParameter("type", "truetype");
    font->setParameter("source", "arial.ttf");
    font->setParameter("size", "26");
    font->setParameter("resolution", "96");
    font->load();

    // Create a panel for the overlay
    Ogre::OverlayManager& overlay_manager = Ogre::OverlayManager::getSingleton();
    Ogre::OverlayContainer* panel = (Ogre::OverlayContainer*) overlay_manager.createOverlayElement("Panel", "MyPanel");
    panel->setMetricsMode(Ogre::GMM_PIXELS);
    panel->setPosition(0, 0);
    panel->setDimensions(200, 100);
        
    // Create a text area and add it to the panel
    Ogre::TextAreaOverlayElement* text_area = static_cast<Ogre::TextAreaOverlayElement*>(overlay_manager.createOverlayElement("TextArea", "MyTextArea"));
    text_area->setMetricsMode(Ogre::GMM_PIXELS);
    text_area->setPosition(0, 0);
    text_area->setDimensions(200, 100);
    text_area->setFontName("MyFont");
    text_area->setCaption("Hello World");
    text_area->setCharHeight(26);
    text_area->setColour(Ogre::ColourValue(0.8, 0.0, 0.0));
    panel->addChild(text_area);

    // Create an overlay using the panel
    Ogre::Overlay* overlay = overlay_manager.create("MyOverlay");
    overlay->add2D(panel);
    overlay->show();
}
