#include "AppDelegate.h"
#include "MainScene/HelloWorldScene.h"
#include "Tool\SqLite.h"
#include "LoadingScene\LoadingScene.h"
#include "Animation.h"
USING_NS_CC;
bool AppDelegate::g_phoneType = true;

AppDelegate::AppDelegate() {
	checkType();
}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("HelloCpp", Rect(0, 0, 540, 960),0.7f);
        director->setOpenGLView(glview);
    }
	
	director->getOpenGLView()->setDesignResolutionSize(1080, 1920, ResolutionPolicy::SHOW_ALL);
	auto data = FileUtils::getInstance()->getDataFromFile("config/test.db");
	FileUtils::getInstance()->writeDataToFile(data, FileUtils::getInstance()->getWritablePath() + "config.db");
    // turn on display FPS
    director->setDisplayStats(false);
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    FileUtils::getInstance()->addSearchPath("res");
	
    auto scene = LoadingScene::createScene();
	director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::checkType()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	AppDelegate::g_phoneType = false;
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	AppDelegate::g_phoneType = true;
#endif
#if  CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	AppDelegate::g_phoneType = false;
#endif
}