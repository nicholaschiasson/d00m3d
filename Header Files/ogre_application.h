#ifndef OGRE_APPLICATION_H
#define OGRE_APPLICATION_H

#include <string>

#include "ogre_app_exception.h"
#include "mesh_factory.h"

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
		void Init(); // Call Init() before running the main loop
		void MainLoop(); // Keep application active

	private:
		// Create root that allows us to access Ogre commands
		std::auto_ptr<Ogre::Root> ogre_root_;
		// Main Ogre window
		Ogre::RenderWindow* ogre_window_;

		// Input managers
		OIS::InputManager *input_manager_;
		OIS::Mouse *mouse_;
		OIS::Keyboard *keyboard_;

		char keyStates[256];

		/* Methods to initialize the application */
		void InitRootNode();
		void InitPlugins();
		void InitRenderSystem();
		void InitWindow();
		void InitViewport();
		void InitEvents();
		void InitOIS();
		void LoadMaterials();

		/* Methods to handle events */
		bool frameRenderingQueued(const Ogre::FrameEvent& fe);
		void windowResized(Ogre::RenderWindow* rw);

    }; // class OgreApplication
} // namespace ogre_application

#endif // OGRE_APPLICATION_H