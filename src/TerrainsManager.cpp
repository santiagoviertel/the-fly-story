#include "TerrainsManager.h"

#define TERRAIN_PAGE_MIN_X 0
#define TERRAIN_PAGE_MIN_Y 0
#define TERRAIN_PAGE_MAX_X 0
#define TERRAIN_PAGE_MAX_Y 0

#define TERRAIN_FILE_PREFIX String("terrain")
#define TERRAIN_FILE_SUFFIX String("dat")
//#define TERRAIN_WORLD_SIZE 12000.0f
#define TERRAIN_WORLD_SIZE 3000.0f
#define TERRAIN_SIZE 513

using namespace Ogre;

TerrainsManager::TerrainsManager(Root* root) {
	mRoot = root;
	mTerrainGroup = nullptr;
	mTerrainGlobalOptions = nullptr;
	mCallBack = nullptr;
}

TerrainsManager::~TerrainsManager() {
	if(mTerrainGlobalOptions) {
		OGRE_DELETE mTerrainGlobalOptions;
		mTerrainGlobalOptions = nullptr;
	}
}

void TerrainsManager::setTerrainsLoadingListener(TerrainsLoadingListener* listener) {
	mCallBack = listener;
}

void TerrainsManager::startLoading(Vector3 terrainPos,Light* light,SceneManager* sceneMgr) {
	mTerrainsImported = false;
	initializeTerrainVariables(terrainPos,sceneMgr);
	configureTerrainDefaults(light,sceneMgr);
	loadAllSubTerrains();
	initializeAllBlendMaps();
	mRoot->addFrameListener(this);
}

void TerrainsManager::initializeTerrainVariables(Vector3 terrainPos,SceneManager* sceneMgr) {
	mTerrainGlobalOptions = new TerrainGlobalOptions();
	mTerrainGroup = new TerrainGroup(sceneMgr,Terrain::ALIGN_X_Z,TERRAIN_SIZE,TERRAIN_WORLD_SIZE);
	mTerrainGroup->setFilenameConvention(TERRAIN_FILE_PREFIX,TERRAIN_FILE_SUFFIX);
	mTerrainGroup->setOrigin(terrainPos);
}

void TerrainsManager::configureTerrainDefaults(Light* light,SceneManager* sceneMgr) {
//	mTerrainGlobalOptions->setMaxPixelError(8);
	mTerrainGlobalOptions->setMaxPixelError(2);
	mTerrainGlobalOptions->setCompositeMapDistance(3000);
	mTerrainGlobalOptions->setLightMapDirection(light->getDerivedDirection());
	mTerrainGlobalOptions->setCompositeMapAmbient(sceneMgr->getAmbientLight());
	mTerrainGlobalOptions->setCompositeMapDiffuse(light->getDiffuseColour());
	Terrain::ImportData& defaultImp = mTerrainGroup->getDefaultImportSettings();
	defaultImp.terrainSize = TERRAIN_SIZE;
	defaultImp.worldSize = TERRAIN_WORLD_SIZE;
//	defaultImp.inputScale = 600;
	defaultImp.inputScale = 150;
	defaultImp.minBatchSize = 33;
	defaultImp.maxBatchSize = 65;
	defaultImp.layerList.resize(3);
	defaultImp.layerList[0].worldSize = 100;
	defaultImp.layerList[0].textureNames.push_back("grass_green-01_diffusespecular.dds");
	defaultImp.layerList[0].textureNames.push_back("grass_green-01_normalheight.dds");
	defaultImp.layerList[1].worldSize = 100;
	defaultImp.layerList[1].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
	defaultImp.layerList[1].textureNames.push_back("dirt_grayrocky_normalheight.dds");
	defaultImp.layerList[2].worldSize = 200;
	defaultImp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
	defaultImp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
}

void TerrainsManager::loadAllSubTerrains() {
	for(long x=TERRAIN_PAGE_MIN_X;x<=TERRAIN_PAGE_MAX_X;x++)
		for(long y=TERRAIN_PAGE_MIN_Y;y<=TERRAIN_PAGE_MAX_Y;y++)
			defineSubTerrain(x,y);
	mTerrainGroup->loadAllTerrains(true);
}

void TerrainsManager::defineSubTerrain(long x,long y) {
	String filename = mTerrainGroup->generateFilename(x,y);
	if(ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(),filename))
		mTerrainGroup->defineTerrain(x,y);
	else {
		Image img;
		getTerrainImage(x%2!=0,y%2!=0,img);
		mTerrainGroup->defineTerrain(x,y,&img);
		mTerrainsImported = true;
	}
}

void TerrainsManager::getTerrainImage(bool flipX,bool flipY,Image& img) {
	img.load("terrain.png",mTerrainGroup->getResourceGroup());
	if(flipX)
		img.flipAroundY();
	if(flipY)
		img.flipAroundX();
}

void TerrainsManager::initializeAllBlendMaps() {
	if(mTerrainsImported) {
		TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
		while(ti.hasMoreElements()) {
			Terrain* t = ti.getNext()->instance;
			initializeBlendMapsForTerrain(t);
		}
	}
	mTerrainGroup->freeTemporaryResources();
}

void TerrainsManager::initializeBlendMapsForTerrain(Terrain* terrain) {
	TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
	TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
	float minHeight0 = 20;
	float fadeDist0 = 15;
	float minHeight1 = 70;
	float fadeDist1 = 15;
	float* pBlend0 = blendMap0->getBlendPointer();
	float* pBlend1 = blendMap1->getBlendPointer();
	for(uint16 y=0;y<terrain->getLayerBlendMapSize();y++) {
		for(uint16 x=0;x<terrain->getLayerBlendMapSize();x++) {
			Real tx,ty;
			blendMap0->convertImageToTerrainSpace(x,y,&tx,&ty);
			float height = terrain->getHeightAtTerrainPosition(tx,ty);
			*pBlend0++ = Math::saturate((height - minHeight0)/fadeDist0);
			*pBlend1++ = Math::saturate((height - minHeight1)/fadeDist1);
		}
	}
	blendMap0->dirty();
	blendMap1->dirty();
	blendMap0->update();
	blendMap1->update();
}

bool TerrainsManager::frameRenderingQueued(const FrameEvent& evt) {
	if(!mTerrainGroup->isDerivedDataUpdateInProgress()) {
		mRoot->removeFrameListener(this);
		if(mTerrainsImported) {
			mTerrainGroup->saveAllTerrains(true);
			mTerrainsImported = false;
		}
		if(mCallBack)
			mCallBack->terrainsLoadingFinished();
	}
	return true;
}