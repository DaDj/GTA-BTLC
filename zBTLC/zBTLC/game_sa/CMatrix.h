#pragma once
#include "plbase/PluginBase_SA.h"
#include "RenderWare.h"
#include "CQuaternion.h"

#pragma pack(push, 4)
class CMatrix
{
public:
    // RwV3d-like:
    CVector      m_right;
    unsigned int flags;
    CVector      m_forward;
    unsigned int pad1;
    CVector      m_up;
    unsigned int pad2;
    CVector      m_pos;
    unsigned int pad3;
    
	RwMatrix *m_pAttachMatrix;
	unsigned char m_bAttachMatrixTemporary; // do we need to delete attaching matrix at detaching

	CMatrix();
	CMatrix(CMatrix const& matrix);
	CMatrix(RwMatrix *matrix, bool temporary); // like previous + attach
	~CMatrix(); // destructor detaches matrix if attached 
	void Attach(RwMatrix *matrix, bool temporary);
	void Detach();
	void CopyOnlyMatrix(CMatrix const& matrix); // copy base RwMatrix to another matrix
	void Update(); // update RwMatrix with attaching matrix. This doesn't check if attaching matrix is present, so use it only if you know it is present.
	               // Using UpdateRW() is more safe since it perform this check.
	void UpdateRW(); // update RwMatrix with attaching matrix.
	void UpdateRW(RwMatrix *matrix); // update RwMatrix with this matrix
	void SetUnity();
	void ResetOrientation();
	void SetScale(float scale);
	void SetScale(float x, float y, float z); // scale on three axes
	void SetTranslateOnly(float x, float y, float z);
	void SetTranslate(float x, float y, float z); // like previous + reset orientation
	void SetRotateXOnly(float angle);
	void SetRotateYOnly(float angle);
	void SetRotateZOnly(float angle);
	void SetRotateX(float angle);
	void SetRotateY(float angle);
	void SetRotateZ(float angle);
	void SetRotate(float x, float y, float z); // set rotate on 3 axes
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void Rotate(float x, float y, float z); // rotate on 3 axes
	void Reorthogonalise();
	void CopyToRwMatrix(RwMatrix *matrix); // similar to UpdateRW(RwMatrixTag *)
	void SetRotate(CQuaternion  const& quat);
	void operator=(CMatrix const& right);
	void operator+=(CMatrix const& right);
	void operator*=(CMatrix const& right);

	CVector& GetRight() { return m_right; }
	const CVector& GetRight() const { return m_right; }

	CVector& GetForward() { return m_forward; }
	const CVector& GetForward() const { return m_forward; }

	CVector& GetUp() { return m_up; }
	const CVector& GetUp() const { return m_up; }

	CVector& GetPosition() { return m_pos; }
	const CVector& GetPosition() const { return m_pos; }
};
#pragma pack(pop)

VALIDATE_SIZE(CMatrix, 0x48);