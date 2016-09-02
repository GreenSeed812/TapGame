#ifndef _ShopData_H_
#define _ShopData_H_
#include<cocos2d.h>
class ShopData
{
public:
	static ShopData* getInstance();
	int getShopGold(){ return m_shopGold; }
	void subShopGold(int gold){ m_shopGold -= gold; }
	void addShopGold(int gold){ m_shopGold += gold;  }
	bool getHaichaoS(){ return m_haichaoS; }
	bool getjianchi(){ return m_jianchi; }
	bool getshuaxin(){ return m_shuaxin; }
private:
	ShopData();
	~ShopData();
	bool m_haichaoS;
	int m_shopGold;
	int m_haiChao;
	int m_shandian;
	int m_huoshe;
	int m_dijingyinhang;
	bool m_jianchi;
	bool m_shuaxin;
	int m_zhuansheng;
	bool m_miaosha;
	bool m_cangbaohaiwan;
	bool m_xingyun;
	bool m_kuangluan;
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
