#include <Siv3D.hpp> // OpenSiv3D v0.6.0

const Size FieldSize{ 320, 160 };

void drawWave(const int n_div = 64)
{
	RectF(FieldSize).drawFrame(2);

	for (int i : step(n_div))
	{
		const auto sinwave = [&](const int t)
		{
			return Vec2(
				t * FieldSize.x / n_div,
				FieldSize.y / 2 * (1 + 0.8 * Sin(t * Math::TwoPiF * 2 / n_div + Scene::Time() * 12.0)));
		};

		Line(sinwave(i), sinwave(i + 1)).draw();
	}
}

void Main()
{
	while (System::Update())
	{
		{
			const Transformer2D transformer(Mat3x2::Translate(Cursor::PosF() - FieldSize / 2));

			drawWave();
		}
	}
}
