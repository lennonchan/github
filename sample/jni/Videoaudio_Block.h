//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Recommand Block.h
//  @ Date : 2012-11-6
//  @ Author : 
//
//


#if !defined(_VIDEOAUDIO_BLOCK_H)
#define _VIDEOAUDIO_BLOCK_H

#include "Block.h"

class VideoaudioBlock :public Block
{
public:
	VideoaudioBlock(gkScene*);
	~VideoaudioBlock();
	virtual BlockEnum getBlockEnum();
	virtual int getMenuFlag();
	virtual int getVacantPosParentID();
protected:
	virtual void initEditMenu();
};

#endif  //_VIDEOAUDIO_BLOCK_H