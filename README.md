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

- glfw in ./thirdparty/
- Vulkan (LunarG).
- Vulkan drivers
- Change vcxproj to point correctly to VulkanSDK and glfw.