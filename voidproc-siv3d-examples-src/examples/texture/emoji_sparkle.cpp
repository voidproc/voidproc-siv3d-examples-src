// 絵文字のみを使ってキラッとするアニメーション

#include <Siv3D.hpp> // OpenSiv3D v0.6.6

void Main_emoji_sparkle()
{
	Scene::SetBackground(Color(40, 50, 80));

	const Array<Texture> texture{
		Texture{ Emoji{ U"🌕" } },
		Texture{ Emoji{ U"⭐️" } },
		Texture{ Emoji{ U"🌟" } },
		Texture{ Emoji{ U"✨" } }, };

	Array<std::tuple<Point, double>> sparkle;

	while (System::Update())
	{
		if (Scene::Rect().leftClicked())
		{
			sparkle.push_back(std::make_tuple(Cursor::Pos(), Scene::Time()));
		}

		sparkle.each([&](const auto& f) {
			const double elapsed = Scene::Time() - std::get<1>(f);
			const int index = (int)(elapsed / 0.04);

			if (index < texture.size())
			{
				texture[index].drawAt(std::get<0>(f));
			}
		});

		sparkle.remove_if([](const auto& f) { return Scene::Time() - std::get<1>(f) >= 0.2; });
	}
}
