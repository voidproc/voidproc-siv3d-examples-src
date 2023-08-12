// サイコロを描く

#include <Siv3D.hpp> // OpenSiv3D v0.6.11

void drawDice()
{
	// ダイス本体

	const double diceSize = 4.0;

	Box{ 0, 0, 0, diceSize }.draw(ColorF{ 0.9, 0.9, 0.9 }.removeSRGBCurve());

	// ダイスの目

	constexpr std::array<std::array<Vec3, 6>, 6> dotPosition = { {
		{ Vec3{ 0, 1, 0 }, },
		{ Vec3{ 1, -0.6, -0.6 }, Vec3{ 1, 0.6, 0.6 },  },
		{ Vec3{ -0.6, -0.6, 1 }, Vec3{ 0, 0, 1 }, Vec3{ 0.6, 0.6, 1 }, },
		{ Vec3{ -0.6, -0.6, -1 }, Vec3{ 0.6, 0.6, -1 }, Vec3{ -0.6, 0.6, -1 }, Vec3{ 0.6, -0.6, -1 }, },
		{ Vec3{ -1, -0.6, -0.6 }, Vec3{ -1, 0.6, 0.6 }, Vec3{ -1, 0.6, -0.6 }, Vec3{ -1, -0.6, 0.6 }, Vec3{ -1, 0, 0 }, },
		{ Vec3{ -0.6, -1, -0.6 }, Vec3{ -0.6, -1, 0 }, Vec3{ -0.6, -1, 0.6 }, Vec3{ 0.6, -1, -0.6 }, Vec3{ 0.6, -1, 0 }, Vec3{ 0.6, -1, 0.6 } },
	} };

	constexpr std::array<Vec3, 6> dotRotation = {
		Vec3{ 0, 0, 0 }, Vec3{ 0, 0, -90_deg }, Vec3{ 90_deg, 0, 0 }, Vec3{ -90_deg, 0, 0 }, Vec3{ 0, 0, 90_deg }, Vec3{ 180_deg, 0, 0 },
	};

	constexpr std::array<double, 6> dotSizeScale = {
		1.2, 1, 1, 1, 1, 1,
	};

	constexpr std::array<Color, 6> dotColor = {
		Palette::Darkred, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
	};

	for (int i : step(6))
	{
		const int nDots = i + 1;

		for (int j : step(nDots))
		{
			const double dotSize = 0.4;

			const auto mat = Mat4x4::RollPitchYaw(dotRotation[i].x, dotRotation[i].y, dotRotation[i].z)
				.translated(dotPosition[i][j] * (diceSize / 2 + 0.0001));

			Disc{ dotSize * dotSizeScale[i] }.draw(mat, dotColor[i]);
		}
	}
}

void Main_dice()
{
	const ColorF bgColor = ColorF{ 0.1, 0.15, 0.2 }.removeSRGBCurve();

	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };

	Graphics3D::SetGlobalAmbientColor(ColorF{ 0.6, 0.65, 0.7 });

	BasicCamera3D camera{ renderTexture.size(), 30_deg };

	while (System::Update())
	{
		const double angle = Scene::Time() * 0.3;
		camera.setView(Vec3{ 28 * Math::Cos(angle), 16, 28 * Math::Sin(angle) }, Vec3{});

		Graphics3D::SetCameraTransform(camera);

		{
			const ScopedRenderTarget3D target{ renderTexture.clear(bgColor) };

			{
				const auto mat = Mat4x4::RollPitchYaw(0.5 * Scene::Time(), 0.1 * Scene::Time(), 0.8 * Scene::Time());

				const Transformer3D transformer{ mat };

				drawDice();
			}
		}

		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}
}
