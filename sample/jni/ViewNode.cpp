//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : ViewNode
//  @ Date : 2012-11-6
//  @ Author : 
//
//
#include "ViewNode.h"
#include "Util.h"
#include "BlenderAnimation.h"

ViewNode::ViewNode(gkScene* pScene,const gkHashedString& str):
		m_pScene(NULL),m_pObj(NULL),m_pIndex(NULL),m_MinIndex(100),m_MaxIndex(-100),m_pNodeAnm(NULL)
{
	_ASSERT_(pScene);
	m_pScene = pScene;
	if(str != "")
		m_pObj = m_pScene->getObject(str);
		//m_pIndex = new int[2];
}

ViewNode::~ViewNode()
{
	if(m_pObj&&m_pObj->isClone())
		ui_delete(m_pObj);
}

int 
ViewNode::getMinIndex()
{
	return m_MinIndex;
}

int 
ViewNode::getMaxIndex()
{
	return m_MaxIndex;
}

int*
ViewNode::getIndex()
{
	return NULL;//m_pIndex;
}

ViewNode* 
ViewNode::setIndex(int i0,int i1)
{
	m_MinIndex = i0;
	m_MaxIndex = i1;
//	m_pIndex[0] = m_MinIndex;
//	m_pIndex[1] = m_MaxIndex;
	return this;
}

ViewNode* 
ViewNode::setMinIndex(int i)
{
	m_MinIndex = i;
//	m_pIndex[0] = m_MinIndex;
	return this;
}

ViewNode* 
ViewNode::setMaxIndex(int i)
{
	m_MaxIndex = i;
//	m_pIndex[1] = m_MaxIndex;
	return this;
}
gkGameObject* 
ViewNode::getGameObj()
{
	return m_pObj;
}

void 
ViewNode::setGameObj(gkGameObject* pObj)
{
	_ASSERT_(!m_pObj);
	m_pObj = pObj;
}

const gkVector3 
ViewNode::getPosition()
{
	_ASSERT_(m_pObj);
	gkVector3 temp = m_pObj ? m_pObj->getParent()->getPosition()+ m_pObj->getPosition() : gkVector3();
	return temp;
}

void 
ViewNode::gameObjectTranslation(gkVector3 v)
{
	_ASSERT_(m_pObj);
	const gkVector3 temp = m_pObj->getPosition()+v;
	m_pObj->setPosition(temp);
}

const gkVector3& 
ViewNode::getScale()
{
	_ASSERT_(m_pObj);
	return m_pObj->getScale();
}

void 
ViewNode::setViewNodeBldAnm(BlenderAnimation* pAnm,int showStart /* = 0 */,int showEnd /* = 0 */,int hideStart /* = 0 */,int hideEnd /* = 0 */,BlenderAnmInterface* pInterface /* = NULL */)
{
	ui_delete(m_pNodeAnm);
	m_pNodeAnm = new sViewNodeAnm(pAnm,showStart,showEnd,hideStart,hideEnd,pInterface);
}

void 
ViewNode::showViewNodeBldAnm()
{
	_ASSERT_(m_pNodeAnm);
	m_pNodeAnm->showViewNodeAnm();
}

void 
ViewNode::hideViewNodeBldAnm()
{
	_ASSERT_(m_pNodeAnm);
	m_pNodeAnm->hideViewNodeAnm();
}



ViewNode::sViewNodeAnm::sViewNodeAnm(BlenderAnimation* pAnm,int showStart /* = 0 */,int showEnd /* = 0 */,int hideStart /* = 0 */,int hideEnd /* = 0 */,BlenderAnmInterface* pInterface /* = NULL */)
{
	_ASSERT_(pAnm);
	mpAnm = pAnm;
	mpAnm->setAnmInterface(pInterface);
	mArrayShowFrame[0] = showStart;
	mArrayShowFrame[1] = showEnd;
	mArrayHideFrame[0] = hideStart;
	mArrayHideFrame[1] = hideEnd;
}

void 
ViewNode::sViewNodeAnm::setShowScope(int starts,int ends)
{
	mArrayShowFrame[0] = starts;
	mArrayShowFrame[1] = ends;
}

void 
ViewNode::sViewNodeAnm::setHideScope(int starts,int ends)
{
	mArrayHideFrame[0] = starts;
	mArrayHideFrame[1] = ends;
}

void 
ViewNode::sViewNodeAnm::setInterface(BlenderAnmInterface* pInterface)
{
	mpAnm->setAnmInterface(pInterface);
}

void 
ViewNode::sViewNodeAnm::showViewNodeAnm()
{
	_ASSERT_(mpAnm);
	mpAnm->setFrameScope(mArrayShowFrame[0],mArrayShowFrame[1]);
	mpAnm->play();
}

void 
ViewNode::sViewNodeAnm::hideViewNodeAnm()
{
	_ASSERT_(mpAnm);
	mpAnm->setFrameScope(mArrayHideFrame[0],mArrayHideFrame[1]);
	mpAnm->play();
}