#ifndef CORE_JSON_H_INCLUDED
#define CORE_JSON_H_INCLUDED

#include <Containers/Vector.hpp>
#include "define.h"
#include "Maths/Vector2.hpp" 
#include "Maths/Vector3.h" 
#include "MtlParser.h"

namespace gce
{
	class File;

	struct Vertex
	{
		Vector3f32 position; // v
		Vector3f32 normal; // vn
		Vector2f32 textureCoordinate; // vt
	};
	struct Mesh
	{
		Vector <uint32> indices;
		MtlMaterial material;
	};
	struct MTLData
	{
		String mtlId;
		uint32 mtlIndexBegin;
		uint32 mtlIndexEnd;

	};
	struct Json
	{
	public:
		Json(String const& path);
		Json(String const&& path);
		~Json();

		void LoadJson();
		UnorderedMap<String, MtlMaterial> LoadMtl(String& path);

		Vector<Mesh> meshs;
		Vector<Vertex> vertices;
		Vector<MTLData> mtlData;
		bool mtlExists = false;

	private:
		void FreeVectors();
		File* pFile;
		String m_path;
		Vector<Vector3f32> m_tempPosVect;
		Vector<Vector2f32> m_tempCoordVect;
		Vector<Vector3f32> m_tempNormVect;
		Vector<uint32> m_tempIndiceVect;
	};
}

#endif