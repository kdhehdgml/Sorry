#pragma once
#include "BaseObject.h"

class IDisplayObject : public BaseObject
{
public:
	enum RenderMode
	{
		RenderMode_Default,
		RenderMode_Lighting,
		RenderMode_ShadowMapping
	};

protected:
	CString					m_name;
	WORD					m_tag;
	D3DXVECTOR3				m_scale;

	VARIATION_P(D3DXMATRIXA16, m_localMatrix, LocalMatrix);
	VARIATION_P(D3DXMATRIXA16, m_worldMatrix, WorldMatrix);
	VARIATION_P(D3DXMATRIXA16, m_combinedMatrix, CombinedMatrix);

	D3DXVECTOR3				m_pos;
	D3DXVECTOR3				m_rot;
	IDisplayObject*			m_pParent;

	D3DXMATRIXA16			m_matWorld;

	//D3DXMATRIXA16			m_localMatrix;
	//D3DXMATRIXA16			m_worldMatrix;
	//D3DXMATRIXA16			m_combinedMatrix;
	D3DXMATRIXA16*			m_pFrameMatrix;

	vector<IDisplayObject*> m_vecPChild;

	RenderMode				m_renderMode;


public:
	IDisplayObject();
	virtual ~IDisplayObject();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void AddChild(IDisplayObject* pChild);
	virtual void ReleaseAll();
	virtual void RenderUseShader_0() {};
	virtual void RenderUseShader_1() {};

	//D3DXVECTOR3		GetPosition() { return m_pos; }
	//void			SetPosition(D3DXVECTOR3* pos) { m_pos = *pos; }
	//D3DXVECTOR3		GetRotation() { return m_rot; }
	//D3DXMATRIXA16	GetWorldMatrix() { return m_matWorld; }

	const CString&	GetName() { return  m_name; }
	void			SetName(LPCTSTR name) { m_name = name; }
	IDisplayObject* FindChildByName(LPCTSTR name);
	const D3DXVECTOR3&	GetPosition() { return m_pos; }
	void				SetPosition(D3DXVECTOR3* pos) { m_pos = *pos; }
	const D3DXVECTOR3&	GetRotation() { return m_rot; }
	void				SetScale(D3DXVECTOR3* pos) { m_scale = *pos; }
	/*void SetLocalMatrix(LPD3DXMATRIXA16 pMat) { m_localMatrix = *pMat; }
	void SetFrameMatrix(LPD3DXMATRIXA16 pMat) { m_pFrameMatrix = pMat; }*/
	//D3DXMATRIXA16&	GetWorldMatrix() { return m_matWorld; }
	//void					SetWorldMatrix(D3DXMATRIXA16* pMat) { m_matWorld = *pMat; }
	//D3DXMATRIXA16* GetCombinedMatrix() { return &m_combinedMatrix; }
};

typedef IDisplayObject* LPDisplayObject;
