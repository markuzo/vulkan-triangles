#pragma once

enum AAType {
	MSAA
};

enum TextureFilteringType {
	None,
	Bilinear,
	Trilinear,
	Anisotropic1,
	Anisotropic2,
	Anisotropic4,
	Anisotropic8,
	Anisotropic16
};


class Config {
public:
	bool VSync = true;
	AAType AA;
	TextureFilteringType TextureFiltering;

	bool Shadows = true;

	bool SaveToFile = false;
};
