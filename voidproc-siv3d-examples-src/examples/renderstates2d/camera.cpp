// キャラの少し前の方を2Dカメラで追従する

# include <Siv3D.hpp> // OpenSiv3D v0.6.6

class Siv3dkun
{
	const int SpriteWidth = 20;
	const int SpriteHeight = 28;

	Texture m_texture;
	Vec2 m_pos;
	Vec2 m_speed;
	double m_timeChangeSpeed;
	Vec2 m_cameraTarget;

public:
	Siv3dkun()
		: m_texture(U"example/spritesheet/siv3d-kun-16.png")
		, m_pos(Scene::Center())
		, m_speed(30.0, 0)
		, m_timeChangeSpeed(1.0)
		, m_cameraTarget()
	{
	}

	void update()
	{
		if (Scene::Time() > m_timeChangeSpeed)
		{
			m_speed.x = Math::Sign(m_speed.x) * (-1) * Random(40, 300);
			m_timeChangeSpeed += Random(1.0, 3.0);
		}

		m_pos += m_speed * Scene::DeltaTime();

		m_cameraTarget.x = Clamp(m_cameraTarget.x + Math::Sign(m_speed.x) * 120 * Scene::DeltaTime(), -60.0, 60.0);
	}

	void draw() const
	{
		const auto renderState = ScopedRenderStates2D{ SamplerState::ClampNearest };

		const int animationFrame = (m_speed.x < 0 ? 6 : 12) + (int)(Periodic::Triangle0_1(0.5s) * 2.0 + 0.5);

		m_texture((animationFrame % 6) * SpriteWidth, (animationFrame / 6) * SpriteHeight, SpriteWidth, SpriteHeight)
			.scaled(8)
			.drawAt(m_pos);
	}

	const Vec2& position() const
	{
		return m_pos;
	}

	Vec2 cameraTargetPosition() const
	{
		return m_pos + m_cameraTarget;
	}
};

void Main_camera()
{
	Scene::SetBackground(ColorF{ 0, 0, 0 });

	Siv3dkun siv3dkun;

	Camera2D camera{ Scene::Center() };

	Image bgImage{ 256, 256, ColorF{ 0.6, 0.6, 0.6 } };
	Rect(0, 0, 128).overwrite(bgImage, ColorF{ 0.8, 0.8, 0.8 });
	Rect(128, 128, 128).overwrite(bgImage, ColorF{ 0.8, 0.8, 0.8 });
	const Texture bgTexture{ bgImage };

	while (System::Update())
	{
		siv3dkun.update();

		camera.jumpTo(siv3dkun.cameraTargetPosition(), 1.0);

		{
			const auto transformer = camera.createTransformer();

			// 背景
			{
				const ScopedRenderStates2D sampler{ SamplerState::RepeatLinear };

				bgTexture.mapped(1920, Scene::Height()).draw(-1920 / 2, 0);
			}

			siv3dkun.draw();
		}
	}
}
