# Red triangle Vulkan application

Setup for basic Vulkan application using GLFW.

Heavily following the guide from vulkan-tutorial.com

#### Linux

Requires the following packages:
* vulkan-devel
* vulkan driver for hardware (testing on intel)
* glfw
* glslang (for SPIR-V compiler)



#### Windows

Tested on Windows 2019. 

Requires:

- glfw in ./thirdparty/ (e.g. thirdparty/glfw/lib-vc2019)
- glm in ./thirdparty/ (e.g. ./thirdparty/glm/glm/glm.hpp)
- stb in ./thirdparty/ (e.g. ./thirdparty/stb/stb/stb_image.h)
- Vulkan (LunarG).
- Vulkan drivers
- Change vcxproj to point correctly to VulkanSDK and thirdparty stuff.