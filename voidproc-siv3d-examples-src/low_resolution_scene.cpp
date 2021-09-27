# include <Siv3D.hpp> // OpenSiv3D v0.6.0

void Main()
{
	// シーンサイズを決定
	constexpr Size sceneSize{ 256, 256 };
	Window::Resize(sceneSize);

	// 以降はシーンサイズは変えない
	Scene::SetResizeMode(ResizeMode::Keep);

	// ウィンドウサイズを (シーンサイズ * scale) に変更
	int scale = 2;
	Window::Resize(sceneSize * scale);

	// シーンが実ウィンドウに転送される際のフィルタを変更
	Scene::SetTextureFilter(TextureFilter::Nearest);

	// テクスチャ拡大縮小時のフィルタを変更
	const ScopedRenderStates2D renderState{ SamplerState::ClampNearest };

	Scene::SetBackground(ColorF{ U"#c6efcb" });

	const Font font{ 10, FileSystem::GetFolderPath(SpecialFolder::SystemFonts) + U"msgothic.ttc", FontStyle::Bitmap };

	const Texture texture{ U"example/spritesheet/siv3d-kun-16.png" };

	while (System::Update())
	{
		Optional<int> newScale;

		if (KeyUp.down())
		{
			newScale = scale + 1;
		}
		else if (KeyDown.down())
		{
			newScale = scale - 1;
		}

		if (newScale)
		{
			scale = Clamp(*newScale, 1, 4);

			Window::Resize(sceneSize * scale);
		}

		font(U"ﾌﾚｰﾑﾊﾞｯﾌｧｻｲｽﾞ={}"_fmt(Window::GetState().frameBufferSize)).draw(2, 2 + (10 + 2) * 0, ColorF{ U"#27552d" });
		font(U"ﾊﾞｰﾁｬﾙｻｲｽﾞ   ={}"_fmt(Window::GetState().virtualSize)).draw(2, 2 + (10 + 2) * 1, ColorF{ U"#27552d" });
		font(U"ｼｰﾝｻｲｽﾞ      ={}"_fmt(Scene::Size())).draw(2, 2 + (10 + 2) * 2, ColorF{ U"#27552d" });
		font(U"ｼｰﾝｻｲｽﾞﾉ【{}倍】ﾃﾞ表示ｼﾃﾏｽ"_fmt(scale)).draw(2, 2 + (10 + 2) * 3, ColorF{ U"#27552d" });

		texture.drawAt(Scene::Center());
	}
}
