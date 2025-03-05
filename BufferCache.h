#pragma once
#include <unordered_map>
#include <wrl/client.h>
#include "enum.h"

using Microsoft::WRL::ComPtr;


class BufferCache
{
private:
	std::unordered_map<EObjectType , ComPtr<struct ID3D11Buffer>> Cache;
	std::unordered_map<EObjectType , int> BufferSize;
public:
	BufferCache();
	~BufferCache();

	ID3D11Buffer* GetBuffer(EObjectType Type);
	int GetBufferSize(EObjectType Type) { return BufferSize[ Type ]; }

private :
	ID3D11Buffer* CreateVertexBuffer(EObjectType Type);
};

