// レンダーテクスチャとガウスぼかしを使ったブルーム効果

# include <Siv3D.hpp> // OpenSiv3D v0.6.6

void drawBg()
{
	Scene::Rect().draw(Arg::top = ColorF(0.08), Arg::bottom = ColorF(0.25));
}

void drawScene()
{
	TextureAsset(U"cat").resized(128).rotated(Scene::Time() * 2).drawAt(Scene::CenterF() + Circular(150, Scene::Time()));
	TextureAsset(U"ghost").resized(128).rotated(Scene::Time() * 2.3).drawAt(Scene::CenterF() + Circular(150, Scene::Time() + Math::HalfPiF));
	TextureAsset(U"alien").resized(128).rotated(Scene::Time() * 2.7).drawAt(Scene::CenterF() + Circular(150, Scene::Time() + Math::PiF));
	TextureAsset(U"nko").resized(128).rotated(Scene::Time() * 3.5).drawAt(Scene::CenterF() + Circular(150, Scene::Time() - Math::HalfPiF));

}

void Main_bloom()
{
	Scene::SetBackground(Palette::Black);

	TextureAsset::Register(U"cat", Emoji(U"🐈"));
	TextureAsset::Register(U"ghost", Emoji(U"👻"));
	TextureAsset::Register(U"alien", Emoji(U"👾"));
	TextureAsset::Register(U"nko", Emoji(U"💩"));

	// シーン
	RenderTexture rtScene(Scene::Size(), Palette::Black);

	// Bloom用
	RenderTexture rtBlurA(Scene::Size()), rtBlurB(Scene::Size());
	RenderTexture rtBlur4A(Scene::Size() / 4), rtBlur4B(Scene::Size() / 4);
	RenderTexture rtBlur8A(Scene::Size() / 8), rtBlur8B(Scene::Size() / 8);

	// GUI
	double sliderA = 0.2, sliderB = 0.25, sliderC = 0.37;
	bool useGrayscale = false;
	bool use = false;

	// カスタムシェーダ
	const PixelShader psDefault = HLSL{ U"example/shader/hlsl/default2d.hlsl", U"PS" };
	const PixelShader psGrayscale = HLSL{ U"example/shader/hlsl/grayscale.hlsl", U"PS" };

	while (System::Update())
	{
		drawBg();

		{
			ScopedCustomShader2D shader(useGrayscale ? psGrayscale : psDefault);
			drawScene();

			{
				ScopedRenderTarget2D target(rtScene);
				ScopedRenderStates2D state(BlendState::Additive);
				rtScene.clear(Palette::Black);
				drawScene();
			}

			if (use)
			{
				Shader::GaussianBlur(rtScene, rtBlurB, rtBlurA);
				Shader::Downsample(rtBlurA, rtBlur4A);
				Shader::GaussianBlur(rtBlur4A, rtBlur4B, rtBlur4A);
				Shader::Downsample(rtBlur4A, rtBlur8A);
				Shader::GaussianBlur(rtBlur8A, rtBlur8B, rtBlur8A);

				{
					ScopedRenderStates2D state(BlendState::Additive);
					rtBlurA.draw(ColorF(sliderA));
					rtBlur4A.resized(Scene::Size()).draw(ColorF(sliderB));
					rtBlur8A.resized(Scene::Size()).draw(ColorF(sliderC));
				}
			}
		}

		{
			const Transformer2D t{ Mat3x2::Scale(0.75, Vec2(0, 0)), TransformCursor::Yes };

			SimpleGUI::Slider(Format(sliderA), sliderA, 0.0, 2.0, Vec2(20, 20));
			SimpleGUI::Slider(Format(sliderB), sliderB, 0.0, 2.0, Vec2(20, 60));
			SimpleGUI::Slider(Format(sliderC), sliderC, 0.0, 2.0, Vec2(20, 100));
			SimpleGUI::CheckBox(useGrayscale, U"grayscale", Vec2(20, 140));
			SimpleGUI::CheckBox(use, U"use", Vec2(20, 180));
		}

	}
}
