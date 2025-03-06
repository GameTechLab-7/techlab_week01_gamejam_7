#include "BufferCache.h"
#include "PrimitiveVertices.h"
#include "Manager/GameManager.h"

BufferCache::BufferCache()
{
}

BufferCache::~BufferCache()
{
}

ID3D11Buffer* BufferCache::GetBuffer(EObjectType Type)
{
	auto it = Cache.find(Type);
	if (it != Cache.end())
	{
		return it->second.Get();
	}
	else
	{
		//여기서 버텍스 버퍼 생성한다
		auto buffer = CreateVertexBuffer(Type);
		Cache.insert({ Type, buffer });

	}
	return nullptr;
}

ID3D11Buffer* BufferCache::CreateVertexBuffer(EObjectType Type)
{
	ID3D11Buffer* buffer = nullptr;
	int size = 0;
	switch (Type)
	{
	case EObjectType::Player:
	{
		//플레이어 버텍스 버퍼 생성 -> 플레이어는 구
		size = BufferSize[ Type ] = std::size(sphere_vertices);
		buffer = GameManager::GetInstance().GetRenderer()->CreateVertexBuffer(sphere_vertices , sizeof(FVertexSimple) * size);
		break;
	}
	case EObjectType::Enemy:
	{
		//적 버텍스 버퍼 생성
		size = BufferSize[ Type ] = std::size(cube_vertices);
		buffer = GameManager::GetInstance().GetRenderer()->CreateVertexBuffer(cube_vertices , sizeof(FVertexSimple) * size);
		break;
	}
	case EObjectType::Bullet:
	{
		//총알 버텍스 버퍼 생성
		size = BufferSize[ Type ] = std::size(triangle_vertices);
		buffer = GameManager::GetInstance().GetRenderer()->CreateVertexBuffer(triangle_vertices , sizeof(FVertexSimple) * size);
		break;
	}
	case EObjectType::UI:
	{
		
		size = BufferSize[ Type ] = std::size(square_vertices);
		buffer = GameManager::GetInstance().GetRenderer()->CreateVertexBuffer(square_vertices , sizeof(FVertexSimple) * size);
		break;
	}
	}
	return buffer;
}

