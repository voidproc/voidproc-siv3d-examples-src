// マウスに吸着する物体

#include <Siv3D.hpp> // OpenSiv3D v0.6.7

// マウスに吸着する物体
class Item
{
	Vec2 m_pos;

public:
	Item(const Vec2 position) : m_pos(position)
	{
	}

	void update()
	{
		if (distanceFromCursor() < 100)
		{
			m_pos += (Cursor::PosF() - m_pos) * 8.0 * Scene::DeltaTime();
		}

		Circle(Arg::center = m_pos, 5.0).draw(Palette::White);
	}

	double distanceFromCursor() const
	{
		return m_pos.distanceFrom(Cursor::PosF());
	}
};

void Main_follow_cursor()
{
	Scene::SetBackground(ColorF(0.2, 0.3, 0.4));

	Array<Item> items;

	Stopwatch stopwatch(StartImmediately::Yes);

	while (System::Update())
	{
		if (stopwatch.ms() > 50)
		{
			items.emplace_back(RandomVec2(Scene::Rect()));
			stopwatch.restart();
		}

		for (auto& i : items)
		{
			i.update();
		}

		items.remove_if([](const auto& i) { return i.distanceFromCursor() < 30; });

		// Cursor
		Circle(Arg::center = Cursor::PosF(), 30).drawFrame(1.0, Alpha(128));
		Circle(Arg::center = Cursor::PosF(), 100).drawFrame(1.0, Alpha(80));

		ClearPrint();
		Print << items.size();
	}
}
