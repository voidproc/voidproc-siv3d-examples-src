// グリフアニメーション

#include <Siv3D.hpp> // OpenSiv3D v0.6.6

void Main_glyph()
{
	Scene::SetBackground(Color(240));

	const Font font(64, Typeface::Bold);
	const Font fontFallback(64, Typeface::MonochromeEmoji);
	font.addFallback(fontFallback);

	const String text = U"Glyph in Siv3D";

	const RectF region = font(text).regionAt(Scene::Center());

	const auto g2 = font.getGlyph(U'2');

	double tr = 0;

	while (System::Update())
	{
		double t = Min(1.0, (Scene::Time() - tr) / 1.0);

		if (KeySpace.down()) {
			tr = Scene::Time();
		}

		Vec2 pos{ region.tl() };

		for (const auto& g : font.getGlyphs(text))
		{
			if (g.codePoint == U'G')
			{
				g.texture.draw(pos + g.getOffset() + RandomVec2(200.0 * (1.0 - t)), Color(48));
			}
			else if (g.codePoint == U'S')
			{
				g.texture.draw(pos + g.getOffset() - Vec2{ 0, 1000 * EaseIn(Easing::Cubic, 1.0 - t) }, Color(48));
			}
			else if (g.codePoint == U'3' && t < 1.0)
			{
				g2.texture.draw(pos + g2.getOffset(), Color(48, 255 * Periodic::Square0_1(0.1s)));
				pos.x += g2.xAdvance;
				continue;
			}
			else if (g.codePoint == U'D')
			{
				const double ratio = Math::Cos(Math::TwoPi * t * 4);
				g.texture.scaled(ratio, 1.0).draw(pos + g.getOffset() + Vec2(g.xAdvance * (1 - ratio) / 2, 0), Color(48));
			}
			else
			{
				g.texture.draw(pos + g.getOffset(), Color(48));
			}

			pos.x += g.xAdvance;
		}
	}
}
