#define TERRAIN_PAGE_MIN_X 0
#define TERRAIN_PAGE_MIN_Y 0
#define TERRAIN_PAGE_MAX_X 0
#define TERRAIN_PAGE_MAX_Y 0

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreTerrain.h"
#include "OgreTerrainGroup.h"
#include "OgreTrays.h"
#include "TerrainsManager.h"
#include "OgreCameraMan.h"

using namespace Ogre;
using namespace OgreBites;

class FirstFlyStory : public ApplicationContext, public InputListener, public TerrainsLoadingListener {
	private:
		TerrainsManager* mTerrainMgr;
		TrayManager* mTrayMgr;
		Label* mInfoLbl;
		CameraMan* mCameraMan;

		SceneNode* flyBoddy;
		SceneNode* flyHead;
		SceneNode* flyRightWing;
		SceneNode* flyLeftWing;
		SceneNode* flyFrontRightFemur;
		SceneNode* flyMiddleRightFemur;
		SceneNode* flyBackRightFemur;
		SceneNode* flyFrontLeftFemur;
		SceneNode* flyMiddleLeftFemur;
		SceneNode* flyBackLeftFemur;
		SceneNode* flyFrontRightTibia;
		SceneNode* flyMiddleRightTibia;
		SceneNode* flyBackRightTibia;
		SceneNode* flyFrontLeftTibia;
		SceneNode* flyMiddleLeftTibia;
		SceneNode* flyBackLeftTibia;
		SceneNode* flyFrontRightShoe;
		SceneNode* flyMiddleRightShoe;
		SceneNode* flyBackRightShoe;
		SceneNode* flyFrontLeftShoe;
		SceneNode* flyMiddleLeftShoe;
		SceneNode* flyBackLeftShoe;


SceneNode* a;


	public:
		FirstFlyStory();
		~FirstFlyStory();
		virtual void terrainsLoadingFinished();
		virtual bool frameRenderingQueued(const FrameEvent& evt);
		virtual bool keyPressed(const KeyboardEvent& evt);
		virtual bool keyReleased(const KeyboardEvent& evt);
		virtual bool mouseMoved(const MouseMotionEvent& evt);
		virtual bool mousePressed(const MouseButtonEvent& evt);
		virtual bool mouseReleased(const MouseButtonEvent& evt);
		virtual void setup();
		void createThings(SceneManager* sceneMgr);
		void createFly(SceneManager* sceneMgr);
};

FirstFlyStory::FirstFlyStory() : ApplicationContext("First fly story") {
	mTerrainMgr = nullptr;
	mTrayMgr = nullptr;
	mInfoLbl = nullptr;
	mCameraMan = nullptr;
}

FirstFlyStory::~FirstFlyStory() {
	OGRE_DELETE mCameraMan;
	OGRE_DELETE mTerrainMgr;
}

void FirstFlyStory::terrainsLoadingFinished() {
	mInfoLbl->setCaption("Press spacebar to start the animation");
//	addInputListener(this);
}

bool FirstFlyStory::frameRenderingQueued(const FrameEvent& evt) {
	mTrayMgr->frameRendered(evt);
	mCameraMan->frameRendered(evt);
	return true;
}

bool FirstFlyStory::keyPressed(const KeyboardEvent& evt) {
	mCameraMan->keyPressed(evt);
	if(evt.keysym.sym == SDLK_SPACE) {
		mTrayMgr->destroyWidget(mInfoLbl);
//		removeInputListener(this);
	}
	else if(evt.keysym.sym == SDLK_ESCAPE)
		getRoot()->queueEndRendering();



else if(evt.keysym.sym == 'r') a->translate(Vector3(5,0,0));
else if(evt.keysym.sym == 'f') a->translate(Vector3(-5,0,0));
else if(evt.keysym.sym == 't') a->translate(Vector3(0,5,0));
else if(evt.keysym.sym == 'g') a->translate(Vector3(0,-5,0));
else if(evt.keysym.sym == 'y') a->translate(Vector3(0,0,5));
else if(evt.keysym.sym == 'h') a->translate(Vector3(0,0,-5));
else if(evt.keysym.sym == 'u') a->pitch(Degree(5));
else if(evt.keysym.sym == 'j') a->pitch(Degree(-5));
else if(evt.keysym.sym == 'i') a->yaw(Degree(5));
else if(evt.keysym.sym == 'k') a->yaw(Degree(-5));
else if(evt.keysym.sym == 'o') a->roll(Degree(5));
else if(evt.keysym.sym == 'l') a->roll(Degree(-5));


else if(evt.keysym.sym == 'b') {
	printf("Position    (%.2f,%.2f,%.2f)\n",a->getPosition().x,a->getPosition().y,a->getPosition().z);
	printf("Orientation (%.2f,%.2f,%.2f,%.2f)\n",a->getOrientation().w,a->getOrientation().x,a->getOrientation().y,a->getOrientation().z);
}


	return true;
}

