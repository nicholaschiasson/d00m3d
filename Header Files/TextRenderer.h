#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

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
	void InitOverlay(Ogre::SceneManager*);
private:

};
#endif
