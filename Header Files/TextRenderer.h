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
	void CreateTextArea(std::string caption, int textSize, Ogre::ColourValue textColour, std::string uniqueTextID,Ogre::Vector2 textPosition);
private:
	Ogre::OverlayContainer* panel;
	Ogre::OverlayManager* overlayManager;
	PlayerSpacecraft* player;
	Ogre::TextAreaOverlayElement* health;
	Ogre::TextAreaOverlayElement* text_area;

//	Ogre::Overlay* overlay;
};
#endif
