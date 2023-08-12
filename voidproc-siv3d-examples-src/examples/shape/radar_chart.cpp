// レーダーチャート
# include <Siv3D.hpp> // OpenSiv3D v0.6.11

Array<double> randomChartValues(const size_t n)
{
	return Array<double>{ n, Arg::generator = []() { return Random(); } };
}

void drawRadarChart(const size_t n, const Vec2& posCenter, const double r, const Array<double>& chartValues)
{
	const auto ngon = Shape2D::Ngon(n, 200, posCenter).asPolygon();

	// 枠

	const ColorF lineColor{ 1.0, 0.5 };

	ngon.drawFrame(2.0, lineColor);

	for (const auto& v : ngon.vertices())
	{
		Line{ posCenter, v }.draw(1.0, lineColor);
	}

	// 値をプロット

	Array<Vec2> points;

	for (auto [i, v] : Indexed(ngon.vertices()))
	{
		points << ngon.centroid() + (v - ngon.centroid()) * chartValues[i];
	}

	// プロットした点を繋いで描画

	Polygon{ points }.draw(ColorF{ Palette::Lime, 0.5 });
}

void Main_radar_chart()
{
	Scene::SetBackground(ColorF{ 0.1 });

	double nInput = 6;
	size_t n = static_cast<size_t>(nInput);

	Array<double> chartValues = randomChartValues(n);

	while (System::Update())
	{
		SimpleGUI::Slider(U"N = {}"_fmt(static_cast<size_t>(nInput)), nInput, 3.0, 8.0, Vec2{ 16, 16 });

		if (const size_t nNew = static_cast<size_t>(nInput); nNew != n)
		{
			n = nNew;
			chartValues = randomChartValues(n);
		}

		drawRadarChart(n, Scene::CenterF(), 200, chartValues);
	}
}
