#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <map>
#include <vector>

#include "OgreVector2.h"
#include "OgreVector3.h"
#include "OIS.h"

enum INPUT_STATE { INPUT_STATE_UP = 0, INPUT_STATE_DOWN };
enum INPUT_SOURCE { INPUT_SOURCE_NONE, INPUT_SOURCE_KEYBOARD, INPUT_SOURCE_MOUSE };
enum INPUT_EVENT { INPUT_EVENT_NONE, INPUT_EVENT_PRESS, INPUT_EVENT_RELEASE, INPUT_EVENT_HOLD, INPUT_EVENT_UP };

class InputManager
{
public:
	InputManager();
	~InputManager();
	
	void Initialize(OIS::Keyboard *k, OIS::Mouse *m);
	void Update(const Ogre::FrameEvent& fe);
	
	void RegisterCallback(void *context, void(*callback)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2), INPUT_SOURCE triggerSource, INPUT_EVENT triggerEvent, bool onMouseMove, int keyOrButtonCode);
	void UnregisterCallback(void *context, void(*callback)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2), INPUT_SOURCE triggerSource, INPUT_EVENT triggerEvent, bool onMouseMove, int keyOrButtonCode);

	void CompensateManualMouseSetPosition(int x, int y);

	void Interrupt();

private:
	OIS::Mouse *mouse;
	OIS::Keyboard *keyboard;

	bool interrupted;

	char shift;
	char ctrl;
	char alt;
	char keys[256];
	int mouseButtons;
	Ogre::Vector3 previousMouseLocation;
	Ogre::Vector3 mouseLocation;
	Ogre::Vector2 mouseLocationCompensation;
	bool firstMoustMove;
	bool mouseMoved;
	
	std::map<bool, std::vector<void(*)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2)>> noInputCallbacks;
	std::map<bool, std::vector<void *>> noInputContexts;
	std::map<INPUT_EVENT, std::map<bool, std::map<OIS::KeyCode, std::vector<void(*)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2)>>>> keyboardCallbacks;
	std::map<INPUT_EVENT, std::map<bool, std::map<OIS::KeyCode, std::vector<void *>>>> keyboardContexts;
	std::map<INPUT_EVENT, std::map<bool, std::map<OIS::MouseButtonID, std::vector<void(*)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2)>>>> mouseCallbacks;
	std::map<INPUT_EVENT, std::map<bool, std::map<OIS::MouseButtonID, std::vector<void *>>>> mouseContexts;

	int GetMouseButtonState(OIS::MouseButtonID button) const;
	void SetMouseButtonState(OIS::MouseButtonID button, INPUT_STATE state);
};

#endif // INPUT_MANAGER_H