bool FirstFlyStory::keyReleased(const KeyboardEvent& evt) {
	mCameraMan->keyReleased(evt);
	return true;
}

bool FirstFlyStory::mouseMoved(const MouseMotionEvent& evt) {
	mCameraMan->mouseMoved(evt);
	return true;
}

bool FirstFlyStory::mousePressed(const MouseButtonEvent& evt) {
	mCameraMan->mousePressed(evt);
	return true;
}

bool FirstFlyStory::mouseReleased(const MouseButtonEvent& evt) {
	mCameraMan->mouseReleased(evt);
	return true;
}

void FirstFlyStory::setup(void) {
	ApplicationContext::setup();
	Root* root = getRoot();
	SceneManager* sceneMgr = root->createSceneManager();
	RenderWindow* renderWdw = getRenderWindow();

	RTShader::ShaderGenerator* shaderGen = RTShader::ShaderGenerator::getSingletonPtr();
	shaderGen->addSceneManager(sceneMgr);

	sceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE);

	mTrayMgr = new TrayManager("Info",renderWdw);
	mTrayMgr->hideCursor();
	mInfoLbl = mTrayMgr->createLabel(TL_TOP,"Feedback","Loading terrain ...",380);
	mTrayMgr->showFrameStats(TL_BOTTOMLEFT);
	mTrayMgr->showLogo(TL_BOTTOMRIGHT);
	sceneMgr->addRenderQueueListener(getOverlaySystem());

	Vector3 terrainPos = Vector3(0,0,0);
	SceneNode* cameraNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
//	cameraNode->setPosition(Vector3(0,1000,1500));
	cameraNode->setPosition(Vector3(0,100,-100));
//	cameraNode->lookAt(Vector3(0,-0.5,-0.5),Node::TS_PARENT);
	cameraNode->lookAt(Vector3(0,100,0),Node::TS_PARENT);
	Camera* camera = sceneMgr->createCamera("Camera");
	camera->setAutoAspectRatio(true);
	camera->setNearClipDistance(0.1);
	camera->setFarClipDistance(50000);
	cameraNode->attachObject(camera);
	if(root->getRenderSystem()->getCapabilities()->hasCapability(RSC_INFINITE_FAR_PLANE))
		camera->setFarClipDistance(0);
	renderWdw->addViewport(camera);

	mCameraMan = new CameraMan(cameraNode);
	addInputListener(this);

//	ColourValue fadeColour(0.9,0.9,0.9);
//	renderWdw->getViewport(0)->setBackgroundColour(fadeColour);
//	sceneMgr->setFog(FOG_EXP,fadeColour,0.002);

	sceneMgr->setAmbientLight(ColourValue(0.2,0.2,0.2));
	Vector3 lightDir(1,-0.4,1);
	lightDir.normalise();
	Light* light = sceneMgr->createLight("DayLight");
	light->setType(Light::LT_DIRECTIONAL);
	light->setDirection(lightDir);
	light->setDiffuseColour(ColourValue(0.7,0.7,0.7));
	light->setSpecularColour(ColourValue(0.4,0.4,0.4));
	light->setShadowFarDistance(1000);

	mTerrainMgr = new TerrainsManager(root);
	mTerrainMgr->setTerrainsLoadingListener(this);
	mTerrainMgr->startLoading(terrainPos,light,sceneMgr);

	createThings(sceneMgr);
	createFly(sceneMgr);

	sceneMgr->setSkyDome(true,"Examples/CloudySky",10,8);
}

