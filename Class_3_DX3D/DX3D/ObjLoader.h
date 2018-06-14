#pragma once
class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();

	bool	LoadMtl_ReadKx(const char* line, float* kx);
	bool	IsCharNumber(char c);
	int		CountNumbers(const char* s);
	bool	InspectVertexDefinition(const char* sVertexDef, bool& hasNormals, bool& hasTexCoords);
	void	InspectFaceLine(const char* sLine, int& vCount, bool inspectVertexComponents, bool& hasTexCoords, bool& hasNormals);
	INT		PathFromFileName(LPCTSTR sFileName);

	INT LoadMtlLib(LPCTSTR sFileName, std::vector<TObjMaterial*>& materials);
	INT LoadObj(LPCTSTR sFileName, TObjMesh* pOutObjMesh);

};

