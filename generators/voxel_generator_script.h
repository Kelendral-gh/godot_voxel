#ifndef VOXEL_GENERATOR_SCRIPT_H
#define VOXEL_GENERATOR_SCRIPT_H

#include "voxel_generator.h"
#include <core/object/script_language.h> // needed for GDVIRTUAL macro
#include <core/object/gdvirtual.gen.inc> // Also needed for GDVIRTUAL macro...

namespace zylann::voxel {

// Generator based on a script, like GDScript, C# or NativeScript.
// The script is expected to properly handle multithreading.
class VoxelGeneratorScript : public VoxelGenerator {
	GDCLASS(VoxelGeneratorScript, VoxelGenerator)
public:
	VoxelGeneratorScript();

	Result generate_block(VoxelGenerator::VoxelQueryData &input) override;
	int get_used_channels_mask() const override;

protected:
	GDVIRTUAL3(_generate_block, Ref<VoxelBuffer>, Vector3i, int)
	GDVIRTUAL0RC(int, _get_used_channels_mask) // I think `C` means `const`?

private:
	static void _bind_methods();
};

} // namespace zylann::voxel

#endif // VOXEL_GENERATOR_SCRIPT_H
