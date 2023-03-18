// テクスチャを白く点滅させるピクセルシェーダ

#include <Siv3D.hpp> // OpenSiv3D v0.6.7

struct WhiteEffectConstants
{
	float strength;
	float unused[3];
};

void Main_pixelshader_white()
{
	Scene::SetBackground(Color{ 30, 30, 30 });

	const Texture texture{ U"example/siv3d-kun.png" };

	const PixelShader psWhite = HLSL{ U"shader/white.hlsl", U"PS" };
	if (not psWhite)
	{
		throw Error{ U"Failed to load a shader file" };
	}

	ConstantBuffer<WhiteEffectConstants> cb;

	while (System::Update())
	{
		cb->strength = Saturate(Math::Sin(Scene::Time() * 5) * 0.5 + 0.5);

		{
			Graphics2D::SetPSConstantBuffer(1, cb);

			const ScopedCustomShader2D shader(psWhite);

			texture.scaled(0.75).drawAt(Scene::Center());
		}
	}
}
