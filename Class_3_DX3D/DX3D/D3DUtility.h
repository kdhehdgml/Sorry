#pragma once

#define WHITE	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define BLACK	D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f)
#define RED		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
#define GREEN	D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)
#define BLUE	D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)
#define YELLOW	D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f)

namespace DXUtil
{
	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);
	
	const D3DMATERIAL9 WHITE_MTRL = InitMtrl(WHITE, WHITE, WHITE, BLACK, 8.0f);
	const D3DMATERIAL9 RED_MTRL = InitMtrl(RED, RED, RED, BLACK, 8.0f);
	const D3DMATERIAL9 GREEN_MTRL = InitMtrl(GREEN, GREEN, GREEN, BLACK, 8.0f);
	const D3DMATERIAL9 BLUE_MTRL = InitMtrl(BLUE, BLUE, BLUE, BLACK, 8.0f);
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 8.0f);
	const D3DMATERIAL9 BLACK_MTRL = InitMtrl(BLACK, BLACK, BLACK, BLACK, 8.0f);

	void ComputeNormal(D3DXVECTOR3* out, D3DXVECTOR3* p0, D3DXVECTOR3* p1, D3DXVECTOR3* p2);

	D3DLIGHT9 InitDirectional(D3DXVECTOR3* dir, D3DXCOLOR* c);
	D3DLIGHT9 InitPoint(D3DXVECTOR3* pos, D3DXCOLOR* c);
	D3DLIGHT9 InitSpot(D3DXVECTOR3* dir, D3DXVECTOR3* pos, D3DXCOLOR* c);
}