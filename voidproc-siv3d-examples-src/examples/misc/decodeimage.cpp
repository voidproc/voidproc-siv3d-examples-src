// Base64 でエンコードした画像をソースコードに埋め込み、表示

#include <Siv3D.hpp> // OpenSiv3D v0.6.6

//#define ENCODE_IMAGES

String encodeFile(const FilePath& filepath)
{
	BinaryReader reader{ filepath };
	auto length = reader.size();

	String imgData;
	imgData.resize(length);
	reader.read(imgData.data(), length);

	return Base64::Encode(imgData.data(), length);
}

void Main_decodeimage()
{
#ifdef ENCODE_IMAGES
	TextWriter writer(U"encodedImages.txt");
	for (auto& file : Array<String>{ U"1.png", U"2.png", U"3.png" })
		if (FileSystem::Exists(file))
			writer.writeln(encodeFile(file));
	return;
#endif

	// Base64 でエンコードされた PNG 画像
	const String encodedImage = U"iVBORw0KGgoAAAANSUhEUgAAAEAAAAAgAgMAAADf85YXAAAACVBMVEXf/+8kSwCfv399yLhfAAAAnUlEQVQoz7XRQQrCUAwE0Al0BHddmPsETzCFfOhxFDyCB/b/Fu2v3eosH9lMBod42SUxYpfhl+ABWFINrMxASqBzaOACoFEYyFMFK40agmQFCnr24GFJzB3ACpGQYoWsYOENvAOGdM0FxEgLi8+FXGCYKrADbHCp4OiBQumB97DEbYO1S0jTYy0HVMIklXf9cxHgoVwe9JcZjmN/5wXZ+S43N2BYQwAAAABJRU5ErkJggg==";

	const Texture texture(MemoryReader(Base64::Decode(encodedImage)));

	Window::Resize(768, 512);

	while (System::Update())
	{
		const ScopedRenderStates2D sampler{ SamplerState::ClampNearest };

		for (int i : step(5))
		{
			for (int j : step(3))
			{
				texture.scaled(4).draw(j * 256, (i - 1) * 128 + 128 * Periodic::Sawtooth0_1(1s));
			}
		}
	}
}
