#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H
#include "player_spacecraft.h"
#include "Ogre.h"

#include "OGRE/Overlay/OgreFontManager.h"
#include "OGRE/Overlay/OgreTextAreaOverlayElement.h"
#include "OGRE/Overlay/OgreOverlayManager.h"
#include "OGRE/Overlay/OgreOverlaySystem.h"
 

class TextRenderer
{
public:
	 TextRenderer();
    ~TextRenderer();
	void InitOverlay(PlayerSpacecraft* player, Ogre::SceneManager* scene_manager);
	void initPanel();
	void initTextAreas();
	void updateUI();
	void CreateTextArea(Ogre::TextAreaOverlayElement* text_area,std::string caption, int textSize, Ogre::ColourValue textColour, std::string uniqueTextID,Ogre::Vector2 textPosition);
	void CreateTextArea(std::string caption, int textSize, Ogre::ColourValue textColour, std::string uniqueTextID,Ogre::Vector2 textPosition);

private:
	Ogre::OverlayContainer* panel;
	Ogre::OverlayManager* overlayManager;
	PlayerSpacecraft* player;
	Ogre::TextAreaOverlayElement* text_area;
	Ogre::TextAreaOverlayElement* health;
	Ogre::TextAreaOverlayElement* speed;
	Ogre::TextAreaOverlayElement* energy;
	Ogre::TextAreaOverlayElement* fuel;
//	Ogre::Overlay* overlay;
};
#endif