void FirstFlyStory::createThings(SceneManager* sceneMgr) {



	Entity* centro = sceneMgr->createEntity("ogrehead.mesh");
	SceneNode* centroNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	centroNode->attachObject(centro);
	centroNode->translate(Vector3(0,150,0));
	centroNode->setScale(Vector3(0.7,0.7,0.7));



	Entity* athene = sceneMgr->createEntity("Athene","athene.mesh");
	athene->setMaterialName("RomanBath/OgreStone");
	SceneNode* atheneNode = sceneMgr->getRootSceneNode()->createChildSceneNode("AtheneNode");
	atheneNode->attachObject(athene);
	atheneNode->translate(Vector3(80,160,495));
	atheneNode->setScale(Vector3(0.7,0.7,0.7));
	atheneNode->setOrientation(Quaternion(-0.16,0.14,0.97,0.06));

	Entity* ogreHead = sceneMgr->createEntity("OgreHead","ogrehead.mesh");
	ogreHead->setMaterialName("RomanBath/OgreStone");
	SceneNode* ogreHeadNode = sceneMgr->getRootSceneNode()->createChildSceneNode("OgreHeadNode");
	ogreHeadNode->attachObject(ogreHead);
	ogreHeadNode->translate(Vector3(-215,50,35));
	ogreHeadNode->setScale(Vector3(0.7,0.7,0.7));
	ogreHeadNode->setOrientation(Quaternion(0.78,-0.09,-0.59,-0.20));

	Entity* humanHead = sceneMgr->createEntity("HumanHead","facial.mesh");
	humanHead->setMaterialName("RomanBath/OgreStone");
	SceneNode* humanHeadNode = sceneMgr->getRootSceneNode()->createChildSceneNode("HumanHeadNode");
	humanHeadNode->attachObject(humanHead);
	humanHeadNode->translate(Vector3(-785,120,-335));
	humanHeadNode->setScale(Vector3(0.7,0.7,0.7));
	humanHeadNode->setOrientation(Quaternion(0.26,0.12,-0.96,-0.06));

	Entity* house = sceneMgr->createEntity("House","tudorhouse.mesh");
	SceneNode* houseNode = sceneMgr->getRootSceneNode()->createChildSceneNode("HouseNode");
	houseNode->attachObject(house);
	houseNode->translate(Vector3(505,110,400));
	houseNode->setScale(Vector3(0.2,0.2,0.2));
	houseNode->setOrientation(Quaternion(0.71,0.00,0.71,0.00));

	Entity* spaceship = sceneMgr->createEntity("Spaceship","RZR-002.mesh");
	SceneNode* spaceshipNode = sceneMgr->getRootSceneNode()->createChildSceneNode("SpaceshipNode");
	spaceshipNode->attachObject(spaceship);
	spaceshipNode->translate(Vector3(920,265,455));
	spaceshipNode->setOrientation(Quaternion(0.46,0.00,-0.89,0.00));
//	spaceshipNode->setVisible(false);

	Entity* woodPallet = sceneMgr->createEntity("WoodPallet","WoodPallet.mesh");
	SceneNode* woodPalletNode = sceneMgr->getRootSceneNode()->createChildSceneNode("WoodPalletNode");
	woodPalletNode->attachObject(woodPallet);
	woodPalletNode->translate(Vector3(500,80,-235));
	woodPalletNode->setOrientation(Quaternion(0.80,0.18,-0.57,-0.10));
}

