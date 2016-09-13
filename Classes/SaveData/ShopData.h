#ifndef _ShopData_H_
#define _ShopData_H_
#include<cocos2d.h>
using namespace cocos2d;
struct ItemData
{
	bool isUsing;
	int itemNum;
	int ID;
	float leftTime;
};
class ShopData
{
public:
	static ShopData* getInstance();
	void useItemByID(int);
	void buyItemByID(int);
	int getShopGold(){ return m_shopGold; }
	void stopItemById(int i);
	void subShopGold(int gold);
	void addShopGold(int gold);
	bool getItemBeUsedById(int id);
	int getCount(int id);
private:
	void init();
	ShopData();
	~ShopData();
	int m_shopGold;
	ItemData* m_items[13];
};


#endif


//����ͼ��
//����ͼ��
//����ͼ��
//��ŭͼ��
//�ؾ�����Ѻ���¹�
//�������
//����ˢ��
//����Ӷ��
//��������
//ת�����
//�����콵
//�ر�����ı���
//����Ӳ��
//���ҹ���
