#include "pch.h"
#include <Resource/PrimitiveMesh.hpp>
#include <Wrapper/RHI.hpp>

namespace Resource
{
	PrimitiveMesh::PrimitiveMesh(const int p_id, const std::string& p_name)
	{
		usedBy = 0;
		name = p_name;
		id = p_id;
		path = p_name;
		isFinishToInit = false;
	}

	const bool PrimitiveMesh::Init()
	{
		switch (type)
		{
		case Resource::COLLIDER_TYPE::BOX:
			InitBox();
			break;
		case Resource::COLLIDER_TYPE::PLANE:
			InitPlane();
			break;
		case Resource::COLLIDER_TYPE::SPHERE:
			InitSphere();
			break;
		default:
			break;
		}
		return true;
	}
	const bool PrimitiveMesh::InitRHI()
	{
		if (isFinishToInit)
		{
			return true;
		}

		Wrapper::RHI::InitCollider(VBO, VAO, EBO, vertexBuffer, indexBuffer, name);

		isFinishToInit = true;

		return true;
	}

	void PrimitiveMesh::Unload()
	{
		Wrapper::RHI::DestroyMesh(VBO, VAO, EBO);
	}

	void PrimitiveMesh::Draw(const unsigned int p_shaderProgram) const
	{
		if (!isFinishToInit)
		{
			return;
		}
		Wrapper::RHI::DrawCollider(VAO, static_cast<unsigned int>(indexBuffer.size()));
	}

	void PrimitiveMesh::InitPlane()
	{
		float bound = 10.f;
		float increment = 1.f;
		for (float i = -bound + 1.f; i < bound; i += increment)
		{
			vertexBuffer.push_back(4.f * Math::Vector3(0.0f, -bound, i));
		}

		for (float i = -bound + 1.f; i < bound; i += increment)
		{
			vertexBuffer.push_back(4.f * Math::Vector3(0.0f, bound, i));
		}

		for (float i = -bound + 1.f; i < bound; i += increment)
		{
			vertexBuffer.push_back(4.f * Math::Vector3(0.0f, i, -bound));
		}

		for (float i = -bound + 1.f; i < bound; i += increment)
		{
			vertexBuffer.push_back(4.f * Math::Vector3(0.0f, i, bound));
		}

		unsigned int offset = (static_cast<unsigned int>(bound) * 8U - 4U) / 2U;
		unsigned int doubleOffset = offset * 2U;

		for (unsigned int i = 0U; i < offset; ++i)
		{
			indexBuffer.push_back(i);
			indexBuffer.push_back(i + offset);
			indexBuffer.push_back(i);
			indexBuffer.push_back(doubleOffset - 1U - i);
		}

		vertexBuffer.push_back(4.f * Math::Vector3(0.0f, -bound, -bound));
		vertexBuffer.push_back(4.f * Math::Vector3(0.0f, -bound, bound));
		vertexBuffer.push_back(4.f * Math::Vector3(0.0f, bound, -bound));
		vertexBuffer.push_back(4.f * Math::Vector3(0.0f, bound, bound));

		for (unsigned int j = 0U; j < 3U; ++j)
		{
			for (unsigned int i = 0U; i < 4U - j; ++i)
			{
				indexBuffer.push_back(doubleOffset + j);
				indexBuffer.push_back(doubleOffset + j + i);
			}
		}
	}

	void PrimitiveMesh::InitBox()
	{
		for (float i = -1.0f; i < 1.1f; i += 2.f)
		{
			for (float j = -1.0f; j < 1.1f; j += 2.f)
			{
				for (float k = -1.0f; k < 1.1f; k += 2.f)
				{
					vertexBuffer.push_back(Math::Vector3(i, j, k));
				}
			}
		}
		unsigned int ind = 0U;
		for (int i = 0; i < 4; ++i)
		{
			indexBuffer.push_back(ind);
			indexBuffer.push_back(ind % 2U == 0U ? ind + 1U : ind - 1U);
			indexBuffer.push_back(ind);
			indexBuffer.push_back(ind % 2U == 0U ? ind + 2U : ind - 2U);
			ind += ind % 2U == 0U ? 3U : 1U;
		}
		for (ind = 0U; ind < 4U; ++ind)
		{
			indexBuffer.push_back(ind);
			indexBuffer.push_back(ind + 4U);
		}
	}

