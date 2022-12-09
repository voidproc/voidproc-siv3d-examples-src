#include <Siv3D.hpp> // OpenSiv3D v0.6.6

void Main_lowresolution()
{
	const Size resolution(128, 72);
	const int scaling = 10;
	Window::Resize(resolution * scaling);

	const ColorF bgColor = Palette::White;
	Scene::SetBackground(bgColor);

	// RenderTextureを拡大描画時にぼやけないように：
	const ScopedRenderStates2D state(SamplerState::ClampNearest);

	// 低解像度のレンダーテクスチャ
	RenderTexture renderTexture(resolution);

	while (System::Update())
	{
		renderTexture.clear(bgColor);

		{
			const ScopedRenderTarget2D renderTarget(renderTexture);

			RectF(resolution * 0.5 - Vec2(20, 20), 40, 40).rotated(Scene::Time() * 0.3).draw(Palette::Black);
			Circle(Cursor::PosF() / scaling, 10).draw(ColorF(0.0, 0.5));
		}

		renderTexture.scaled(scaling).draw();
	}
}
