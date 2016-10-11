#include"Animation.h"
#include "cocostudio/CocoStudio.h"
MyAnimation * MyAnimation::m_animation = nullptr;
using namespace cocostudio;
MyAnimation::MyAnimation()
	:m_kssj(false)
	,m_klgj(false)
	, m_fntt(false)
{
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/gongjianzuo.plist");
	//m_harmaer = Animation::create();
	//for (size_t i = 0; i < 18; i++)
	//{
	//	m_harmaer->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("gongjianzuo%d.png", i).c_str()));
	//}
	//m_harmaer->setDelayPerUnit(0.0816f);
	//m_harmaer->retain();

	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/aoshu.plist");
	//m_aoshu = Animation::create();
	//for (size_t i = 0; i < 25; i++)
	//{
	//	m_aoshu->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("xiaofagong_%d.png", i).c_str()));
	//}
	//m_aoshu->setDelayPerUnit(0.1216f);
	//m_aoshu->retain();
}

MyAnimation* MyAnimation::getInstance()
{
	if (m_animation == nullptr)
	{
		m_animation = new MyAnimation();
		m_animation->initXiangyunani();
		m_animation->initZhisiani();
		m_animation->initShizijun();
		m_animation->initKuaisusheji();
		m_animation->initBaofengxueani();
		m_animation->initshixie();
		m_animation->initshixiekuang();
		m_animation->inittouqie();
		m_animation->initkuangluan();
		m_animation->initbaodian();
		m_animation->initfengnu();
		ArmatureDataManager::getInstance()->addArmatureFileInfo("old/Effect_appear_dust0.png", "old/Effect_appear_dust0.plist", "old/Effect_appear_dust.ExportJson");//读取动画相关文件
		ArmatureDataManager::getInstance()->addArmatureFileInfo("old/Effect_atk_hunter0.png", "old/Effect_atk_hunter0.plist", "old/Effect_atk_hunter.ExportJson");//读取动画相关文件
		ArmatureDataManager::getInstance()->addArmatureFileInfo("old/Effect_atk_magister0.png", "old/Effect_atk_magister0.plist", "old/Effect_atk_magister.ExportJson");//读取动画相关文件
		ArmatureDataManager::getInstance()->addArmatureFileInfo("old/Effect_atk_warrior0.png", "old/Effect_atk_warrior0.plist", "old/Effect_atk_warrior.ExportJson");//读取动画相关文件
		ArmatureDataManager::getInstance()->addArmatureFileInfo("old/Effect_nextmap0.png", "old/Effect_nextmap0.plist", "old/Effect_nextmap.ExportJson");//读取动画相关文件
		ArmatureDataManager::getInstance()->addArmatureFileInfo("old/Effect_PK_hit10.png", "old/Effect_PK_hit10.plist", "old/Effect_PK_hit1.ExportJson");//读取动画相关文件
		ArmatureDataManager::getInstance()->addArmatureFileInfo("old/Effect_strike_hunter0.png", "old/Effect_strike_hunter0.plist", "old/Effect_strike_hunter.ExportJson");//读取动画相关文件
		ArmatureDataManager::getInstance()->addArmatureFileInfo("old/Effect_strike_magister0.png", "old/Effect_strike_magister0.plist", "old/Effect_strike_magister.ExportJson");//读取动画相关文件
		ArmatureDataManager::getInstance()->addArmatureFileInfo("old/Effect_strike_warrior0.png", "old/Effect_strike_warrior0.plist", "old/Effect_strike_warrior.ExportJson");//读取动画相关文件
		ArmatureDataManager::getInstance()->addArmatureFileInfo("old/goldcoin_drop0.png", "old/goldcoin_drop0.plist", "old/goldcoin_drop.ExportJson");//读取动画相关文件
		m_animation->initsxAction();
	}
	return m_animation;
}

//void MyAnimation::runHarmer(bool isRun,Node * node)
//{
//	auto animate = Animate::create(m_harmaer);
//	auto sprite = Sprite::create();
//	sprite->setScale(0.6);
//	sprite->setName("Harmer");
//	if (isRun)
//	{
//		sprite->runAction(RepeatForever::create(animate));
//	}
//	sprite->setPosition(Vec2(node->getContentSize().width - 700,node->getContentSize().height -500));
//	node->addChild(sprite);
//}
//
//void MyAnimation::runAoshu(bool isRun, Node * node)
//{
//	auto animate = Animate::create(m_aoshu);
//	auto sprite = Sprite::create();
//	sprite->setScale(2);
//	sprite->setName("aoshu");
//	if (isRun)
//	{
//		sprite->runAction(RepeatForever::create(animate));
//	}
//	sprite->setPosition(Vec2(node->getContentSize().width / 2, node->getContentSize().height - 500));
//	node->addChild(sprite);
//}

