
#ifndef _TASKITEM_H_
#define _TASKITEM_H_
#include <cocos2d.h>
USING_NS_CC;

class TaskItem : public cocos2d::Layer
{
public:
	bool init();
	void initTaskItem(int);
	CREATE_FUNC(TaskItem);
private:
	Node * m_rootNode;
	int m_id;
	bool m_state;
	bool m_clicked;
	ValueMap m_strings;
	void taskChange(Ref*);
	void stateChange();
};

#endif