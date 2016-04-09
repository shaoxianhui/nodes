#include "DisplayPackageReq.h"



CDisplayPackageReq::CDisplayPackageReq()
{
}


CDisplayPackageReq::~CDisplayPackageReq()
{
	if (data != NULL)
		delete[] data;
}
