﻿# pragma once

// ★ 図形を描く ( examples/shape/ )
void Main_radar_chart(); // radar_chart.cpp : レーダーチャート

// ★ 動きを作る ( examples/animation/ )
void Main_easing_editor(); // easing_editor.cpp : イージングエディタ

// ★ あたり判定 ( examples/2d-intersection/ )
void Main_ddp_laser(); // ddp_laser.cpp : 障害物に当たるまで上方へ伸びる DDP 風レーザー
void Main_intersect(); // intersect.cpp : 異なる種類の図形に対し一括であたり判定をチェックする

// ★ 画像を描く ( examples/texture/ )
void Main_emoji_sparkle(); // emoji_sparkle.cpp : 絵文字のみを使ってキラッとするアニメーション

// ★ 日付と時刻、時間 ( examples/time/ )
void Main_customclock(); // customclock.cpp : Stopwatchを一括して停止・再開したり、遅く／速く進行させる（ISteadyClockの実装例）

// ★ フォントを使う ( examples/font/ )
void Main_crispy_font(); // crispy_font.cpp : ピクセルフォントを使用する
void Main_draw_glyphs(); // draw_glyphs.cpp : 絵文字を含むテキストを文字単位で自由描画する
void Main_glyph(); // glyph.cpp : グリフアニメーション

// ★ シーンとウィンドウ ( examples/scene/ )
void Main_low_resolution_scene(); // low_resolution_scene.cpp : 低解像度のシーンを整数倍に拡大して表示

// ★ マウス・キーボード入力 ( examples/mouse-keyboard/ )
void Main_follow_cursor(); // follow_cursor.cpp : マウスに吸着する物体
void Main_key_mouse_inputs(); // key_mouse_inputs.cpp : 押されたキー・マウスのボタン名を表示
void Main_textinput_window(); // textinput_window.cpp : テキスト入力ウィンドウ

// ★ 2D レンダーステート ( examples/renderstates2d/ )
void Main_camera(); // camera.cpp : キャラの少し前の方を2Dカメラで追従する
void Main_transform(); // transform.cpp : 2D 描画位置を自由にずらす
void Main_window_appears(); // window_appears.cpp : 画面外からぬるっと現れるビューポート

// ★ エフェクト ( examples/effect/ )
void Main_click_effect(); // click_effect.cpp : マウスクリック位置にエフェクト
void Main_trail(); // trail.cpp : テクスチャに残像をつける
void Main_twinkle(); // twinkle.cpp : キラキラ

// ★ シーン管理 ( examples/scene-manager/ )
void Main_various_fade(); // various_fade.cpp : いろんなフェード

// ★ レンダーテクスチャ ( examples/rendertexture/ )
void Main_bloom(); // bloom.cpp : レンダーテクスチャとガウスぼかしを使ったブルーム効果
void Main_lowresolution(); // lowresolution.cpp : 低解像度のレンダーテクスチャに描画した結果を整数倍に拡大して表示するサンプル
void Main_retro(); // retro.cpp : レンダーテクスチャとガウスぼかし、ピクセルシェーダを使ったレトロコンソール的表現

// ★ 2D カスタムシェーダ ( examples/shader2d/ )
void Main_pixelshader_white(); // pixelshader_white.cpp : テクスチャを白く点滅させるピクセルシェーダ

// ★ 3D 形状を描く ( examples/3d/ )
void Main_dice(); // dice.cpp : サイコロを描く

// ★ 未分類 ( examples/misc/ )
void Main_decodeimage(); // decodeimage.cpp : Base64 でエンコードした画像をソースコードに埋め込み、表示
void Main_grid_layout(); // grid_layout.cpp : phina.js 風グリッドレイアウト
void Main_motion(); // motion.cpp : 指定した一連の座標に向かっていくオブジェクト
void Main_whites(); // whites.cpp : チョウのようなものの群れが飛んで行く
void Main_tmp(); // _tmp.cpp : //

