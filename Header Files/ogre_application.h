#ifndef OGRE_APPLICATION_H
#define OGRE_APPLICATION_H

#include <string>

#include "ogre_app_exception.h"
#include "mesh_factory.h"
#include "input_manager.h"
#include "world.h"
#include "camera.h"

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

	private:
		// Create root that allows us to access Ogre commands
		std::auto_ptr<Ogre::Root> ogre_root_;
		// Main Ogre window
		Ogre::RenderWindow* ogre_window_;

		// Input managers
		OIS::InputManager *ogre_input_manager_;
		InputManager inputManager;
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
		void LoadResources();
		void RegisterInputCallbacks();

		/* Methods to handle events */
		bool frameRenderingQueued(const Ogre::FrameEvent& fe);
		void windowResized(Ogre::RenderWindow* rw);
		World world;
		Camera camera;

		/* Input Callbacks */
		static void ExitOgreApplication(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);
		static void CameraZoom(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);

    }; // class OgreApplication
} // namespace ogre_application

#endif // OGRE_APPLICATION_H