void MyAnimation::setPos()
{

}
void MyAnimation::initXiangyunani()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/xiangyun.plist");
	m_xiangyunani = Animation::create();
	for (int i = 0; i < 20; i++)
	{
		m_xiangyunani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("guochang%02d.png", i)));
	}
	m_xiangyunani->setDelayPerUnit(0.0416f);

	m_xiangyunani->retain();
}
void MyAnimation::initZhisiani()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/zhisi.plist");
	m_zhisiani = Animation::create();
	for (int i = 0; i < 25; i++)
	{
		auto str = StringUtils::format("zhisi%02d.png", i);
		m_zhisiani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("zhisi%02d.png", i)));
	}
	m_zhisiani->setDelayPerUnit(0.0832f);

	m_zhisiani->retain();
}
void MyAnimation::initShizijun()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/shizijun.plist");
	m_shizijunani = Animation::create();
	for (int i = 0; i < 20; i++)
	{
		auto str = StringUtils::format("shizijun%02d.png", i);
		m_shizijunani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("shizijun%02d.png", i)));
	}
	m_shizijunani->setDelayPerUnit(0.0416f);

	m_shizijunani->retain();
}
void MyAnimation::initKuaisusheji()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/KS.plist");
	m_kuaisusheji = Animation::create();
	for (int i = 1; i < 18; i++)
	{
		auto str = StringUtils::format("KSSJ%02d.png", i);
		m_kuaisusheji->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("KS%02d.png", i)));
	}
	m_kuaisusheji->setDelayPerUnit(0.0416f);
	m_kuaisusheji->retain();

}
void MyAnimation::initBaofengxueani()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/baofengxue.plist");
	m_baofengxueani = Animation::create();
	for (int i = 1; i < 17; i++)
	{
		auto str = StringUtils::format("BFX%02d.png", i);
		m_baofengxueani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("BFX%02d.png", i)));
	}
	m_baofengxueani->setDelayPerUnit(0.0416f);

	m_baofengxueani->retain();
}
void MyAnimation::initshixie()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/shixie.plist");
	m_shixieani = Animation::create();
	for (int i = 0; i < 22; i++)
	{
		auto str = StringUtils::format("shixie%02d.png", i);
		m_shixieani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("shixie%02d.png", i)));
	}
	m_shixieani->setDelayPerUnit(0.0416f);
	m_shixieani->retain();
}
void MyAnimation::initshixiekuang()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/shixiekuang.plist");
	m_shixiekuangani = Animation::create();
	for (int i = 0; i < 60; i++)
	{
		auto str = StringUtils::format("shixiekuang%02d.png", i);
		m_shixiekuangani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("shixiekuang%02d.png", i)));
	}
	m_shixiekuangani->setDelayPerUnit(0.0416f);
	m_shixiekuangani->retain();
}
void MyAnimation::inittouqie()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/touqie.plist");
	m_touqieani = Animation::create();
	for (int i = 0; i < 49; i++)
	{
		auto str = StringUtils::format("touqie%02d.png", i);
		m_touqieani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("touqie%02d.png", i)));
	}
	m_touqieani->setDelayPerUnit(0.0416f);
	m_touqieani->retain();
}

void MyAnimation::initkuangluan()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/kuangluan.plist");
	m_kuangluanani = Animation::create();
	for (int i = 1; i < 10; i++)
	{
		auto str = StringUtils::format("kuangluan%d.png", i);
		m_kuangluanani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
	}
	m_kuangluanani->setDelayPerUnit(0.0416f);
	m_kuangluanani->retain();
}
void MyAnimation::initbaodian()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/baodian.plist");
	m_baodian = Animation::create();
	for (int i = 0; i < 6; i++)
	{
		auto str = StringUtils::format("baodian%d.png", i);
		m_baodian->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("baodian%d.png", i)));
	}
	m_baodian->setDelayPerUnit(0.0416f);
	m_baodian->retain();
}
void MyAnimation::initfengnu()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/fengnu.plist");
	m_fengnuani = Animation::create();
	for (int i = 1; i < 10; i++)
	{
		auto str = StringUtils::format("f%d.png", i);
		m_fengnuani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
	}
	m_fengnuani->setDelayPerUnit(0.0416f);
	m_fengnuani->retain();
}
void MyAnimation::initsxAction()
{
	auto fadein = FadeIn::create(1.0f);
	auto fadeout = FadeOut::create(1.0f);
	m_sxAct = Sequence::create(fadein, fadeout, NULL);
	m_sxAct->retain();
	
}
Animate* MyAnimation::getAnimate_fn()
{
	return Animate::create(m_fengnuani);
}
Animate* MyAnimation::getAnimate_xy()
{
	return Animate::create(m_xiangyunani);
}

Animate* MyAnimation::getAnimate_zs()
{
	return Animate::create(m_zhisiani);
}

Animate* MyAnimation::getAnimate_szj()
{
	return Animate::create(m_shizijunani);
}

Animate* MyAnimation::getAnimate_kssj()
{
	return Animate::create(m_kuaisusheji);
}
Animate* MyAnimation::getAnimate_bfx()
{
	return Animate::create(m_baofengxueani);
}
Animate* MyAnimation::getAnimate_sx()
{
	return Animate::create(m_shixieani);
}
Sequence* MyAnimation::getAction_sx()
{
	return m_sxAct;
}
Animate* MyAnimation::getAnimate_sxk()
{
	return Animate::create(m_shixiekuangani);
}
Animate* MyAnimation::getAnimate_tq()
{
	return Animate::create(m_touqieani);
}
Animate* MyAnimation::getAnimate_kl()
{
	return Animate::create(m_kuangluanani);
}
Animate* MyAnimation::getAnimate_bd()
{
	return Animate::create(m_baodian);
}