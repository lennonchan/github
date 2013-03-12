 #ifndef __EDITBLOCKMOVELOGIC__
 #define __EDITBLOCKMOVELOGIC__
 
#include "EditBaseLogic.h"
 
 class EditBlockMoveLogic : public EditBaseLogic
 {
 public:
	 enum{
		 CURRENT_EDIT_STATE = 10,
	 };
	DECLARE_SOCKET_TYPE(CURRENT_EDIT_STATE, EditStateSet);
 	EditBlockMoveLogic(gkLogicTree* parent, size_t id);
 	bool evaluate(gkScalar tick);
 private:
 	void editBlockMove();
	void deleteBlock();
	void addBlock();
 };
 
 #endif