	void PrimitiveMesh::InitSphere()
	{
		float subDiv = 30.f;
		unsigned int vertexAmount = static_cast<unsigned int>(vertexBuffer.size());
		for (float teta = 0.f; teta < Math::doublePi; teta += Math::doublePi / subDiv)
		{
			vertexBuffer.push_back(Math::Vector3(cosf(teta), sinf(teta), 0.f));
			if (teta > 0.f)
			{
				indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 2U);
				indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 1U);
			}
		}
		indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 1U);
		indexBuffer.push_back(vertexAmount);
		vertexAmount = static_cast<unsigned int>(vertexBuffer.size());
		for (float teta = 0.f; teta < Math::doublePi; teta += Math::doublePi / subDiv)
		{
			vertexBuffer.push_back(Math::Vector3(0.f, cosf(teta), sinf(teta)));
			if (teta > 0.f)
			{
				indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 2U);
				indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 1U);
			}
		}
		indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 1U);
		indexBuffer.push_back(vertexAmount);
		vertexAmount = static_cast<unsigned int>(vertexBuffer.size());
		for (float teta = 0.f; teta < Math::doublePi; teta += Math::doublePi / subDiv)
		{
			vertexBuffer.push_back(Math::Vector3(cosf(teta), 0.f, sinf(teta)));
			if (teta > 0.f)
			{
				indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 2U);
				indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 1U);
			}
		}
		indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 1U);
		indexBuffer.push_back(vertexAmount);
	}

	void PrimitiveMesh::InitCapsule(const float p_halfHeight, const float p_radius)
	{
		vertexBuffer.clear();
		indexBuffer.clear();
		float subDiv = 30.f;
		unsigned int vertexAmount = static_cast<unsigned int>(vertexBuffer.size());
		for (float teta = 0.f; teta < Math::doublePi; teta += Math::doublePi / subDiv)
		{
			vertexBuffer.push_back(Math::Vector3(p_halfHeight, sinf(teta) * p_radius, cosf(teta) * p_radius));
			if (teta > 0.f)
			{
				indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 2U);
				indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 1U);
			}
		}
		indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 1U);
		indexBuffer.push_back(vertexAmount);
		vertexAmount = static_cast<unsigned int>(vertexBuffer.size());
		for (float teta = 0.f; teta < Math::doublePi; teta += Math::doublePi / subDiv)
		{
			vertexBuffer.push_back(Math::Vector3(-p_halfHeight, sinf(teta) * p_radius, cosf(teta) * p_radius));
			if (teta > 0.f)
			{
				indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 2U);
				indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 1U);
			}
		}
		indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 1U);
		indexBuffer.push_back(vertexAmount);
		vertexAmount = static_cast<unsigned int>(vertexBuffer.size());
		for (float teta = 0.f; teta < Math::doublePi; teta += Math::doublePi / subDiv)
		{
			if (teta < Math::pi)
			{
				vertexBuffer.push_back(Math::Vector3(p_halfHeight + sin(teta) * p_radius, 0.f, cosf(teta) * p_radius));
			}
			else
			{
				vertexBuffer.push_back(Math::Vector3(-p_halfHeight + sin(teta) * p_radius, 0.f, cosf(teta) * p_radius));
			}
			if (teta > 0.f)
			{
				indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 2U);
				indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 1U);
			}
		}
		indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 1U);
		indexBuffer.push_back(vertexAmount);
		vertexAmount = static_cast<unsigned int>(vertexBuffer.size());
		for (float teta = 0.f; teta < Math::doublePi; teta += Math::doublePi / subDiv)
		{
			if (teta < Math::pi)
			{
				vertexBuffer.push_back(Math::Vector3(p_halfHeight + sin(teta) * p_radius, cosf(teta) * p_radius, 0.f));
			}
			else
			{
				vertexBuffer.push_back(Math::Vector3(-p_halfHeight + sin(teta) * p_radius, cosf(teta) * p_radius, 0.f));
			}
			if (teta > 0.f)
			{
				indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 2U);
				indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 1U);
			}
		}
		indexBuffer.push_back(static_cast<unsigned int>(vertexBuffer.size()) - 1U);
		indexBuffer.push_back(vertexAmount);

		if (!isFinishToInit)
		{
			InitRHI();
			return;
		}

		Wrapper::RHI::RebindCollider(VBO, VAO, EBO, vertexBuffer, indexBuffer);
	}
}

