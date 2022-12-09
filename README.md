# voidproc-siv3d-examples-src

[Siv3Dミニサンプル集 (Scrapbox)](https://scrapbox.io/voidproc-siv3d-examples/Siv3D%E3%83%9F%E3%83%8B%E3%82%B5%E3%83%B3%E3%83%97%E3%83%AB%E9%9B%86) に載せているサンプルコードです。

- あたり判定
  - [障害物に当たるまで上方へ伸びる DDP 風レーザー](voidproc-siv3d-examples-src/examples/2d-intersection/ddp_laser.cpp)
  - [異なる種類の図形に対し一括であたり判定をチェックする](voidproc-siv3d-examples-src/examples/2d-intersection/intersect.cpp)
- 画像を描く
  - [絵文字のみを使ってキラッとするアニメーション](voidproc-siv3d-examples-src/examples/texture/emoji_sparkle.cpp)
- 日付と時刻、時間
  - [Stopwatchを一括して停止・再開したり、遅く／速く進行させる（ISteadyClockの実装例）](voidproc-siv3d-examples-src/examples/time/customclock.cpp)
- フォントを使う
  - [グリフアニメーション](voidproc-siv3d-examples-src/examples/font/glyph.cpp)
  - [絵文字を含むテキストを文字単位で自由描画する](voidproc-siv3d-examples-src/examples/font/draw_glyphs.cpp)
- シーンとウィンドウ
  - [低解像度のシーンを整数倍に拡大して表示](voidproc-siv3d-examples-src/examples/scene/low_resolution_scene.cpp)
- マウス・キーボード入力
  - [マウスに吸着する物体](voidproc-siv3d-examples-src/examples/mouse-keyboard/follow_cursor.cpp)
  - [押されたキー・マウスのボタン名を表示](voidproc-siv3d-examples-src/examples/mouse-keyboard/key_mouse_inputs.cpp)
- 2D レンダーステート
  - [2D 描画位置を自由にずらす](voidproc-siv3d-examples-src/examples/renderstates2d/transform.cpp)
  - [画面外からぬるっと現れるビューポート](voidproc-siv3d-examples-src/examples/renderstates2d/window_appears.cpp)
  - [キャラの少し前の方を2Dカメラで追従する](voidproc-siv3d-examples-src/examples/renderstates2d/camera.cpp)
- エフェクト
  - [キラキラ](voidproc-siv3d-examples-src/examples/effect/twinkle.cpp)
  - [テクスチャに残像をつける](voidproc-siv3d-examples-src/examples/effect/trail.cpp)
  - [マウスクリック位置にエフェクト](voidproc-siv3d-examples-src/examples/effect/click_effect.cpp)
- レンダーテクスチャ
  - [低解像度のレンダーテクスチャに描画した結果を整数倍に拡大して表示するサンプル](voidproc-siv3d-examples-src/examples/rendertexture/lowresolution.cpp)
  - [レンダーテクスチャとガウスぼかしを使ったブルーム効果](voidproc-siv3d-examples-src/examples/rendertexture/bloom.cpp)
  - [レンダーテクスチャとガウスぼかし、ピクセルシェーダを使ったレトロコンソール的表現](voidproc-siv3d-examples-src/examples/rendertexture/retro.cpp)
- 2D カスタムシェーダ
  - [テクスチャを白く点滅させるピクセルシェーダ](voidproc-siv3d-examples-src/examples/shader2d/pixelshader_white.cpp)
- 3D 形状を描く
  - [サイコロを描く](voidproc-siv3d-examples-src/examples/3d/dice.cpp)
- 未分類
  - [チョウのようなものの群れが飛んで行く](voidproc-siv3d-examples-src/examples/misc/whites.cpp)
  - [Base64 でエンコードした画像をソースコードに埋め込み、表示](voidproc-siv3d-examples-src/examples/misc/decodeimage.cpp)
  - [phina.js 風グリッドレイアウト](voidproc-siv3d-examples-src/examples/misc/grid_layout.cpp)
  - [指定した一連の座標に向かっていくオブジェクト](voidproc-siv3d-examples-src/examples/misc/motion.cpp)
