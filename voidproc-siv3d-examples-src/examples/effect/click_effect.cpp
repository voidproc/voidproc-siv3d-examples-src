// マウスクリック位置にエフェクト

# include <Siv3D.hpp> // OpenSiv3D v0.6.6

struct ClickEffect : IEffect
{
	Vec2 m_pos;
	Effect& m_effect;

	ClickEffect(const Vec2& pos, Effect& effect)
		: m_pos{ pos }
		, m_effect{ effect }
	{
	}

	bool update(double) override
	{
		m_effect.add<ClickEffect1>(m_pos);

		m_effect.add<ClickEffect2>(m_pos);

		for (int i : step(8))
		{
			const double angle = Random(Math::TwoPi);

			m_effect.add<ClickEffect3>(
				m_pos + Circular(Random(5, 35), angle),
				Circular(80, angle));
		}

		return false;
	}

	struct ClickEffect1 : IEffect
	{
		Vec2 m_pos;

		ClickEffect1(const Vec2& pos)
			: m_pos{ pos }
		{
		}

		bool update(double t) override
		{
			const double lifetime = 0.30;

			const double t_0_1 = Clamp(t / lifetime, 0.0, 1.0);

			const double size = 15 + 45 * EaseInOutSine(t_0_1);
			const double alpha = 1.0 - 1.0 * EaseInCubic(t_0_1);

			RectF{ size }
				.setCenter(m_pos)
				.rotatedAt(m_pos, 45_deg)
				.drawFrame(5.0 - 5.0 * EaseInCubic(t_0_1), ColorF{ Palette::Aqua, alpha });

			return (t < lifetime);
		}
	};

	struct ClickEffect2 : IEffect
	{
		Vec2 m_pos;

		ClickEffect2(const Vec2& pos)
			: m_pos{ pos }
		{
		}

		bool update(double t) override
		{
			const double delay = 0.10;
			const double lifetime = delay + 0.30;

			if (t >= delay)
			{
				const double t_0_1 = Clamp((t - delay) / lifetime, 0.0, 1.0);

				const double size = 10 + 70 * (t_0_1);
				const double alpha = 1.0 - 1.0 * (t_0_1);

				RectF{ size }
					.setCenter(m_pos)
					.rotatedAt(m_pos, 45_deg)
					.drawFrame(1.5 - 0.5 * t_0_1, ColorF{ Palette::Aqua, alpha });
			}

			return (t < lifetime);
		}
	};

	struct ClickEffect3 : IEffect
	{
		Vec2 m_pos;
		Vec2 m_vel;
		double m_size;

		ClickEffect3(const Vec2& pos, const Vec2& vel)
			: m_pos{ pos }
			, m_vel{ vel }
			, m_size{ Random(4.0, 15.0) }
		{
		}

		bool update(double t) override
		{
			const double lifetime = 0.28;

			const double t_0_1 = Clamp(t / lifetime, 0.0, 1.0);

			const double size = m_size * (1.0 - t_0_1);
			const double alpha = 1.0 - 1.0 * (t_0_1);

			m_pos += m_vel * Scene::DeltaTime();

			RectF{ size }
				.setCenter(m_pos)
				.rotatedAt(m_pos, t_0_1 * 60_deg)
				.drawFrame(3.0, ColorF{ Palette::Aqua, alpha });

			return (t < lifetime);
		}
	};
};

void Main_click_effect()
{
	Scene::SetBackground(ColorF{ U"#05070F" });

	Effect effect;

	while (System::Update())
	{
		if (MouseL.down())
		{
			effect.add<ClickEffect>(Cursor::PosF(), effect);
		}

		effect.update();
	}
}
