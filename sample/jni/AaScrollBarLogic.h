#ifndef __AaSCROLLBARLOGIC__
#define  __AaSCROLLBARLOGIC__

#include "BaseLogic.h"
#include "Logic/gkMouseNode.h"

class AaScrollBarLogic: public BaseLogic
{
public:
	enum{
		ENABLE = 10,
	};

	DECLARE_SOCKET_TYPE(ENABLE, StateSet);

	AaScrollBarLogic(gkLogicTree* parent, UTsize handle);
	
	bool evaluate(gkScalar tick);
	//void update(gkScalar tick);

private:
	void scrollBarDrag(Ogre::RaySceneQueryResult&);
	void scrollBarTrack(Ogre::RaySceneQueryResult&);

};


#endif