# include <Siv3D.hpp> // OpenSiv3D v0.6.0

String commaSeparatedInputNames(const Array<Input>& inputs)
{
	return inputs.map([](const auto& x) { return x.name(); })
		.join(U", ", U"", U"");
}

void Main()
{
	Scene::SetBackground(ColorF{ 0.0, 0.05, 0.1 });

	Font font{ 32, Typeface::Bold };

	while (System::Update())
	{
		Array<String> inputNames;

		if (const auto keyInputs = Keyboard::GetAllInputs(); not keyInputs.isEmpty())
		{
			inputNames.push_back(commaSeparatedInputNames(keyInputs));
		}

		if (const auto mouseInputs = Mouse::GetAllInputs(); not mouseInputs.isEmpty())
		{
			inputNames.push_back(commaSeparatedInputNames(mouseInputs));
		}

		font(inputNames.join(U", ", U"", U"")).drawAt(Scene::Center(), ColorF{0.95, 0.98, 1.00});
	}
}
