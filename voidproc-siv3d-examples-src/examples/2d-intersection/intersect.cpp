#include <Siv3D.hpp> // OpenSiv3D v0.6.6
#include <variant>

void Main_intersect()
{
	Scene::SetBackground(Palette::Slategray);

	const Vec2 pos{ 800 / 2, 600 / 2 };

	Array<std::variant<Circle, RectF, Quad, Triangle>> shapes;
	shapes.push_back(Circle(pos, 50));  //Circle
	shapes.push_back(RectF(pos.movedBy(-130, -130), 100, 200));  //RectF
	shapes.push_back(RectF(pos.movedBy(0, -100), 120, 100).rotated(45_deg));  //Quad
	shapes.push_back(Triangle(pos, pos.movedBy(140, 0), pos.movedBy(0, 120)));  //Triangle

	while (System::Update())
	{
		for (auto& shape : shapes)
		{
			std::visit([](auto s) {
				if (Geometry2D::Intersect(Cursor::PosF(), s)) {
					s.draw(Palette::Orange);
				}
				s.drawFrame(3);
			}, shape);
		}
	}
}