void FirstFlyStory::createFly(SceneManager* sceneMgr) {
	Entity* boddyEntity = sceneMgr->createEntity("FlyBoddy","Boddy.mesh");
	flyBoddy = sceneMgr->getRootSceneNode()->createChildSceneNode("FlyBoddyNode");
	flyBoddy->attachObject(boddyEntity);
	flyBoddy->translate(Vector3(0,100,0) + Vector3(-26.5,9.45,35.1));

	flyBoddy->rotate(Vector3(1,0,0),Degree(-90));
	flyBoddy->rotate(Vector3(0,0,1),Degree(90));

Quaternion q = flyBoddy->getOrientation();
printf("*********************************************************************\n");
printf("Orientation: (%.2f,%.2f,%.2f,%.2f)\n",q.w,q.x,q.y,q.z);
printf("*********************************************************************\n");

	flyBoddy->scale(0.05,0.05,0.05);





	Entity* headEntity = sceneMgr->createEntity("FlyHead","Head.mesh");
	flyHead = flyBoddy->createChildSceneNode("FlyHeadNode");
	flyHead->attachObject(headEntity);
	flyHead->translate(Vector3(26.5,-0.485,5.104));

	Entity* rightWingEntity = sceneMgr->createEntity("FlyRightWing","RightWing.mesh");
	flyRightWing = flyBoddy->createChildSceneNode("FlyRightWingNode");
	flyRightWing->attachObject(rightWingEntity);
	flyRightWing->translate(Vector3(12.386,-7.705,10.149));

	Entity* leftWingEntity = sceneMgr->createEntity("FlyLeftWing","LeftWing.mesh");
	flyLeftWing = flyBoddy->createChildSceneNode("FlyLeftWingNode");
	flyLeftWing->attachObject(leftWingEntity);
	flyLeftWing->translate(Vector3(13.294,6.715,9.883));

	Entity* frontRightFemurEntity = sceneMgr->createEntity("FlyFrontRightFemur","FrontRightFemur.mesh");
	Entity* middleRightFemurEntity = sceneMgr->createEntity("FlyMiddleRightFemur","MiddleRightFemur.mesh");
	Entity* backRightFemurEntity = sceneMgr->createEntity("FlyBackRightFemur","BackRightFemur.mesh");
	Entity* frontLeftFemurEntity = sceneMgr->createEntity("FlyFrontLeftFemur","FrontLeftFemur.mesh");
	Entity* middleLeftFemurEntity = sceneMgr->createEntity("FlyMiddleLeftFemur","MiddleLeftFemur.mesh");
	Entity* backLeftFemurEntity = sceneMgr->createEntity("FlyBackLeftFemur","BackLeftFemur.mesh");

	flyFrontRightFemur = flyBoddy->createChildSceneNode("FlyFrontRightFemurNode");
	flyMiddleRightFemur = flyBoddy->createChildSceneNode("FlyMiddleRightFemurNode");
	flyBackRightFemur = flyBoddy->createChildSceneNode("FlyBackRightFemurNode");
	flyFrontLeftFemur = flyBoddy->createChildSceneNode("FlyFrontLeftFemurNode");
	flyMiddleLeftFemur = flyBoddy->createChildSceneNode("FlyMiddleLeftFemurNode");
	flyBackLeftFemur = flyBoddy->createChildSceneNode("FlyBackLeftFemurNode");

	flyFrontRightFemur->attachObject(frontRightFemurEntity);
	flyMiddleRightFemur->attachObject(middleRightFemurEntity);
	flyBackRightFemur->attachObject(backRightFemurEntity);
	flyFrontLeftFemur->attachObject(frontLeftFemurEntity);
	flyMiddleLeftFemur->attachObject(middleLeftFemurEntity);
	flyBackLeftFemur->attachObject(backLeftFemurEntity);

	flyFrontRightFemur->translate(Vector3(23.256,-9.45,-1.418));
	flyMiddleRightFemur->translate(Vector3(18.136,-9.45,-1.992));
	flyBackRightFemur->translate(Vector3(10.747,-14.717,-1.002));
	flyFrontLeftFemur->translate(Vector3(23.487,8.398,-1.268));
	flyMiddleLeftFemur->translate(Vector3(17.966,10.981,-1.533));
	flyBackLeftFemur->translate(Vector3(9.473,13.398,-1.55));

	Entity* frontRightTibiaEntity = sceneMgr->createEntity("FlyFrontRightTibia","FrontRightTibia.mesh");
	Entity* middleRightTibiaEntity = sceneMgr->createEntity("FlyMiddleRightTibia","MiddleRightTibia.mesh");
	Entity* backRightTibiaEntity = sceneMgr->createEntity("FlyBackRightTibia","BackRightTibia.mesh");
	Entity* frontLeftTibiaEntity = sceneMgr->createEntity("FlyFrontLeftTibia","FrontLeftTibia.mesh");
	Entity* middleLeftTibiaEntity = sceneMgr->createEntity("FlyMiddleLeftTibia","MiddleLeftTibia.mesh");
	Entity* backLeftTibiaEntity = sceneMgr->createEntity("FlyBackLeftTibia","BackLeftTibia.mesh");

	flyFrontRightTibia = flyFrontRightFemur->createChildSceneNode("FlyFrontRightTibiaNode");
	flyMiddleRightTibia = flyMiddleRightFemur->createChildSceneNode("FlyMiddleRightTibiaNode");
	flyBackRightTibia = flyBackRightFemur->createChildSceneNode("FlyBackRightTibiaNode");
	flyFrontLeftTibia = flyFrontLeftFemur->createChildSceneNode("FlyFrontLeftTibiaNode");
	flyMiddleLeftTibia = flyMiddleLeftFemur->createChildSceneNode("FlyMiddleLeftTibiaNode");
	flyBackLeftTibia = flyBackLeftFemur->createChildSceneNode("FlyBackLeftTibiaNode");

	flyFrontRightTibia->attachObject(frontRightTibiaEntity);
	flyMiddleRightTibia->attachObject(middleRightTibiaEntity);
	flyBackRightTibia->attachObject(backRightTibiaEntity);
	flyFrontLeftTibia->attachObject(frontLeftTibiaEntity);
	flyMiddleLeftTibia->attachObject(middleLeftTibiaEntity);
	flyBackLeftTibia->attachObject(backLeftTibiaEntity);

	flyFrontRightTibia->translate(Vector3(12.667,-9.278,-10.902));
	flyMiddleRightTibia->translate(Vector3(0.255,-19.042,-9.63));
	flyBackRightTibia->translate(Vector3(-14.989,-6.094,-11.545));
	flyFrontLeftTibia->translate(Vector3(13.01,8.717,-10.354));
	flyMiddleLeftTibia->translate(Vector3(0.425,15.692,-10.089));
	flyBackLeftTibia->translate(Vector3(-13.142,5.841,-10.338));

	Entity* frontRightShoeEntity = sceneMgr->createEntity("FlyFrontRightShoe","FrontRightShoe.mesh");
	Entity* middleRightShoeEntity = sceneMgr->createEntity("FlyMiddleRightShoe","MiddleRightShoe.mesh");
	Entity* backRightShoeEntity = sceneMgr->createEntity("FlyBackRightShoe","BackRightShoe.mesh");
	Entity* frontLeftShoeEntity = sceneMgr->createEntity("FlyFrontLeftShoe","FrontLeftShoe.mesh");
	Entity* middleLeftShoeEntity = sceneMgr->createEntity("FlyMiddleLeftShoe","MiddleLeftShoe.mesh");
	Entity* backLeftShoeEntity = sceneMgr->createEntity("FlyBackLeftShoe","BackLeftShoe.mesh");

	flyFrontRightShoe = flyFrontRightTibia->createChildSceneNode("FlyFrontRightShoeNode");
	flyMiddleRightShoe = flyMiddleRightTibia->createChildSceneNode("FlyMiddleRightShoeNode");
	flyBackRightShoe = flyBackRightTibia->createChildSceneNode("FlyBackRightShoeNode");
	flyFrontLeftShoe = flyFrontLeftTibia->createChildSceneNode("FlyFrontLeftShoeNode");
	flyMiddleLeftShoe = flyMiddleLeftTibia->createChildSceneNode("FlyMiddleLeftShoeNode");
	flyBackLeftShoe = flyBackLeftTibia->createChildSceneNode("FlyBackLeftShoeNode");

	flyFrontRightShoe->attachObject(frontRightShoeEntity);
	flyMiddleRightShoe->attachObject(middleRightShoeEntity);
	flyBackRightShoe->attachObject(backRightShoeEntity);
	flyFrontLeftShoe->attachObject(frontLeftShoeEntity);
	flyMiddleLeftShoe->attachObject(middleLeftShoeEntity);
	flyBackLeftShoe->attachObject(backLeftShoeEntity);

	flyFrontRightShoe->translate(Vector3(0.304,-0.443,-12.912));
	flyMiddleRightShoe->translate(Vector3(0,-0.446,-13.01));
	flyBackRightShoe->translate(Vector3(-1.541,-0.058,-12.616));
	flyFrontLeftShoe->translate(Vector3(0.579,-0.613,-13.214));
	flyMiddleLeftShoe->translate(Vector3(0,-0.503,-13.541));
	flyBackLeftShoe->translate(Vector3(-0.358,-0.75,-13.009));

	flyFrontRightFemur->rotate(Vector3(1,0,0),Degree(15));
	flyFrontRightFemur->rotate(Vector3(0,1,0),Degree(10));
	flyMiddleRightFemur->rotate(Vector3(1,0,0),Degree(15));
	flyMiddleRightFemur->rotate(Vector3(0,1,0),Degree(10));
	flyBackRightFemur->rotate(Vector3(1,0,0),Degree(15));
	flyBackRightFemur->rotate(Vector3(0,1,0),Degree(10));
	flyFrontLeftFemur->rotate(Vector3(1,0,0),Degree(-15));
	flyFrontLeftFemur->rotate(Vector3(0,1,0),Degree(10));
	flyMiddleLeftFemur->rotate(Vector3(1,0,0),Degree(-15));
	flyMiddleLeftFemur->rotate(Vector3(0,1,0),Degree(10));
	flyBackLeftFemur->rotate(Vector3(1,0,0),Degree(-15));
	flyBackLeftFemur->rotate(Vector3(0,1,0),Degree(10));



a = flyBoddy;

}

int main(int argc, char *argv[]) {
	FirstFlyStory app;
	app.initApp();
	app.getRoot()->startRendering();
	app.closeApp();
	return 0;
}