#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <map>
#include <vector>

#include "OgreVector3.h"
#include "OIS.h"

enum INPUT_STATE { INPUT_STATE_UP = 0, INPUT_STATE_DOWN };
enum INPUT_SOURCE { INPUT_SOURCE_KEYBOARD, INPUT_SOURCE_MOUSE };
enum INPUT_EVENT { INPUT_EVENT_PRESS, INPUT_EVENT_RELEASE, INPUT_EVENT_HOLD, INPUT_EVENT_UP };

class InputManager
{
public:
	InputManager(OIS::Keyboard *k, OIS::Mouse *m);
	~InputManager();

	void Update(const Ogre::FrameEvent& fe);
	
	void RegisterCallback(void(*callback)(const Ogre::FrameEvent& fe), INPUT_SOURCE triggerSource, INPUT_EVENT triggerEvent, bool onMouseMove, int keyOrButtonCode);
	void UnregisterCallback(void(*callback)(const Ogre::FrameEvent& fe), INPUT_SOURCE triggerSource, INPUT_EVENT triggerEvent, bool onMouseMove, int keyOrButtonCode);

private:
	OIS::Mouse *mouse;
	OIS::Keyboard *keyboard;

	char shift;
	char ctrl;
	char alt;
	char keys[256];
	int mouseButtons;
	Ogre::Vector3 mouseLocation;
	bool mouseMoved;
	
	std::map<INPUT_EVENT, std::map<OIS::KeyCode, std::vector<void(*)(const Ogre::FrameEvent& fe)>>> keyboardCallbacks; 
	std::map<INPUT_EVENT, std::map<OIS::MouseButtonID, std::vector<void(*)(const Ogre::FrameEvent& fe)>>> mouseCallbacks; 

	int GetMouseButtonState(OIS::MouseButtonID button) const;
	void SetMouseButtonState(OIS::MouseButtonID button, INPUT_STATE state);
};

#endif // INPUT_MANAGER_H