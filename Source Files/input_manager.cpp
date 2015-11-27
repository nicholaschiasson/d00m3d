#include "input_manager.h"

InputManager::InputManager()
{	
	interrupted = false;
	shift = INPUT_STATE_UP;
	ctrl = INPUT_STATE_UP;
	alt = INPUT_STATE_UP;
	for (int i = 0; i < 255; i++)
	{
		keys[i] = INPUT_STATE_UP;
	}
	mouseButtons = 0;
	mouseLocation = Ogre::Vector3(0.0f, 0.0f, 0.0f);
	previousMouseLocation = Ogre::Vector3(0.0f, 0.0f, 0.0f);
	mouseLocationCompensation = Ogre::Vector2(0.0f, 0.0f);
	firstMoustMove = false;
}

InputManager::~InputManager()
{

}

void InputManager::Initialize(OIS::Keyboard *k, OIS::Mouse *m)
{
	keyboard = k;
	mouse = m;
	keyboard->capture();
	mouse->capture();
	keyboard->copyKeyStates(keys);
	OIS::MouseState mouseState = mouse->getMouseState();
	mouseButtons = mouseState.buttons;
	mouseLocation = Ogre::Vector3((float)mouseState.X.abs, (float)mouseState.Y.abs, (float)mouseState.Z.abs);
	previousMouseLocation = mouseLocation;
}

