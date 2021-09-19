#include <Siv3D.hpp> // OpenSiv3D v0.6.0
#include <list>

void Main()
{
	std::list<std::tuple<Vec2, int, int>> whites;
	Iota(32).each([&](auto) { whites.push_back(std::make_tuple(RandomVec2(Scene::Rect()), 0, Random(5, 9))); });

	Array<Vec2> bones{ 6 };
	bones[0] = Circular{ 10, 170_deg };
	bones[1] = Circular{ 18, 85_deg };
	bones[2] = Circular{ 8, -60_deg };
	bones[3] = Circular{ 10, 140_deg };
	bones[4] = Circular{ 16, 60_deg };
	bones[5] = Circular{ 7, 40_deg };

	double timeSpawned = 0;

	while (System::Update())
	{
		Scene::Rect().draw(Color(120));

		if (Scene::Time() - timeSpawned > 0.016 * 4)
		{
			whites.push_back(std::make_tuple(Vec2{ Scene::Width(), Random(Scene::Height()) }, 0, Random(5, 9)));

			timeSpawned = Scene::Time();
		}

		for (auto& w : whites)
		{
			const int t = (std::get<1>(w) / std::get<2>(w)) % 2;
			const Array<Vec2> r{ 4, Arg::generator = []() { return RandomVec2(2.0); } };
			Triangle{ Vec2{} + r[0], bones[t * 3 + 1] + r[1], bones[t * 3 + 0] + r[2] }.movedBy(std::get<0>(w)).draw(Color(240));
			Triangle{ Vec2{} + r[0], bones[t * 3 + 2] + r[3], bones[t * 3 + 0] + r[2] }.movedBy(std::get<0>(w)).draw(Color(230));
			std::get<0>(w) += Vec2{ Random(-6.0, 2.0), Random(-4.0, 4.0) };
			std::get<1>(w)++;
		}

		whites.remove_if([](auto& w) { return !Scene::Rect().intersects(std::get<0>(w)); });
	}
}

