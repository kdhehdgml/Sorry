#pragma once

extern CString ASSET_PATH;

#define CUBE_RADIUS 5.0f

#define CUBE_INDEX_SIZE 36
extern WORD g_aCubeIndex[];
#define CUBE_VERTEX_SIZE 8
#define NODE_POSITSIZEZ 190
#define NODE_POSITSIZEX 140
extern D3DXVECTOR3 g_aCubeVertex[];
extern D3DXVECTOR3 g_Cube_TesT[];

#define SINGLETON(class_name) private:\
	class_name();\
	~class_name();\
public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}

//xfile
#define SAFE_DELETE_ARRAY(p) if(p) {delete [] (p); (p) = NULL;}
#define SAFE_ADDREF(p) if(p) { (p)->AddRef(); }
//

#define SAFE_WNDPROC(p) if(p) {(p)->WndProc(hWnd, message, wParam, lParam);}
#define SAFE_UPDATE(p) if(p) { (p)->Update();}
#define SAFE_RENDER(p) if(p) { (p)->Render();}
#define SAFE_RELEASE(p) if(p) { (p)->Release(); (p) = NULL;}
#define SAFE_DELETE(p) if(p) { delete (p); (p) = NULL;}

#define MIN(x,y) ( (x)<(y)? (x) : (y) )
#define MAX(x,y) ( (x)>(y)? (x) : (y) )

#define SCREEN_POINT(lParam) LOWORD(lParam), HIWORD(lParam)

#define METHOD_WNDPROC(method) void method(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)

enum SCENE_INDEX {
	SCENE_MAIN,
	SCENE_LOADING,
	SCENE_HEIGHTMAP,
	SCENE_GRID,
	SCENE_OBJMAP,
	SCENE_TEST,
	SCENE_XFILE,
	SCENE_HEIGHTMAPTEST
};

enum TAG_DISPLAYOBJECT {
	TAG_PLAYER,
	TAG_MOB,
	TAG_TEAM
};

struct KEYBOARD_STATE
{
	D3DXVECTOR3 deltaPos;
	D3DXVECTOR3 deltaRot;
	bool		bJump;
};

//	1. Position 정점의 좌표 x,y,z(float)				: D3DFVF_XYZ
// 	2. RHW (float)                                  : D3DFVF_XYZRHW (D3DFVF_XYZ 또는 D3DFVF_NORMAL과 같이 사용불가)
// 	3. Blending Weight Data 결합 가중치 (float)		: D3DFVF_XYZB1 ~ D3DFVF_XYZB5
// 	4. Vertex Normal 정점의 법선 벡터 x,y,z(float)	: D3DFVF_NORMAL
// 	5. Vertex Point Size 정점의 점 크기 (float)		: D3DFVF_PSIZE
// 	6. Diffuse Color (DWORD)						: D3DFVF_DIFFUSE
// 	7. Specular Color (DWORD)						: D3DFVF_SPECULAR
// 	8. Texture Coordinate Set 1 (float)             : D3DFVF_TEX0 - D3DFVF_TEX8

struct VERTEX_PC
{
	D3DXVECTOR3 p;
	D3DCOLOR c;

	VERTEX_PC() {}
	VERTEX_PC(D3DXVECTOR3 _p, D3DCOLOR _c) :p(_p), c(_c) {}

	enum {FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};
};

struct VERTEX_PT
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;

	VERTEX_PT() {}
	VERTEX_PT(D3DXVECTOR3 _p, D3DXVECTOR2 _t) :p(_p), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

struct VERTEX_PN
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;

	VERTEX_PN() {}
	VERTEX_PN(D3DXVECTOR3 _p, D3DXVECTOR3 _n) :p(_p), n(_n) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
};

struct VERTEX_PNT
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;

	VERTEX_PNT() {}
	VERTEX_PNT(D3DXVECTOR3 _p, D3DXVECTOR3 _n, D3DXVECTOR2 _t)
		:p(_p), n(_n), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1};
};

struct VERTEX_RHWC
{
	D3DXVECTOR4 p;
	D3DCOLOR	c;

	VERTEX_RHWC() {}
	VERTEX_RHWC(D3DXVECTOR4 _p, D3DCOLOR _c)
		:p(_p), c(_c) {}

	enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
};

struct MTLTEX : public BaseObject
{
	D3DMATERIAL9		material;
	LPDIRECT3DTEXTURE9	pTexture;
	int					id;

	MTLTEX() {
		ZeroMemory(&material, sizeof(D3DMATERIAL9));
		pTexture = NULL;}
	
