// いろんなフェード

#include <Siv3D.hpp> // OpenSiv3D v0.6.11

using App = SceneManager<String>;

// フェードイン・フェードアウトの描画をするクラス
struct Fade
{
	virtual ~Fade() = default;
	virtual void fade(double t) = 0;
};

// 1. 画面全体をフェード
struct Fade1 : public Fade
{
	void fade(double t) override
	{
		Scene::Rect().draw(ColorF{ 0.1, EaseInCubic(t) });
	}
};

// 2. 円が広がる／狭まる
struct Fade2 : public Fade
{
	void fade(double t) override
	{
		const auto r = Scene::CenterF().distanceFrom(Vec2::Zero());

		Circle{ Scene::Center(), r }.drawFrame(EaseInCubic(t) * r, 0, ColorF{ 0.1 });
	}
};

// 3. くるくる
struct Fade3 : public Fade
{
	void fade(double t) override
	{
		const auto n = 3;
		const auto r0 = Scene::CenterF().distanceFrom(Vec2::Zero());

		for (int i : step(n))
		{
			const auto r = r0 / n * (i + 1);
			const auto delay = 1.0 / n * (n - 1 - i);
			const auto angle = Clamp((t - delay) / (1.0 / n) * 360_deg, 0_deg, 360_deg);

			Circle{ Scene::Center(), r }.drawArc(0_deg, angle, r0 / n, 2.0 /* 0だと隙間ができる */, ColorF{ 0.1 });
		}
	}
};

// 4. グリッド
struct Fade4 : public Fade
{
	Array<int> rectPos;
	const int size = 100;
	const int w = Scene::Width() / size;
	const int h = Scene::Height() / size;

	Fade4()
	{
		rectPos = Iota(w * h);
		Shuffle(rectPos);
	}

	void fade(double t) override
	{
		for (auto [index, pos] : Indexed(rectPos))
		{
			if (index > t * w * h) break;

			const auto x = pos % w;
			const auto y = pos / w;
			Rect{ x * size, y * size, size }.draw(ColorF{ 0.1 });
		}
	}
};

// フェード描画クラスのインスタンスをランダムに返す
auto randomFade()
{
	Array<std::function<std::unique_ptr<Fade>()>> makeFadeFuncs = {
		[]() -> std::unique_ptr<Fade> { return std::make_unique<Fade1>(); },
		[]() -> std::unique_ptr<Fade> { return std::make_unique<Fade2>(); },
		[]() -> std::unique_ptr<Fade> { return std::make_unique<Fade3>(); },
		[]() -> std::unique_ptr<Fade> { return std::make_unique<Fade4>(); },
	};

	return Sample(makeFadeFuncs)();
}

class Scene1 : public App::Scene
{
public:

	Scene1(const InitData& init)
		: IScene{ init }
	{

	}

	void update() override
	{
		if (MouseL.down())
		{
			changeScene(U"Scene2");
		}
	}

	void draw() const override
	{
		Scene::SetBackground(ColorF{ U"#679abc" });

		FontAsset(U"SceneName")(this->getState()).drawAt(Scene::Center());
	}

	void drawFadeIn(double t) const override
	{
		draw();

		m_fadeInFunction->fade(1 - t);
	}

	void drawFadeOut(double t) const override
	{
		draw();

		m_fadeOutFunction->fade(t);
	}

private:
	std::unique_ptr<Fade> m_fadeInFunction = randomFade();
	std::unique_ptr<Fade> m_fadeOutFunction = randomFade();
};

class Scene2 : public App::Scene
{
public:

	Scene2(const InitData& init)
		: IScene{ init }
	{

	}

	void update() override
	{
		if (MouseL.down())
		{
			changeScene(U"Scene1");
		}
	}

	void draw() const override
	{
		Scene::SetBackground(ColorF(U"#a167bc"));

		FontAsset(U"SceneName")(this->getState()).drawAt(Scene::Center());
	}

	void drawFadeIn(double t) const override
	{
		draw();

		m_fadeInFunction->fade(1 - t);
	}

	void drawFadeOut(double t) const override
	{
		draw();

		m_fadeOutFunction->fade(t);
	}

private:
	std::unique_ptr<Fade> m_fadeInFunction = randomFade();
	std::unique_ptr<Fade> m_fadeOutFunction = randomFade();
};

void Main_various_fade()
{
	FontAsset::Register(U"SceneName", 64, Typeface::Heavy);

	App manager;
	manager.add<Scene1>(U"Scene1");
	manager.add<Scene2>(U"Scene2");

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
