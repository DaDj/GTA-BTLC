#pragma once

#include "plbase/PluginBase_SA.h"
#include "CColSphere.h"
#include "CColBox.h"
#include "CColLine.h"
#include "CompressedVector.h"
#include "CColTriangle.h"
#include "CColTrianglePlane.h"

#pragma pack(push, 4)
class CColData
{
public:
    unsigned short   m_wNumSpheres;
    unsigned short   m_wNumBoxes;
    unsigned short   m_wNumTriangles;
    unsigned char    m_bNumLines;
    unsigned char    m_bFlags;
    CColSphere        *m_pSpheres;
    CColBox           *m_pBoxes;
	/* possibly was the union with some unknown yet collision model which was used for CMtruck only.
	    union{
		    CColLine          *m_pLines;
			CMtruckColLine    *m_pMtruckLines;
		};
	*/
    CColLine          *m_pLines;
    CompressedVector  *m_pVertices;
    CColTriangle      *m_pTriangles;
    CColTrianglePlane *m_pTrianglePlanes;
    unsigned int   m_dwNumShadowTriangles;
    unsigned int   m_dwNumShadowVertices;
    CompressedVector  *m_pShadowVertices;
    CColTriangle      *m_pShadowTriangles;
};
#pragma pack(pop)

VALIDATE_SIZE(CColData, 0x30);