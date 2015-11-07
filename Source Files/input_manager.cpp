#include "input_manager.h"

InputManager::InputManager(OIS::Keyboard *k, OIS::Mouse *m)
{
	keyboard = k;
	mouse = m;
	
	shift = INPUT_STATE_UP;
	ctrl = INPUT_STATE_UP;
	alt = INPUT_STATE_UP;
	keyboard->copyKeyStates(keys);
	OIS::MouseState mouseState = mouse->getMouseState();
	mouseButtons = mouseState.buttons;
	mouseLocation = Ogre::Vector3((float)mouseState.X.abs, (float)mouseState.Y.abs, (float)mouseState.Z.abs);
}

InputManager::~InputManager()
{

}

void InputManager::Update(const Ogre::FrameEvent& fe)
{
	keyboard->capture();
	mouse->capture();

	OIS::MouseState mouseState = mouse->getMouseState();
	if (mouseState.X.abs != (int)mouseLocation.x || mouseState.Y.abs != (int)mouseLocation.y || mouseState.Z.abs != (int)mouseLocation.z)
	{
		mouseMoved = true;
	}
	else
	{
		mouseMoved = false;
	}
	mouseLocation = Ogre::Vector3((float)mouseState.X.abs, (float)mouseState.Y.abs, (float)mouseState.Z.abs);

	for (int i = 0; i < 8; i++)
	{
		if (mouseState.buttonDown((OIS::MouseButtonID)i))
		{
			if (GetMouseButtonState((OIS::MouseButtonID)i) == INPUT_STATE_UP)
			{
				// Press
				for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe)>::iterator it = mouseCallbacks[INPUT_EVENT_PRESS][(OIS::MouseButtonID)i].begin();
					it != mouseCallbacks[INPUT_EVENT_PRESS][(OIS::MouseButtonID)i].end(); ++it)
				{
					int index = (int)(it - mouseCallbacks[INPUT_EVENT_PRESS][(OIS::MouseButtonID)i].begin());
					(*it)(mouseCallbacks[INPUT_EVENT_PRESS][(OIS::MouseButtonID)i][index], fe);
				}
			}
			// Hold
			for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe)>::iterator it = mouseCallbacks[INPUT_EVENT_HOLD][(OIS::MouseButtonID)i].begin();
				it != mouseCallbacks[INPUT_EVENT_HOLD][(OIS::MouseButtonID)i].end(); ++it)
			{
				int index = (int)(it - mouseCallbacks[INPUT_EVENT_HOLD][(OIS::MouseButtonID)i].begin());
				(*it)(mouseCallbacks[INPUT_EVENT_HOLD][(OIS::MouseButtonID)i][index], fe);
			}
		}
		else if (!mouseState.buttonDown((OIS::MouseButtonID)i))
		{
			if (GetMouseButtonState((OIS::MouseButtonID)i) == INPUT_STATE_DOWN)
			{
				// Release
				for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe)>::iterator it = mouseCallbacks[INPUT_EVENT_RELEASE][(OIS::MouseButtonID)i].begin();
					it != mouseCallbacks[INPUT_EVENT_RELEASE][(OIS::MouseButtonID)i].end(); ++it)
				{
					int index = (int)(it - mouseCallbacks[INPUT_EVENT_RELEASE][(OIS::MouseButtonID)i].begin());
					(*it)(mouseCallbacks[INPUT_EVENT_RELEASE][(OIS::MouseButtonID)i][index], fe);
				}
			}
			// Up
			for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe)>::iterator it = mouseCallbacks[INPUT_EVENT_UP][(OIS::MouseButtonID)i].begin();
				it != mouseCallbacks[INPUT_EVENT_UP][(OIS::MouseButtonID)i].end(); ++it)
			{
				int index = (int)(it - mouseCallbacks[INPUT_EVENT_UP][(OIS::MouseButtonID)i].begin());
				(*it)(mouseCallbacks[INPUT_EVENT_UP][(OIS::MouseButtonID)i][index], fe);
			}
		}
	}
	mouseButtons = mouse->getMouseState().buttons;
	
	/*
	// All this modifier code is likely not necessary since the modifier key codes are included in the OIS::KeyCodes
	
	if (keyboard->isModifierDown(keyboard->Shift))
	{
		if (shift == INPUT_STATE_UP)
		{
			// Press

		}
		// Hold

	}
	else if (!keyboard->isModifierDown(keyboard->Shift))
	{
		if (shift == INPUT_STATE_DOWN)
		{
			// Release

		}
		// Up

	}

	if (keyboard->isModifierDown(keyboard->Ctrl))
	{
		if (ctrl == INPUT_STATE_UP)
		{
			// Press

		}
		// Hold

	}
	else if (!keyboard->isModifierDown(keyboard->Ctrl))
	{
		if (ctrl == INPUT_STATE_DOWN)
		{
			// Release

		}
		// Up

	}
	
	if (keyboard->isModifierDown(keyboard->Alt))
	{
		if (alt == INPUT_STATE_UP)
		{
			// Press

		}
		// Hold

	}
	else if (!keyboard->isModifierDown(keyboard->Alt))
	{
		if (alt == INPUT_STATE_DOWN)
		{
			// Release

		}
		// Up

	}
	
	shift = (char)(keyboard->isModifierDown(keyboard->Shift));
	ctrl = (char)(keyboard->isModifierDown(keyboard->Ctrl));
	alt = (char)(keyboard->isModifierDown(keyboard->Alt));
	*/
	
	for (int i = 0; i < 256; i++)
	{
		if (keyboard->isKeyDown((OIS::KeyCode)i))
		{
			if (keys[i] == INPUT_STATE_UP)
			{
				// Press
				for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe)>::iterator it = keyboardCallbacks[INPUT_EVENT_PRESS][(OIS::KeyCode)i].begin();
					it != keyboardCallbacks[INPUT_EVENT_PRESS][(OIS::KeyCode)i].end(); ++it)
				{
					int index = (int)(it - keyboardCallbacks[INPUT_EVENT_PRESS][(OIS::KeyCode)i].begin());
					(*it)(keyboardContexts[INPUT_EVENT_PRESS][(OIS::KeyCode)i][index], fe);
				}
			}
			// Hold
			for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe)>::iterator it = keyboardCallbacks[INPUT_EVENT_HOLD][(OIS::KeyCode)i].begin();
				it != keyboardCallbacks[INPUT_EVENT_HOLD][(OIS::KeyCode)i].end(); ++it)
			{
				int index = (int)(it - keyboardCallbacks[INPUT_EVENT_HOLD][(OIS::KeyCode)i].begin());
				(*it)(keyboardContexts[INPUT_EVENT_HOLD][(OIS::KeyCode)i][index], fe);
			}
		}
		else if (!keyboard->isKeyDown((OIS::KeyCode)i))
		{
			if (keys[i] == INPUT_STATE_DOWN)
			{
				// Release
				for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe)>::iterator it = keyboardCallbacks[INPUT_EVENT_RELEASE][(OIS::KeyCode)i].begin();
					it != keyboardCallbacks[INPUT_EVENT_RELEASE][(OIS::KeyCode)i].end(); ++it)
				{
					int index = (int)(it - keyboardCallbacks[INPUT_EVENT_RELEASE][(OIS::KeyCode)i].begin());
				(*it)(keyboardContexts[INPUT_EVENT_RELEASE][(OIS::KeyCode)i][index], fe);
				}
			}
			// Up
			for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe)>::iterator it = keyboardCallbacks[INPUT_EVENT_UP][(OIS::KeyCode)i].begin();
				it != keyboardCallbacks[INPUT_EVENT_UP][(OIS::KeyCode)i].end(); ++it)
			{
				int index = (int)(it - keyboardCallbacks[INPUT_EVENT_UP][(OIS::KeyCode)i].begin());
				(*it)(keyboardContexts[INPUT_EVENT_UP][(OIS::KeyCode)i][index], fe);
			}
		}
	}
	keyboard->copyKeyStates(keys);
}