	void SetMaterial(const D3DMATERIAL9 &_material) 
	{material = _material;}
	D3DMATERIAL9 GetMaterial() { return material; }
	void SetTexture(LPDIRECT3DTEXTURE9 _pTexture)
	{pTexture = _pTexture;}
	LPDIRECT3DTEXTURE9 GetTexture() { return pTexture; }
};

struct ASE_POS_SAMPLE
{
	int			tick;
	D3DXVECTOR3 position;
};

struct ASE_ROT_SAMPLE
{
	int				tick;
	D3DXQUATERNION	quaternion;
};

struct ASE_SCENE
{
	int numFirstFrame;
	int numLastFrame;
	int frameSpeed;
	int ticksPerFrame;
};

struct BoundingSphere
{
	D3DXVECTOR3 center;
	float		radius;
	bool		isPicked;

	BoundingSphere() :isPicked(false) {}
	BoundingSphere(D3DXVECTOR3 _center, float _radius) :center(_center),
		radius(_radius), isPicked(false) {}
};

struct BoundingBox
{
	D3DXVECTOR3 aa;
	D3DXVECTOR3 bb;
	bool isPicked;
	BoundingBox() :isPicked(false) {}
	BoundingBox(D3DXVECTOR3 _aa, D3DXVECTOR3 _bb) :aa(_aa),
		bb(_bb), isPicked(false) {}
};

DWORD FtoDw(float f);

float  GetRandomFloat(float lowBound, float highBound);

# define LINE_BUFF_SIZE 4096

struct TObjMaterial
{
	char name[MAX_PATH];
	float Ka[3];
	float Kd[3];
	float Ks[3];
	float Tf[3];
	float Tr;
	float Ns;
	float Ni;
	int illum;
	char map_Ka[MAX_PATH];
	char map_Kd[MAX_PATH];
	char map_Ks[MAX_PATH];
	char map_Ns[MAX_PATH];
	char map_Tr[MAX_PATH];
	char map_Disp[MAX_PATH];
	char map_Bump[MAX_PATH];
	char map_Refl[MAX_PATH];


	TObjMaterial()
	{
		strncpy_s(name, "default", MAX_PATH);
		Ka[0] = 0.2f; Ka[1] = 0.2f; Ka[2] = 0.2f;
		Kd[0] = 0.8f; Kd[1] = 0.8f; Kd[2] = 0.8f;
		Ks[0] = 0.f; Ks[1] = 0.f; Ks[2] = 0.f;
		Tf[0] = 1.0f; Tf[1] = 1.0f; Tf[2] = 1.0f;
		Tr = 1.f;
		Ns = 32.f;
		Ni = 1.f;
		illum = 2;
		map_Ka[0] = 0;
		map_Kd[0] = 0;
		map_Ks[0] = 0;
		map_Ns[0] = 0;
		map_Tr[0] = 0;
		map_Disp[0] = 0;
		map_Bump[0] = 0;
		map_Refl[0] = 0;
	}
};

struct TObjMesh
{
# ifdef __D3DX9_H__
	typedef D3DXVECTOR3 TFloat3;
	typedef D3DXVECTOR2 TFloat2;
# else
	struct TFloat3 { float x, y, z; };
	struct TFloat2 { float x, y; };
# endif

	struct TFace
	{
		INT firstVertex;
		INT firstTexCoord;
		INT firstNormal;
		INT vCount;
	};

	struct TGroup
	{
		UINT firstFace;
		UINT numFaces;
		char name[MAX_PATH];
	};


	std::vector< TFloat3 >		vertices;
	std::vector< TFloat3 >		normals;
	std::vector< TFloat2 >		texCoords;
	std::vector< TFace >		faces;

	std::vector< INT >			faceVertices;
	std::vector< INT >			faceNormals;
	std::vector< INT >			faceTexCoords;

	std::vector< TGroup >		groups;
	std::vector< TGroup >		matGroups;

	std::vector< TObjMaterial* > materials;

	UINT					numTriangles;
	TFloat3					bbmin;
	TFloat3					bbmax;

	char sMtlFileName[MAX_PATH];


	TObjMesh() { numTriangles = 0; }

	void Free()
	{
		vertices.clear();
		normals.clear();
		texCoords.clear();
		faces.clear();
		matGroups.clear();
		faceVertices.clear();
		faceNormals.clear();
		numTriangles = 0;
		for (UINT i = 0; i<materials.size(); i++)
			delete materials[i];
		materials.clear();
	}

};

struct ObjTriVertex
{
	INT iPos;
	INT iNormal;
	INT iTex;

	void Init() { iPos = iNormal = iTex = -1; }
};

struct ObjTriangle
{
	ObjTriVertex vertex[3];

	void Init() { vertex[0].Init(); vertex[1].Init(); vertex[2].Init(); }
};