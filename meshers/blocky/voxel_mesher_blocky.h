#ifndef VOXEL_MESHER_BLOCKY_H
#define VOXEL_MESHER_BLOCKY_H

#include "../../util/zprofiling.h"
#include "../../voxel.h"
#include "../../voxel_buffer.h"
#include "../../voxel_library.h"
#include <core/reference.h>
#include <scene/resources/mesh.h>

// TODO Should be renamed VoxelMesherBlocky or something like that
class VoxelMesherBlocky : public Reference {
	GDCLASS(VoxelMesherBlocky, Reference)

public:
	static const unsigned int MAX_MATERIALS = 8; // Arbitrary. Tweak if needed.
	static const int MINIMUM_PADDING = 1;

	VoxelMesherBlocky();

	void set_library(Ref<VoxelLibrary> library);
	Ref<VoxelLibrary> get_library() const { return _library; }

	void set_occlusion_darkness(float darkness);
	float get_occlusion_darkness() const { return _baked_occlusion_darkness; }

	void set_occlusion_enabled(bool enable);
	bool get_occlusion_enabled() const { return _bake_occlusion; }

	Array build(const VoxelBuffer &buffer_ref, unsigned int channel, int padding);
	Ref<ArrayMesh> build_mesh(Ref<VoxelBuffer> buffer_ref, unsigned int channel, Array materials, Ref<ArrayMesh> mesh = Ref<ArrayMesh>());

protected:
	static void _bind_methods();

private:
	struct Arrays {
		Vector<Vector3> positions;
		Vector<Vector3> normals;
		Vector<Vector2> uvs;
		Vector<Color> colors;
		Vector<int> indices;
	};

	Ref<VoxelLibrary> _library;
	Arrays _arrays[MAX_MATERIALS];
	float _baked_occlusion_darkness;
	bool _bake_occlusion;

#ifdef VOXEL_PROFILING
	ZProfiler _zprofiler;
	Dictionary get_profiling_info() const { return _zprofiler.get_all_serialized_info(); }
#endif
};

#endif // VOXEL_MESHER_BLOCKY_H