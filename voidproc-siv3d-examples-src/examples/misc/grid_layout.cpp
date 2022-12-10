// phina.js 風グリッドレイアウト

# include <Siv3D.hpp> // OpenSiv3D v0.6.6

class GridLayout
{
	int m_cols;
	int m_rows;
	RectF m_targetRect;

	double offsetX_(const double offset) const
	{
		return offset * m_targetRect.w / m_cols;
	}

	double offsetY_(const double offset) const
	{
		return offset * m_targetRect.h / m_rows;
	}

public:
	GridLayout(const int cols = 16, const int rows = 16, const RectF& targetRect = Scene::Rect()) : m_cols(cols), m_rows(rows), m_targetRect(targetRect)
	{
	}

	double x(const double pos) const
	{
		return m_targetRect.x + offsetX_(pos);
	}

	double y(const double pos) const
	{
		return m_targetRect.y + offsetY_(pos);
	}

	Vec2 pos(const double posX, const double posY) const
	{
		return Vec2(x(posX), y(posY));
	}

	double w(const double size) const
	{
		return size * m_targetRect.w / m_cols;
	}

	double h(const double size) const
	{
		return size * m_targetRect.h / m_rows;
	}

	Vec2 size(const double width, const double height) const
	{
		return Vec2(w(width), h(height));
	}

	RectF region(const double posX, const double posY, const double width, const double height) const
	{
		return RectF(pos(posX, posY), size(width, height));
	}

	Vec2 center(const double offsetX = 0, const double offsetY = 0) const
	{
		return pos(m_cols / 2 + offsetX, m_rows / 2 + offsetY);
	}

	int cols() const
	{
		return m_cols;
	}

	int rows() const
	{
		return m_rows;
	}
};

void Main_grid_layout()
{
	Scene::SetBackground(Palette::Azure);

	GridLayout gridLayout;

	while (System::Update())
	{
		// グリッドを描画
		for (auto& p : step(Size(gridLayout.cols() + 1, gridLayout.rows() + 1)))
		{
			Shape2D::Cross(5.0, 2.0, gridLayout.pos(p.x, p.y), 45_deg).draw(Palette::Paleturquoise);
		}

		Scene::Rect().top().movedBy(0, Scene::Rect().h / 2).draw(2, Palette::Paleturquoise);
		Scene::Rect().left().movedBy(Scene::Rect().w / 2, 0).draw(2, Palette::Paleturquoise);


		// x(), y() でグリッド単位での位置を指定
		// w(), h() でグリッド単位でのサイズを指定
		RectF(gridLayout.x(0), gridLayout.y(1), gridLayout.w(4), gridLayout.h(2))
			.rounded(3).draw(Color(Palette::Lightseagreen, 168)).drawFrame(1, 1, Palette::Lightseagreen);

		// pos() でグリッド単位での位置を指定
		// size() でグリッド単位でのサイズを指定
		RectF(gridLayout.pos(4, 3), gridLayout.size(4, 2))
			.rounded(3).draw(Color(Palette::Lightseagreen, 168)).drawFrame(1, 1, Palette::Lightseagreen);

		// region() でグリッド単位での位置・サイズを指定
		gridLayout.region(8, 5, 4, 2)
			.rounded(3).draw(Color(Palette::Lightseagreen, 168)).drawFrame(1, 1, Palette::Lightseagreen);

		gridLayout.region(12, 7, 4, 2)
			.rounded(3).draw(Color(Palette::Lightseagreen, 168)).drawFrame(1, 1, Palette::Lightseagreen);

		// center() で画面中央からグリッド単位でオフセットした位置を指定
		Range(-1, 1).each([&](const int i) {
			RectF(gridLayout.size(4, 4)).setCenter(gridLayout.center(i * 5, 4))
				.rounded(3).draw(Color(Palette::Lightseagreen, 168)).drawFrame(1, 1, Palette::Lightseagreen);
		});
	}
}
