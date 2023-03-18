// 障害物に当たるまで上方へ伸びる DDP 風レーザー

#include <Siv3D.hpp> // OpenSiv3D v0.6.7

void Main_ddp_laser()
{
	Scene::SetBackground(Color{ 255, 237, 216 });

	const Texture textureFire{ U"🔥"_emoji };
	const Texture textureCol{ U"💥"_emoji };

	// 敵や障害物などのレーザーがあたるもの
	Array<Circle> enemies{ Circle{50}, Circle{40}, Circle{70} };

	while (System::Update())
	{
		// 敵を動かす／描画
		for (int i : step(enemies.size()))
		{
			const float period = 1.2 + i * 0.4;
			enemies[i].setCenter(Scene::CenterF().x + (120 + i * 80) * (Periodic::Sine0_1(SecondsF(period), Scene::Time() + i * period / 3) - 0.5) * 2, 100);
			enemies[i].draw(Color{ 255, 193, 118 });
		}

		// マウス位置の上方にレーザーが伸びる
		// いま nearest まで伸びてる
		const auto cursorPos = Cursor::PosF();
		Vec2 nearest = cursorPos + Vec2{ 0, -1000 };

		for (const auto& enemy : enemies)
		{
			if (cursorPos.intersects(enemy))
			{
				// レーザー発射点がめりこんでいれば、レーザーは伸びない
				nearest = cursorPos;
			}
			else
			{
				// めりこんでいないので、マウス位置に一番近い衝突点までレーザーが伸びる
				Line{ cursorPos, nearest }.intersectsAt(enemy).value_or(Array<Vec2>{}).each([&](const auto& pos) {
					if (cursorPos.distanceFrom(pos) < cursorPos.distanceFrom(nearest)) {
						nearest = pos;
					};
				});
			}
		}

		Line{ cursorPos, nearest }.draw(12 + 8 * Periodic::Sine0_1(SecondsF(0.5s)), Palette::Darkorange); //レーザー本体
		textureFire.resized(70 + 8 * Periodic::Sine0_1(0.25s)).rotated(-20_deg + 40_deg * Periodic::Sine0_1(0.4s)).drawAt(cursorPos);  //発射点
		textureCol.resized(100 + 30 * Periodic::Sine0_1(0.1s)).drawAt(nearest); //照射先
	}
}