void InputManager::RegisterCallback(void *context, void(*callback)(void *context, const Ogre::FrameEvent& fe), INPUT_SOURCE triggerSource, INPUT_EVENT triggerEvent, bool onMouseMove, int keyOrButtonCode)
{
	if (triggerSource == INPUT_SOURCE_KEYBOARD)
	{
		keyboardCallbacks[triggerEvent][(OIS::KeyCode)keyOrButtonCode].push_back(callback);
		keyboardContexts[triggerEvent][(OIS::KeyCode)keyOrButtonCode].push_back(context);
	}
	else if (triggerSource == INPUT_SOURCE_MOUSE)
	{
		mouseCallbacks[triggerEvent][(OIS::MouseButtonID)keyOrButtonCode].push_back(callback);
		mouseContexts[triggerEvent][(OIS::MouseButtonID)keyOrButtonCode].push_back(context);
	}
}

void InputManager::UnregisterCallback(void *context, void(*callback)(void *context, const Ogre::FrameEvent& fe), INPUT_SOURCE triggerSource, INPUT_EVENT triggerEvent, bool onMouseMove, int keyOrButtonCode)
{
	if (triggerSource == INPUT_SOURCE_KEYBOARD)
	{
		std::vector<void(*)(void *context, const Ogre::FrameEvent& fe)>::iterator callbackIt = std::find(keyboardCallbacks[triggerEvent][(OIS::KeyCode)keyOrButtonCode].begin(),
			keyboardCallbacks[triggerEvent][(OIS::KeyCode)keyOrButtonCode].end(), callback);
		int index = (int)(callbackIt - keyboardCallbacks[triggerEvent][(OIS::KeyCode)keyOrButtonCode].begin());
		std::vector<void *>::iterator contextIt = keyboardContexts[triggerEvent][(OIS::KeyCode)keyOrButtonCode].begin() + index;
		keyboardCallbacks[triggerEvent][(OIS::KeyCode)keyOrButtonCode].erase(callbackIt);
		keyboardContexts[triggerEvent][(OIS::KeyCode)keyOrButtonCode].erase(contextIt);
		
	}
	else if (triggerSource == INPUT_SOURCE_MOUSE)
	{
		std::vector<void(*)(void *context, const Ogre::FrameEvent& fe)>::iterator callbackIt = std::find(mouseCallbacks[triggerEvent][(OIS::MouseButtonID)keyOrButtonCode].begin(),
			mouseCallbacks[triggerEvent][(OIS::MouseButtonID)keyOrButtonCode].end(), callback);
		int index = (int)(callbackIt - mouseCallbacks[triggerEvent][(OIS::MouseButtonID)keyOrButtonCode].begin());
		std::vector<void *>::iterator contextIt = mouseContexts[triggerEvent][(OIS::MouseButtonID)keyOrButtonCode].begin() + index;
		mouseCallbacks[triggerEvent][(OIS::MouseButtonID)keyOrButtonCode].erase(callbackIt);
		mouseContexts[triggerEvent][(OIS::MouseButtonID)keyOrButtonCode].erase(contextIt);
	}
}

int InputManager::GetMouseButtonState(OIS::MouseButtonID button) const
{
	return ((mouseButtons & ( 1L << button )) == 0) ? INPUT_STATE_UP : INPUT_STATE_DOWN;
}

void InputManager::SetMouseButtonState(OIS::MouseButtonID button, INPUT_STATE state)
{
	if (state == INPUT_STATE_UP)
	{
		mouseButtons &= ~(1L << button);
	}
	else if (state == INPUT_STATE_DOWN)
	{
		mouseButtons |= 1L << button;
	}
}