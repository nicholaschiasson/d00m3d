#ifndef OGRE_APPLICATION_H
#define OGRE_APPLICATION_H

#include <string>

#include "ogre_app_exception.h"
#include "mesh_factory.h"
#include "input_manager.h"

#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include "OGRE/OgreManualObject.h"
#include "OGRE/OgreEntity.h"
#include "OIS/OIS.h"

namespace ogre_application
{
	/* A useful type to define */
	typedef std::vector<Ogre::String> Strings;

	/* Our Ogre application */
	class OgreApplication :
	    public Ogre::FrameListener, // Derive from FrameListener to be able to have render event callbacks
        public Ogre::WindowEventListener // Derive from WindowEventListener to be able to have window event callbacks
	{
	public:
		OgreApplication();
		~OgreApplication();
		void Initialize(); // Call Initialize() before running the main loop
		void MainLoop(); // Keep application active
		
		static OgreApplication *application_singleton_;

	private:
		// Create root that allows us to access Ogre commands
		std::auto_ptr<Ogre::Root> ogre_root_;
		// Main Ogre window
		Ogre::RenderWindow* ogre_window_;

		// Input managers
		OIS::InputManager *ogre_input_manager_;
		InputManager *inputManager;
		OIS::Mouse *mouse_;
		OIS::Keyboard *keyboard_;

		/* Methods to initialize the application */
		void InitRootNode();
		void InitPlugins();
		void InitRenderSystem();
		void InitWindow();
		void InitViewport();
		void InitEvents();
		void InitOIS();
		void LoadMaterials();
		void RegisterInputCallbacks();

		/* Methods to handle events */
		bool frameRenderingQueued(const Ogre::FrameEvent& fe);
		void windowResized(Ogre::RenderWindow* rw);

		/* Input Callbacks */
		static void ExitOgreApplication(const Ogre::FrameEvent& fe);
		static void CameraMoveForward(const Ogre::FrameEvent& fe);
		static void CameraMoveLeft(const Ogre::FrameEvent& fe);
		static void CameraMoveBackward(const Ogre::FrameEvent& fe);
		static void CameraMoveRight(const Ogre::FrameEvent& fe);
		static void CameraMoveUp(const Ogre::FrameEvent& fe);
		static void CameraMoveDown(const Ogre::FrameEvent& fe);
		static void CameraPitchUp(const Ogre::FrameEvent& fe);
		static void CameraYawLeft(const Ogre::FrameEvent& fe);
		static void CameraPitchDown(const Ogre::FrameEvent& fe);
		static void CameraYawRight(const Ogre::FrameEvent& fe);

    }; // class OgreApplication
} // namespace ogre_application

#endif // OGRE_APPLICATION_H