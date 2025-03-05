#pragma once
#include <unordered_map>
#include <d3d11.h>
#include <wrl/client.h>
#include "enum.h"


class BufferCache
{
private:
	std::unordered_map<EObjectType , Microsoft::WRL::ComPtr<ID3D11Buffer>> Cache;
	std::unordered_map<EObjectType , int> BufferSize;
public:
	BufferCache();
	~BufferCache();

	ID3D11Buffer* GetBuffer(EObjectType Type);
	int GetBufferSize(EObjectType Type) { return BufferSize[ Type ]; }

private :
	ID3D11Buffer* CreateVertexBuffer(EObjectType Type);
};

