#include "NodeQueryPackageAck.h"



CNodeQueryPackageAck::CNodeQueryPackageAck()
{
}


CNodeQueryPackageAck::~CNodeQueryPackageAck()
{
	if (data != NULL)
	{
		delete[] data;
	}
		
}
