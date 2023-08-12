// テキスト入力ウィンドウ
# include <Siv3D.hpp> // OpenSiv3D v0.6.11

class TextInputWindow
{
public:
	TextInputWindow(String& text)
		: m_text{ text }, m_cursorPos{ text.size() }, m_timerNotEditing{ StartImmediately::Yes }
	{
	}

	// テキストの状態を更新（テキスト入力、カーソル移動）
	void update()
	{
		// 変換待ちのテキストがなくなったときに開始するタイマー
		if (TextInput::GetEditingText())
		{
			m_timerNotEditing.reset();
		}
		else if (not m_timerNotEditing.isRunning())
		{
			m_timerNotEditing.restart();
		}

		// カーソル移動（左右、Home、Endキー）

		if (KeyLeft.down())
		{
			m_cursorPos = (m_cursorPos == 0) ? 0 : m_cursorPos - 1;
		}

		if (KeyRight.down())
		{
			m_cursorPos = Min(m_cursorPos + 1, m_text.size());
		}

		if (KeyHome.down())
		{
			m_cursorPos = 0;
		}

		if (KeyEnd.down())
		{
			m_cursorPos = m_text.size();
		}

		// テキスト入力を処理、カーソル位置を更新
		m_cursorPos = TextInput::UpdateText(m_text, m_cursorPos, TextInputMode::AllowBackSpaceDelete);
	}

	void drawAt(double fontSize, const Vec2& posDrawAt) const
	{
		constexpr ColorF PanelColor{ 0, 0.9 };
		constexpr int PanelHeight = 168;
		constexpr ColorF TextColor{ 0.95 };
		const ColorF CursorColor{ 0.95, Periodic::Jump0_1(0.8s) };
		constexpr int CursorWidth = 4;
		constexpr ColorF EditingTextColor{ Palette::White };
		constexpr ColorF EditingTextBgColor{ Palette::Blue, 0.8 };
		constexpr ColorF HelpTextColor{ Palette::Gray };

		// パネル
		const auto panelRect = RectF{ Scene::Width(), PanelHeight }.setCenter(posDrawAt).draw(PanelColor);

		// テキスト描画位置
		const auto textRegion = textboxFont()(m_text).regionAt(fontSize, posDrawAt);

		// テキストを1文字ずつ描画

		Vec2 penPos = textRegion.tl();
		Vec2 cursorPos = penPos;

		{
			const ScopedCustomShader2D shader{ Font::GetPixelShader(textboxFont().method()) };

			for (auto [charIndex, glyph] : Indexed(textboxFont().getGlyphs(m_text)))
			{
				const auto glyphRect = glyph.texture.draw(penPos + glyph.getOffset(), TextColor);

				if (m_cursorPos == charIndex)
				{
					cursorPos = penPos;
				}

				penPos.x += glyph.xAdvance;
			}
		}

		if (m_cursorPos == m_text.size())
		{
			cursorPos = penPos;
		}

		// 未変換のテキストを描画
		if (const auto editingText = TextInput::GetEditingText(); editingText)
		{
			textboxFont()(editingText).region(cursorPos).draw(EditingTextBgColor);
			textboxFont()(editingText).draw(cursorPos, EditingTextColor);
		}

		// カーソル
		Line{ cursorPos, cursorPos.movedBy(0, textRegion.h) }.draw(CursorWidth, CursorColor);

		// 操作説明
		textboxFont()(U"[Enter], [Escape] キーで閉じる").drawAt(16, panelRect.bottomCenter().movedBy(0, -24), HelpTextColor);
	}

	StringView text() const
	{
		return m_text;
	}

	bool editing() const
	{
		return TextInput::GetEditingText() || m_timerNotEditing.sF() < 0.5;
	}


private:
	// 操作対象の文字列
	String& m_text;

	// カーソル位置
	size_t m_cursorPos;

	Stopwatch m_timerNotEditing;

	FontAsset textboxFont() const
	{
		return FontAsset(U"textbox");
	}
};

void Main_textinput_window()
{
	Scene::SetBackground(ColorF{ 0.95 });

	// Escapeキーで終了しない
	System::SetTerminationTriggers(UserAction::CloseButtonClicked);

	FontAsset::Register(U"textbox", FontMethod::MSDF, 40, Typeface::Medium);

	std::unique_ptr<TextInputWindow> textInputWindow;

	Array<String> textList;
	textList.emplace_back(U"テキスト1");
	textList.emplace_back(U"テキスト2");
	textList.emplace_back(U"テキスト3");

	while (System::Update())
	{
		Vec2 buttonPos = Scene::CenterF().movedBy(0, -64);

		for (auto& text : textList)
		{
			if (SimpleGUI::ButtonAt(text, buttonPos))
			{
				textInputWindow = std::make_unique<TextInputWindow>(text);
			}

			buttonPos.moveBy(0, 64);
		}

		if (KeyEscape.down() || KeyEnter.down())
		{
			if (textInputWindow && not textInputWindow->editing())
			{
				textInputWindow.reset();
			}
		}

		if (textInputWindow)
		{
			textInputWindow->update();
			textInputWindow->drawAt(40, Scene::CenterF());
		}
	}
}
