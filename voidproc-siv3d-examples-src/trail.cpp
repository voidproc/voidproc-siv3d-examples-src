#include <Siv3D.hpp> // OpenSiv3D v0.6.0

// 徐々に消えるテクスチャ（残像）
struct Afterimage : IEffect
{
	TexturedQuad m_texture;
	Vec2 m_pos;
	double m_fadeoutTime;

	Afterimage(const TexturedQuad& texture, const Vec2& pos, double fadeoutTime = 1.0)
		: m_texture(texture), m_pos(pos), m_fadeoutTime(fadeoutTime)
	{
	}

	bool update(double t) override
	{
		m_texture.drawAt(m_pos, AlphaF(1.0 - t / m_fadeoutTime));
		return t < m_fadeoutTime;
	}
};

void Main()
{
	Scene::SetBackground(Palette::White);

	const Texture dolphin(Emoji(U"🐬"));
	Effect effect;
	Stopwatch interval{ StartImmediately::Yes };

	while (System::Update())
	{
		const double t = Scene::Time();
		const auto texture = dolphin.scaled(1.0 + 0.4 * Sin(t * 3.0)).rotated(t * -6.0);
		const Vec2 pos = Scene::CenterF().movedBy(200 * Cos(t * 5.0), 200 * Sin(t * 4.0));
		texture.drawAt(pos);

		// 0.1秒ごとに残像を生成
		if (interval.elapsed() >= 0.1s)
		{
			effect.add<Afterimage>(texture, pos, 0.7);  //0.7秒かけて消える
			interval.restart();
		}

		effect.update();
	}
}
