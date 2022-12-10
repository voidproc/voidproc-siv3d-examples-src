// レンダーテクスチャとガウスぼかし、ピクセルシェーダを使ったレトロコンソール的表現

# include <Siv3D.hpp> // OpenSiv3D v0.6.6

void drawBg_retro()
{
	Scene::Rect().draw(Arg::top = ColorF(0.15), Arg::bottom = ColorF(0.40));
}

void drawScene_retro()
{
	const double angle = Scene::Time() * 0.7;
	TextureAsset(U"cat").resized(128).rotated(Scene::Time() * 1.6).drawAt(Scene::CenterF() + Circular(150, angle));
	TextureAsset(U"ghost").resized(128).rotated(Scene::Time() * 2).drawAt(Scene::CenterF() + Circular(150, angle + Math::HalfPiF));
	TextureAsset(U"alien").resized(128).rotated(Scene::Time() * 1.2).drawAt(Scene::CenterF() + Circular(150, angle + Math::PiF));
	TextureAsset(U"nko").resized(128).rotated(Scene::Time() * 3).drawAt(Scene::CenterF() + Circular(150, angle - Math::HalfPiF));
}

void drawScanline()
{
	for (int i : step(Scene::Height() / 4))
	{
		int y = i * 4;
		Line(0, y, Scene::Width(), y).draw(1, ColorF(0, 0.80));
	}
}

void Main_retro()
{
	Scene::SetBackground(Palette::Black);

	TextureAsset::Register(U"cat", Emoji(U"🐈"));
	TextureAsset::Register(U"ghost", Emoji(U"👻"));
	TextureAsset::Register(U"alien", Emoji(U"👾"));
	TextureAsset::Register(U"nko", Emoji(U"💩"));

	RenderTexture rtScene(Scene::Size(), Palette::Black);
	RenderTexture rtBlurA(Scene::Size()), rtBlurB(Scene::Size());
	RenderTexture rtBlur4A(Scene::Size() / 4), rtBlur4B(Scene::Size() / 4);
	RenderTexture rtBlur8A(Scene::Size() / 8), rtBlur8B(Scene::Size() / 8);

	// GUI
	double sliderA = 0.12, sliderB = 0.24, sliderC = 0.75;
	bool enableFx = false;

	// カスタムシェーダ
	const PixelShader psDefault = HLSL{ U"example/shader/hlsl/default2d.hlsl", U"PS" };
	const PixelShader psFx = HLSL{ U"shader/green.hlsl", U"PS" };

	while (System::Update())
	{
		{
			// 背景とシーンをレンダーテクスチャに描き込む
			{
				ScopedRenderTarget2D target(rtScene);
				rtScene.clear(Palette::Black);
				drawBg_retro();
				drawScene_retro();
			}

			// シーン（背景なし）にガウスぼかしを掛ける（ブルーム用）
			if (enableFx)
			{
				ScopedRenderTarget2D target(rtBlurA);
				ScopedRenderStates2D state(BlendState::Additive);
				rtBlurA.clear(Palette::Black);
				drawScene_retro();

				Shader::GaussianBlur(rtBlurA, rtBlurB, rtBlurA);
				Shader::Downsample(rtBlurA, rtBlur4A);
				Shader::GaussianBlur(rtBlur4A, rtBlur4B, rtBlur4A);
				Shader::Downsample(rtBlur4A, rtBlur8A);
				Shader::GaussianBlur(rtBlur8A, rtBlur8B, rtBlur8A);
			}

			// 背景とシーンを描き込んだテクスチャを描画
			// 緑色にするシェーダを適用
			ScopedCustomShader2D shader(enableFx ? psFx : psDefault);
			rtScene.draw();

			// スキャンライン
			if (enableFx)
				drawScanline();

			// ブルーム
			if (enableFx)
			{
				ScopedRenderStates2D state(BlendState::Additive);
				rtBlurA.draw(ColorF(sliderA));
				rtBlur4A.resized(Scene::Size()).draw(ColorF(sliderB));
				rtBlur8A.resized(Scene::Size()).draw(ColorF(sliderC));
			}
		}

		{
			const Transformer2D t{ Mat3x2::Scale(0.75, Vec2(0, 0)), TransformCursor::Yes };

			SimpleGUI::Slider(Format(sliderA), sliderA, 0.0, 2.0, Vec2(20, 20));
			SimpleGUI::Slider(Format(sliderB), sliderB, 0.0, 2.0, Vec2(20, 60));
			SimpleGUI::Slider(Format(sliderC), sliderC, 0.0, 2.0, Vec2(20, 100));
			SimpleGUI::CheckBox(enableFx, U"enable", Vec2(20, 140));
		}
	}
}
