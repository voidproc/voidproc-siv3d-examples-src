// ピクセルフォントを使用する

#include <Siv3D.hpp> // OpenSiv3D v0.6.7

// 使用フォント
// ・美咲ゴシック(第2)、美咲明朝、k8x12(L,S)
//   門真 なむ 様 https://littlelimit.net/font.htm
//
// ・Nuきなこもち、Nuあんこもち
//   こかげの窓 様 http://kokagem.sakura.ne.jp/font/mochi/
//
// ・JFドットシリーズ
//   自家製フォント工房 様 http://jikasei.me/font/jf-dotfont/
//
// ・５×７ドット文字
//   ユズノカ 様 https://booth.pm/ja/items/1477300

// ※「Nuきなこもち」、「Nuあんこもち」のフォントファイルは、
//   利用条件に基づきリポジトリに収録していません。
//   各フォントファイルのダウンロードについては、次のURLを参照してください。
//   「こかげの窓」様 : http://kokagem.sakura.ne.jp/font/mochi/

void Main_crispy_font()
{
	struct FontInfo
	{
		String name;
		String assetName;
		int size;
		FontStyle style;
		FilePath path;
	};

	const auto fontFolder = FileSystem::GetFolderPath(SpecialFolder::SystemFonts);

	const Array<FontInfo> fontInfo = {
		{ U"ＭＳ ゴシック",      U"msgothic10",        10, FontStyle::Bitmap, fontFolder + U"msgothic.ttc"},
		{ U"ＭＳ ゴシック",      U"msgothic12",        12, FontStyle::Bitmap, fontFolder + U"msgothic.ttc"},
		{ U"ＭＳ 明朝",          U"msmincho12",        12, FontStyle::Bitmap, fontFolder + U"msmincho.ttc"},
		{ U"美咲ゴシック",       U"misaki_gothic",     8,  FontStyle::Bitmap, U"font/misaki_gothic.ttf"},
		{ U"美咲ゴシック第２",   U"misaki_gothic_2nd", 8,  FontStyle::Bitmap, U"font/misaki_gothic_2nd.ttf" },
		{ U"美咲明朝",           U"misaki_mincho",     8,  FontStyle::Bitmap, U"font/misaki_mincho.ttf" },
		//{ U"Nuきなこもち",       U"NuKinakoMochi",     8,  FontStyle::Bitmap, U"font/NuKinakoMochiFwCt-Reg.otf" },
		//{ U"Nuあんこもち",       U"NuAnkoMochi",       8,  FontStyle::Bitmap, U"font/NuAnkoMochiFwCt-Reg.otf" },
		{ U"JFドットk6x8",       U"JF-Dot-k6x8",       8,  FontStyle::Bitmap, U"font/JF-Dot-k6x8.ttf" },
		{ U"k8x12",              U"k8x12",             12, FontStyle::Bitmap, U"font/k8x12.ttf" },
		{ U"k8x12L",             U"k8x12L",            12, FontStyle::Bitmap, U"font/k8x12L.ttf" },
		{ U"k8x12S",             U"k8x12S",            12, FontStyle::Bitmap, U"font/k8x12S.ttf" },
		{ U"JFドットM+10",       U"JF-Dot-MPlus10",    10, FontStyle::Bitmap, U"font/JF-Dot-MPlus10.ttf" },
		{ U"JFドットK12x10",     U"JF-Dot-K12x10",     10, FontStyle::Bitmap, U"font/JF-Dot-K12x10.ttf" },
		{ U"JFドットK12",        U"JF-Dot-K12",        12, FontStyle::Bitmap, U"font/JF-Dot-K12.ttf" },
		{ U"JFドット東雲まるもじ12", U"JF-Dot-ShinonomeMaru12", 12, FontStyle::Bitmap, U"font/JF-Dot-ShinonomeMaru12.ttf" },
		{ U"５×７ドット文字",   U"pixelfont-5x7",     8,  FontStyle::Bitmap, U"font/pixelfont-5x7.ttf" },
	};

	// 上記のフォントをFontAssetに登録

	for (const auto& info : fontInfo)
	{
		FontAsset::Register(info.assetName, info.size, info.path, info.style);
	}

	// シーン・ウィンドウサイズを設定

	const Size SceneSize{ 640, 400 };

	Scene::Resize(SceneSize);
	Scene::SetResizeMode(ResizeMode::Keep);

	int scale = 2;
	Window::Resize(SceneSize * scale);

	// フォントがぼやけないためのテクスチャフィルタ、レンダーステート設定

	Scene::SetTextureFilter(TextureFilter::Nearest);

	const ScopedRenderStates2D renderState{ SamplerState::ClampNearest };

	while (System::Update())
	{
		// 背景

		Scene::SetBackground(ColorF(0.25));

		for (int y = 0; y < SceneSize.y; y += 2)
		{
			Rect{ 0, y, SceneSize.x, 1 }.draw(ColorF{ 0.0, 0.5 });
		}

		const auto padding = Vec2(16, 28);
		const auto textColor = ColorF(0.97);
		const auto lineHeight = 20;

		double maxNameWidth = 0;

		// フォントのプレビュー（フォント名）

		for (auto [i, info] : Indexed(fontInfo))
		{
			const auto text = U"{} ({})"_fmt(info.name, info.size);
			const auto region = FontAsset(info.assetName)(text).draw(padding + Vec2{ 0, lineHeight * i }, textColor);
			maxNameWidth = Max(maxNameWidth, region.w);
		}

		// フォントのプレビュー
		for (auto [i, info] : Indexed(fontInfo))
		{
			const auto text = U"あいうえお漢字全角ＡＢＣ半角ABCDEFabcdef01234.,+-*|/\\^~\"'`$@()[]{}";
			FontAsset(info.assetName)(text).draw(padding + Vec2{ maxNameWidth + 8, lineHeight * i }, textColor);
		}

		// ←→キーでウィンドウサイズを整数倍に拡縮

		if (KeyLeft.down())
		{
			scale = Max(1, scale - 1);
			Window::Resize(SceneSize * scale);
		}

		if (KeyRight.down())
		{
			scale = Min(8, scale + 1);
			Window::Resize(SceneSize * scale);
		}
	}
}
