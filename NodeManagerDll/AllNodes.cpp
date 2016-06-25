#include "AllNodes.h"

CAllNodes::CAllNodes()
{
	memset(quickTable, 0x00, 1024);
	/*for (int i = 0; i < 100; i++)
	{
		CNodeInfoWithSocket info;
		info.info.UID[0] = i;
		string uid = CUtil::UIDtoString((char*)info.info.UID);
		allNodes[uid] = info;
	}*/
}

CAllNodes::~CAllNodes()
{
}
