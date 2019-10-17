#ifndef __TerrainsManager_H__
#define __TerrainsManager_H__

#include "OgreRoot.h"
#include "OgreFrameListener.h"
#include "OgreTerrainGroup.h"

class TerrainsLoadingListener {
	public:
		virtual void terrainsLoadingFinished() {}
};

class TerrainsManager : public Ogre::FrameListener {
	private:
		Ogre::Root* mRoot;
		Ogre::TerrainGroup* mTerrainGroup;
		Ogre::TerrainGlobalOptions* mTerrainGlobalOptions;
		TerrainsLoadingListener* mCallBack;
		bool mTerrainsImported;

		void initializeTerrainVariables(Ogre::Vector3 terrainPos,Ogre::SceneManager* sceneMgr);
		void configureTerrainDefaults(Ogre::Light* light,Ogre::SceneManager* sceneMgr);
		void loadAllSubTerrains();
		void defineSubTerrain(long x,long y);
		void getTerrainImage(bool flipX,bool flipY,Ogre::Image& img);
		void initializeAllBlendMaps();
		void initializeBlendMapsForTerrain(Ogre::Terrain* terrain);

	public:
		TerrainsManager(Ogre::Root* root);
		~TerrainsManager();
		void setTerrainsLoadingListener(TerrainsLoadingListener* listener);
		void startLoading(Ogre::Vector3 terrainPos,Ogre::Light* light,Ogre::SceneManager* sceneMgr);
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
};

#endif