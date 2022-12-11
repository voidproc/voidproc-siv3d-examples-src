# voidproc-siv3d-examples-src

[Siv3Dミニサンプル集 (Scrapbox)](https://scrapbox.io/voidproc-siv3d-examples/Siv3D%E3%83%9F%E3%83%8B%E3%82%B5%E3%83%B3%E3%83%97%E3%83%AB%E9%9B%86) に載せているサンプルコードです。

>Siv3D のいろいろな便利な機能を試したり、紹介したりするために作成した、ちょっとしたプログラムをサンプル集として公開しています。

## サンプル集

- あたり判定
  - [障害物に当たるまで上方へ伸びる DDP 風レーザー](voidproc-siv3d-examples-src/examples/2d-intersection/ddp_laser.cpp)
  - [異なる種類の図形に対し一括であたり判定をチェックする](voidproc-siv3d-examples-src/examples/2d-intersection/intersect.cpp)
- 画像を描く
  - [絵文字のみを使ってキラッとするアニメーション](voidproc-siv3d-examples-src/examples/texture/emoji_sparkle.cpp)
- 日付と時刻、時間
  - [Stopwatchを一括して停止・再開したり、遅く／速く進行させる（ISteadyClockの実装例）](voidproc-siv3d-examples-src/examples/time/customclock.cpp)
- フォントを使う
  - [ピクセルフォントを使用する](voidproc-siv3d-examples-src/examples/font/crispy_font.cpp)
  - [絵文字を含むテキストを文字単位で自由描画する](voidproc-siv3d-examples-src/examples/font/draw_glyphs.cpp)
  - [グリフアニメーション](voidproc-siv3d-examples-src/examples/font/glyph.cpp)
- シーンとウィンドウ
  - [低解像度のシーンを整数倍に拡大して表示](voidproc-siv3d-examples-src/examples/scene/low_resolution_scene.cpp)
- マウス・キーボード入力
  - [マウスに吸着する物体](voidproc-siv3d-examples-src/examples/mouse-keyboard/follow_cursor.cpp)
  - [押されたキー・マウスのボタン名を表示](voidproc-siv3d-examples-src/examples/mouse-keyboard/key_mouse_inputs.cpp)
- 2D レンダーステート
  - [キャラの少し前の方を2Dカメラで追従する](voidproc-siv3d-examples-src/examples/renderstates2d/camera.cpp)
  - [2D 描画位置を自由にずらす](voidproc-siv3d-examples-src/examples/renderstates2d/transform.cpp)
  - [画面外からぬるっと現れるビューポート](voidproc-siv3d-examples-src/examples/renderstates2d/window_appears.cpp)
- エフェクト
  - [マウスクリック位置にエフェクト](voidproc-siv3d-examples-src/examples/effect/click_effect.cpp)
  - [テクスチャに残像をつける](voidproc-siv3d-examples-src/examples/effect/trail.cpp)
  - [キラキラ](voidproc-siv3d-examples-src/examples/effect/twinkle.cpp)
- シーン管理
  - [いろんなフェード](voidproc-siv3d-examples-src/examples/scene-manager/various_fade.cpp)
- レンダーテクスチャ
  - [レンダーテクスチャとガウスぼかしを使ったブルーム効果](voidproc-siv3d-examples-src/examples/rendertexture/bloom.cpp)
  - [低解像度のレンダーテクスチャに描画した結果を整数倍に拡大して表示するサンプル](voidproc-siv3d-examples-src/examples/rendertexture/lowresolution.cpp)
  - [レンダーテクスチャとガウスぼかし、ピクセルシェーダを使ったレトロコンソール的表現](voidproc-siv3d-examples-src/examples/rendertexture/retro.cpp)
- 2D カスタムシェーダ
  - [テクスチャを白く点滅させるピクセルシェーダ](voidproc-siv3d-examples-src/examples/shader2d/pixelshader_white.cpp)
- 3D 形状を描く
  - [サイコロを描く](voidproc-siv3d-examples-src/examples/3d/dice.cpp)
- 未分類
  - [Base64 でエンコードした画像をソースコードに埋め込み、表示](voidproc-siv3d-examples-src/examples/misc/decodeimage.cpp)
  - [phina.js 風グリッドレイアウト](voidproc-siv3d-examples-src/examples/misc/grid_layout.cpp)
  - [指定した一連の座標に向かっていくオブジェクト](voidproc-siv3d-examples-src/examples/misc/motion.cpp)
  - [チョウのようなものの群れが飛んで行く](voidproc-siv3d-examples-src/examples/misc/whites.cpp)

## 開発環境

- Windows 11 Pro 22H2
- Visual Studio 2022 Community 17.4.2
- [OpenSiv3D](https://siv3d.github.io/ja-jp/) v0.6.6
