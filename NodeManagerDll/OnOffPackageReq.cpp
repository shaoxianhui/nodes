#include "OnOffPackageReq.h"



COnOffPackageReq::COnOffPackageReq()
{
}


COnOffPackageReq::~COnOffPackageReq()
{
	if (data != NULL)
		delete[] data;
}
