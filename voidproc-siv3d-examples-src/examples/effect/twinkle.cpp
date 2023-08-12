// キラキラ

#include <Siv3D.hpp> // OpenSiv3D v0.6.11

struct Twinkle : IEffect
{
	Vec2 pos;
	double angle;
	double scale;

	Twinkle(const Vec2 pos) : pos(pos), angle(Sample({ 0_deg, 45_deg })), scale(Random(0.2, 1.0))
	{
	}

	bool update(double t) override
	{
		scale *= 0.988;

		const double outer = (4 + 25 + 25 * Sin(t * 6_pi)) * scale;
		const double inner = (0.5 + 1 + 1 * Sin(t * 6_pi)) * scale;

		Shape2D::NStar(4, outer, inner, pos, angle).draw(Alpha(1 + 120 + 120 * Sin(t * 6_pi)));

		return t < 0.50;
	}
};

void Main_twinkle()
{
	Effect effect;

	double timeFxSpawned = 0;

	while (System::Update())
	{
		if (Scene::Time() - timeFxSpawned > 0.03)
		{
			effect.add<Twinkle>(Cursor::Pos() + RandomVec2(Random(80.0)));

			timeFxSpawned = Scene::Time();
		}

		effect.update();
	}
}
