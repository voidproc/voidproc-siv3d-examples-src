# include <Siv3D.hpp> // OpenSiv3D v0.6.6

class GlyphsDrawer
{
	Font& font_;
	Font& emojiFont_;

	// 絵文字とみなす文字
	const String emojiList_ = U"🐣🐈🐶";

public:
	GlyphsDrawer(Font& font, Font& emojiFont)
		: font_(font)
		, emojiFont_(emojiFont)
	{
	}

	RectF region(StringView text) const
	{
		Vec2 charPos{ 0, 0 };
		Array<Vec2> points;

		for (auto [index, g] : Indexed(font_.getGlyphs(text)))
		{
			const Glyph* glyph = &g;

			Glyph glyphEmoji;
			if (emojiList_.includes(g.codePoint))
			{
				glyphEmoji = emojiFont_.getGlyph(g.codePoint);
				glyph = &glyphEmoji;
			}

			const auto rect = RectF{ charPos + glyph->getOffset(), glyph->texture.size };
			points.push_back(rect.tl());
			points.push_back(rect.br());

			charPos.x += glyph->xAdvance;
		}

		return Geometry2D::BoundingRect(points);
	}

	void draw(StringView text, const Vec2& pos) const
	{
		Vec2 charPos = pos;

		for (auto [index, g] : Indexed(font_.getGlyphs(text)))
		{
			const Glyph* glyph = &g;

			Glyph glyphEmoji;
			if (emojiList_.includes(g.codePoint))
			{
				glyphEmoji = emojiFont_.getGlyph(g.codePoint);
				glyph = &glyphEmoji;
			}

			const double t = Scene::Time() - index * 0.04;
			const double alpha = Clamp(t * 8, 0.0, 1.0);
			const double offsetY = (1 - Clamp(t * 20, 0.0, 1.0)) * 16;
			glyph->texture.draw(Math::Round(charPos + glyph->getOffset() + Vec2(0, offsetY)), AlphaF(alpha));

			charPos.x += glyph->xAdvance;
		}
	}
};

void Main_draw_glyphs()
{
	Scene::SetBackground(ColorF{ 0.2, 0.2, 0.2 });

	Font font{ 32, Typeface::Bold };
	Font emojiFont{ 32, Typeface::MonochromeEmoji };

	GlyphsDrawer glyphsDrawer{ font, emojiFont };

	while (System::Update())
	{
		const String text = U"'o') < This text includes emojis 🐣🐈🐶 !";

		const auto region = glyphsDrawer.region(text);

		const Vec2 textPos = Scene::CenterF() - Vec2(region.w / 2, 0);

		//region.movedBy(textPos).drawFrame(1.0, Palette::Lime);

		glyphsDrawer.draw(text, textPos);
	}
}
