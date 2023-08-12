// イージングエディタ
# include <Siv3D.hpp> // OpenSiv3D v0.6.11

void Main_easing_editor()
{
	constexpr Size SceneSize{ 1600, 1200 };
	constexpr Size DefaultWindowSize{ 800, 600 };

	Scene::Resize(SceneSize);
	Scene::SetResizeMode(ResizeMode::Keep);
	Window::Resize(DefaultWindowSize);

	Scene::SetBackground(ColorF{ 0.1 });

	struct EasingFuncRatio
	{
		StringView name;
		double (*func)(double);
		double ratio;
	};

	std::array<EasingFuncRatio, 30> easingFuncRatio = { {
		{ U"InSine"_sv, EaseInSine, 0.0 },
		{ U"InQuad"_sv, EaseInQuad, 0.0 },
		{ U"InCubic"_sv, EaseInCubic, 0.0 },
		{ U"InQuart"_sv, EaseInQuart, 0.0 },
		{ U"InQuint"_sv, EaseInQuint, 0.0 },
		{ U"InExpo"_sv, EaseInExpo, 0.0 },
		{ U"InCirc"_sv, EaseInCirc, 0.0 },
		{ U"InBack"_sv, EaseInBack, 0.0 },
		{ U"InElastic"_sv, EaseInElastic, 0.0 },
		{ U"InBounce"_sv, EaseInBounce, 0.0 },
		{ U"OutSine"_sv, EaseOutSine, 0.0 },
		{ U"OutQuad"_sv, EaseOutQuad, 0.0 },
		{ U"OutCubic"_sv, EaseOutCubic, 0.0 },
		{ U"OutQuart"_sv, EaseOutQuart, 0.0 },
		{ U"OutQuint"_sv, EaseOutQuint, 0.0 },
		{ U"OutExpo"_sv, EaseOutExpo, 0.0 },
		{ U"OutCirc"_sv, EaseOutCirc, 0.0 },
		{ U"OutBack"_sv, EaseOutBack, 0.0 },
		{ U"OutElastic"_sv, EaseOutElastic, 0.0 },
		{ U"OutBounce"_sv, EaseOutBounce, 0.0 },
		{ U"InOutSine"_sv, EaseInOutSine, 0.0 },
		{ U"InOutQuad"_sv, EaseInOutQuad, 0.0 },
		{ U"InOutCubic"_sv, EaseInOutCubic, 0.0 },
		{ U"InOutQuart"_sv, EaseInOutQuart, 0.0 },
		{ U"InOutQuint"_sv, EaseInOutQuint, 0.0 },
		{ U"InOutExpo"_sv, EaseInOutExpo, 0.0 },
		{ U"InOutCirc"_sv, EaseInOutCirc, 0.0 },
		{ U"InOutBack"_sv, EaseInOutBack, 0.0 },
		{ U"InOutElastic"_sv, EaseInOutElastic, 0.0 },
		{ U"InOutBounce"_sv, EaseInOutBounce, 0.0 },
	} };

	while (System::Update())
	{
		const Size GraphAreaSize{ 1200, Scene::Height() };
		const Size ControlAreaSize{ Scene::Width() - GraphAreaSize.x, Scene::Height() };

		double ratioSum = 0.0;
		for (const auto& e : easingFuncRatio)
		{
			ratioSum += e.ratio;
		}

		// Graph Area

		{
			const ScopedViewport2D viewport{ Point{ 0, 0 }, GraphAreaSize };

			constexpr int N = 200;

			LineString points;

			for (int i : step(N))
			{
				const double x0 = static_cast<double>(i) / N;  // 0～1
				const double x = 200.0 + 800.0 * x0;  // 200～1000

				double y0 = 0.0;

				for (const auto& e : easingFuncRatio)
				{
					y0 += e.ratio * e.func(x0);
				}

				if (ratioSum > 1e-6)
				{
					y0 /= ratioSum;
				}

				const double y = 1000.0 - 800.0 * y0;  // 200～1000

				points << Vec2{ x, y };
			}

			points.draw(2.0);

		}

		// Control Area

		{
			const ScopedViewport2D viewport{ Point{ GraphAreaSize.x, 0 }, ControlAreaSize };
			const Transformer2D transformer{ Mat3x2::Identity(), Mat3x2::Translate(GraphAreaSize.x, 0) };

			Rect{ 0, 0, ControlAreaSize }.draw(ColorF{ 0.14 });

			for (int i : step(30))
			{
				SimpleGUI::Slider(easingFuncRatio[i].name, easingFuncRatio[i].ratio, Vec2{ 40, 40 + 32 * i }, 160.0, 160.0);
			}

			if (SimpleGUI::Button(U"Copy"_sv, Vec2{ 40, 40 + 32 * 30 + 40 }, none, ratioSum > 1e-6))
			{
				String code;

				for (const auto& e : easingFuncRatio)
				{
					if (e.ratio > 1e-6)
					{
						if (not code.isEmpty())
						{
							code += U" + ";
						}

						code += U"Ease{}(x) * {:.2f}"_fmt(e.name, e.ratio / ratioSum);
					}
				}

				Clipboard::SetText(code);

				System::MessageBoxOK(U"クリップボードにコピーしました：\n{}"_fmt(code));
			}
		}
	}
}