void InputManager::Update(const Ogre::FrameEvent& fe)
{
	keyboard->capture();
	mouse->capture();

	OIS::MouseState mouseState = mouse->getMouseState();
	previousMouseLocation = mouseLocation;
	mouseLocation = Ogre::Vector3((float)mouseState.X.abs, (float)mouseState.Y.abs, (float)mouseState.Z.abs);

	if (previousMouseLocation != mouseLocation)
	{
			mouseMoved = true;
	}
	else
	{
		mouseMoved = false;
	}

	for (int i = 0; i < 8; i++)
	{
		if (mouseState.buttonDown((OIS::MouseButtonID)i))
		{
			if (GetMouseButtonState((OIS::MouseButtonID)i) == INPUT_STATE_UP)
			{
				// Press
				for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2)>::iterator it = 
					mouseCallbacks[INPUT_EVENT_PRESS][mouseMoved][(OIS::MouseButtonID)i].begin();
					it != mouseCallbacks[INPUT_EVENT_PRESS][mouseMoved][(OIS::MouseButtonID)i].end(); ++it)
				{
					int index = (int)(it - mouseCallbacks[INPUT_EVENT_PRESS][mouseMoved][(OIS::MouseButtonID)i].begin());
					(*it)(mouseCallbacks[INPUT_EVENT_PRESS][mouseMoved][(OIS::MouseButtonID)i][index], fe, (int)previousMouseLocation.x, (int)previousMouseLocation.y, (int)mouseLocation.x, (int)mouseLocation.y);
					if (interrupted)
					{
						interrupted = false;
						return;
					}
				}
			}
			// Hold
			for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2)>::iterator it = 
				mouseCallbacks[INPUT_EVENT_HOLD][mouseMoved][(OIS::MouseButtonID)i].begin();
				it != mouseCallbacks[INPUT_EVENT_HOLD][mouseMoved][(OIS::MouseButtonID)i].end(); ++it)
			{
				int index = (int)(it - mouseCallbacks[INPUT_EVENT_HOLD][mouseMoved][(OIS::MouseButtonID)i].begin());
				(*it)(mouseCallbacks[INPUT_EVENT_HOLD][mouseMoved][(OIS::MouseButtonID)i][index], fe, (int)previousMouseLocation.x, (int)previousMouseLocation.y, (int)mouseLocation.x, (int)mouseLocation.y);
				if (interrupted)
				{
					interrupted = false;
					return;
				}
			}
		}
		else if (!mouseState.buttonDown((OIS::MouseButtonID)i))
		{
			if (GetMouseButtonState((OIS::MouseButtonID)i) == INPUT_STATE_DOWN)
			{
				// Release
				for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2)>::iterator it = 
					mouseCallbacks[INPUT_EVENT_RELEASE][mouseMoved][(OIS::MouseButtonID)i].begin();
					it != mouseCallbacks[INPUT_EVENT_RELEASE][mouseMoved][(OIS::MouseButtonID)i].end(); ++it)
				{
					int index = (int)(it - mouseCallbacks[INPUT_EVENT_RELEASE][mouseMoved][(OIS::MouseButtonID)i].begin());
					(*it)(mouseCallbacks[INPUT_EVENT_RELEASE][mouseMoved][(OIS::MouseButtonID)i][index], fe, (int)previousMouseLocation.x, (int)previousMouseLocation.y, (int)mouseLocation.x, (int)mouseLocation.y);
					if (interrupted)
					{
						interrupted = false;
						return;
					}
				}
			}
			// Up
			for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2)>::iterator it = 
				mouseCallbacks[INPUT_EVENT_UP][mouseMoved][(OIS::MouseButtonID)i].begin();
				it != mouseCallbacks[INPUT_EVENT_UP][mouseMoved][(OIS::MouseButtonID)i].end(); ++it)
			{
				int index = (int)(it - mouseCallbacks[INPUT_EVENT_UP][mouseMoved][(OIS::MouseButtonID)i].begin());
				(*it)(mouseCallbacks[INPUT_EVENT_UP][mouseMoved][(OIS::MouseButtonID)i][index], fe, (int)previousMouseLocation.x, (int)previousMouseLocation.y, (int)mouseLocation.x, (int)mouseLocation.y);
				if (interrupted)
				{
					interrupted = false;
					return;
				}
			}
		}
	}
	mouseButtons = mouse->getMouseState().buttons;
	
	for (int i = 0; i < 256; i++)
	{
		if (keyboard->isKeyDown((OIS::KeyCode)i))
		{
			if (keys[i] == INPUT_STATE_UP)
			{
				// Press
				for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2)>::iterator it = 
					keyboardCallbacks[INPUT_EVENT_PRESS][mouseMoved][(OIS::KeyCode)i].begin();
					it != keyboardCallbacks[INPUT_EVENT_PRESS][mouseMoved][(OIS::KeyCode)i].end(); ++it)
				{
					int index = (int)(it - keyboardCallbacks[INPUT_EVENT_PRESS][mouseMoved][(OIS::KeyCode)i].begin());
					(*it)(keyboardContexts[INPUT_EVENT_PRESS][mouseMoved][(OIS::KeyCode)i][index], fe, (int)previousMouseLocation.x, (int)previousMouseLocation.y, (int)mouseLocation.x, (int)mouseLocation.y);
					if (interrupted)
					{
						interrupted = false;
						return;
					}
				}
			}
			// Hold
			for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2)>::iterator it = 
				keyboardCallbacks[INPUT_EVENT_HOLD][mouseMoved][(OIS::KeyCode)i].begin();
				it != keyboardCallbacks[INPUT_EVENT_HOLD][mouseMoved][(OIS::KeyCode)i].end(); ++it)
			{
				int index = (int)(it - keyboardCallbacks[INPUT_EVENT_HOLD][mouseMoved][(OIS::KeyCode)i].begin());
				(*it)(keyboardContexts[INPUT_EVENT_HOLD][mouseMoved][(OIS::KeyCode)i][index], fe, (int)previousMouseLocation.x, (int)previousMouseLocation.y, (int)mouseLocation.x, (int)mouseLocation.y);
				if (interrupted)
				{
					interrupted = false;
					return;
				}
			}
		}
		else if (!keyboard->isKeyDown((OIS::KeyCode)i))
		{
			if (keys[i] == INPUT_STATE_DOWN)
			{
				// Release
				for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2)>::iterator it = 
					keyboardCallbacks[INPUT_EVENT_RELEASE][mouseMoved][(OIS::KeyCode)i].begin();
					it != keyboardCallbacks[INPUT_EVENT_RELEASE][mouseMoved][(OIS::KeyCode)i].end(); ++it)
				{
					int index = (int)(it - keyboardCallbacks[INPUT_EVENT_RELEASE][mouseMoved][(OIS::KeyCode)i].begin());
					(*it)(keyboardContexts[INPUT_EVENT_RELEASE][mouseMoved][(OIS::KeyCode)i][index], fe, (int)previousMouseLocation.x, (int)previousMouseLocation.y, (int)mouseLocation.x, (int)mouseLocation.y);
					if (interrupted)
					{
						interrupted = false;
						return;
					}
				}
			}
			// Up
			for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2)>::iterator it = 
				keyboardCallbacks[INPUT_EVENT_UP][mouseMoved][(OIS::KeyCode)i].begin();
				it != keyboardCallbacks[INPUT_EVENT_UP][mouseMoved][(OIS::KeyCode)i].end(); ++it)
			{
				int index = (int)(it - keyboardCallbacks[INPUT_EVENT_UP][mouseMoved][(OIS::KeyCode)i].begin());
				(*it)(keyboardContexts[INPUT_EVENT_UP][mouseMoved][(OIS::KeyCode)i][index], fe, (int)previousMouseLocation.x, (int)previousMouseLocation.y, (int)mouseLocation.x, (int)mouseLocation.y);
				if (interrupted)
				{
					interrupted = false;
					return;
				}
			}
		}
	}
	keyboard->copyKeyStates(keys);

	for (std::vector<void(*)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2)>::iterator it = 
		noInputCallbacks[mouseMoved].begin(); it != noInputCallbacks[mouseMoved].end(); ++it)
	{
		int index = (int)(it - noInputCallbacks[mouseMoved].begin());
		(*it)(noInputContexts[mouseMoved][index], fe, (int)previousMouseLocation.x, (int)previousMouseLocation.y, (int)mouseLocation.x, (int)mouseLocation.y);
		if (interrupted)
		{
			interrupted = false;
			return;
		}
	}
	
	mouseLocation.x += mouseLocationCompensation.x;
	mouseLocation.y += mouseLocationCompensation.y;
	mouseLocationCompensation = Ogre::Vector2(0.0f, 0.0f);
}

