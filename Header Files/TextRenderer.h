#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H
#include "player_spacecraft.h"
#include "Ogre.h"
#include "system_component.h"
#include "OGRE/Overlay/OgreFontManager.h"
#include "OGRE/Overlay/OgreTextAreaOverlayElement.h"
#include "OGRE/Overlay/OgreOverlayManager.h"
#include "OGRE/Overlay/OgreOverlaySystem.h"
 

class TextRenderer
{
public:
	 TextRenderer();
    ~TextRenderer();
	void InitOverlay(PlayerSpacecraft* player, Ogre::SceneManager* scene_manager, Ogre::Viewport* v);
	void initPanel();
	void initTextAreas();
	void updateUI();
	void CreateTextArea(Ogre::TextAreaOverlayElement* text_area,std::string caption, int textSize, Ogre::ColourValue textColour, std::string uniqueTextID,Ogre::Vector2 textPosition);
	void CreateTextArea(std::string caption, int textSize, Ogre::ColourValue textColour, std::string uniqueTextID,Ogre::Vector2 textPosition);
	void updateFPS(int FPS);

private:
	Ogre::OverlayContainer* panel;
	Ogre::OverlayManager* overlayManager;
	PlayerSpacecraft* player;

	Ogre::Viewport* viewport;

	Ogre::TextAreaOverlayElement* health;

	Ogre::TextAreaOverlayElement* speed;

	Ogre::TextAreaOverlayElement* energy;
	Ogre::TextAreaOverlayElement* artillery_health;
	Ogre::TextAreaOverlayElement* energy_bkp;

	Ogre::TextAreaOverlayElement* fuel;
	Ogre::TextAreaOverlayElement* fuel_bkp;
	Ogre::TextAreaOverlayElement* fuel_health;

	Ogre::TextAreaOverlayElement* defense;
	Ogre::TextAreaOverlayElement* defense_bkp;

	Ogre::TextAreaOverlayElement* navigation;
	Ogre::TextAreaOverlayElement* navigation_bkp;

	Ogre::TextAreaOverlayElement* death;

	Ogre::TextAreaOverlayElement* FPS;
};
#endif