void InputManager::RegisterCallback(void *context, void(*callback)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2), 
									INPUT_SOURCE triggerSource, INPUT_EVENT triggerEvent, bool onMouseMove, int keyOrButtonCode)
{
	if (triggerSource == INPUT_SOURCE_NONE)
	{
		noInputCallbacks[onMouseMove].push_back(callback);
		noInputContexts[onMouseMove].push_back(context);
	}
	else if (triggerSource == INPUT_SOURCE_KEYBOARD)
	{
		keyboardCallbacks[triggerEvent][onMouseMove][(OIS::KeyCode)keyOrButtonCode].push_back(callback);
		keyboardContexts[triggerEvent][onMouseMove][(OIS::KeyCode)keyOrButtonCode].push_back(context);
	}
	else if (triggerSource == INPUT_SOURCE_MOUSE)
	{
		mouseCallbacks[triggerEvent][onMouseMove][(OIS::MouseButtonID)keyOrButtonCode].push_back(callback);
		mouseContexts[triggerEvent][onMouseMove][(OIS::MouseButtonID)keyOrButtonCode].push_back(context);
	}
}

void InputManager::UnregisterCallback(void *context, void(*callback)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2), 
									  INPUT_SOURCE triggerSource, INPUT_EVENT triggerEvent, bool onMouseMove, int keyOrButtonCode)
{
	if (triggerSource == INPUT_SOURCE_NONE)
	{
		std::vector<void(*)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2)>::iterator callbackIt = 
			std::find(noInputCallbacks[onMouseMove].begin(), noInputCallbacks[onMouseMove].end(), callback);
		if (callbackIt != noInputCallbacks[onMouseMove].end())
		{
			int index = (int)(callbackIt - noInputCallbacks[onMouseMove].begin());
			std::vector<void *>::iterator contextIt = noInputContexts[onMouseMove].begin() + index;
			noInputCallbacks[onMouseMove].erase(callbackIt);
			noInputContexts[onMouseMove].erase(contextIt);
		}
	}
	else if (triggerSource == INPUT_SOURCE_KEYBOARD)
	{
		std::vector<void(*)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2)>::iterator callbackIt = 
			std::find(keyboardCallbacks[triggerEvent][onMouseMove][(OIS::KeyCode)keyOrButtonCode].begin(),
			keyboardCallbacks[triggerEvent][onMouseMove][(OIS::KeyCode)keyOrButtonCode].end(), callback);
		if (callbackIt != keyboardCallbacks[triggerEvent][onMouseMove][(OIS::KeyCode)keyOrButtonCode].end())
		{
			int index = (int)(callbackIt - keyboardCallbacks[triggerEvent][onMouseMove][(OIS::KeyCode)keyOrButtonCode].begin());
			std::vector<void *>::iterator contextIt = keyboardContexts[triggerEvent][onMouseMove][(OIS::KeyCode)keyOrButtonCode].begin() + index;
			keyboardCallbacks[triggerEvent][onMouseMove][(OIS::KeyCode)keyOrButtonCode].erase(callbackIt);
			keyboardContexts[triggerEvent][onMouseMove][(OIS::KeyCode)keyOrButtonCode].erase(contextIt);
		}
		
	}
	else if (triggerSource == INPUT_SOURCE_MOUSE)
	{
		std::vector<void(*)(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int x2, int y2)>::iterator callbackIt = 
			std::find(mouseCallbacks[triggerEvent][onMouseMove][(OIS::MouseButtonID)keyOrButtonCode].begin(),
			mouseCallbacks[triggerEvent][onMouseMove][(OIS::MouseButtonID)keyOrButtonCode].end(), callback);
		if (callbackIt != mouseCallbacks[triggerEvent][onMouseMove][(OIS::MouseButtonID)keyOrButtonCode].end())
		{
			int index = (int)(callbackIt - mouseCallbacks[triggerEvent][onMouseMove][(OIS::MouseButtonID)keyOrButtonCode].begin());
			std::vector<void *>::iterator contextIt = mouseContexts[triggerEvent][onMouseMove][(OIS::MouseButtonID)keyOrButtonCode].begin() + index;
			mouseCallbacks[triggerEvent][onMouseMove][(OIS::MouseButtonID)keyOrButtonCode].erase(callbackIt);
			mouseContexts[triggerEvent][onMouseMove][(OIS::MouseButtonID)keyOrButtonCode].erase(contextIt);
		}
	}
}

void InputManager::CompensateManualMouseSetPosition(int x, int y)
{
	mouseLocationCompensation.x += (float)x;
	mouseLocationCompensation.y += (float)y;
}

void InputManager::Interrupt()
{
	interrupted = true;
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