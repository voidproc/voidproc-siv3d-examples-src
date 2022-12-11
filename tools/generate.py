# Main.cpp, examples/examples.h を生成する
# tools/ から実行されることを想定

import os
import re

# ファイルから関数定義 'void Main_****()' と、ファイル先頭のコメントを抽出
def extract_example_info(filepath):
    main_func_def = ''
    comment = ''

    with open(filepath, 'r', encoding='utf_8_sig') as file:
        lines = [line.strip() for line in file.readlines()]

        if len(lines) > 0:
            comment = lines[0].replace('// ', '')

        for line in lines:
            if re.search('^void Main_.+\(\)', line):
                main_func_def = line
                break

    return (main_func_def, comment)


sections = {
    '2d-intersection': { 'desc': 'あたり判定', 'examples': [] },
    'texture': { 'desc': '画像を描く', 'examples': [] },
    'time': { 'desc': '日付と時刻、時間', 'examples': [] },
    'font': { 'desc': 'フォントを使う', 'examples': [] },
    'scene': { 'desc': 'シーンとウィンドウ', 'examples': [] },
    'mouse-keyboard': { 'desc': 'マウス・キーボード入力', 'examples': [] },
    'renderstates2d': { 'desc': '2D レンダーステート', 'examples': [] },
    'effect': { 'desc': 'エフェクト', 'examples': [] },
    'scene-manager': { 'desc': 'シーン管理', 'examples': [] },
    'rendertexture': { 'desc': 'レンダーテクスチャ', 'examples': [] },
    'shader2d': { 'desc': '2D カスタムシェーダ', 'examples': [] },
    '3d': { 'desc': '3D 形状を描く', 'examples': [] },
    'misc': { 'desc': '未分類', 'examples': [] },
}

os.chdir('../voidproc-siv3d-examples-src/examples')

for dirpath, dirnames, filenames in os.walk('./'):
    for filename in filenames:
        if re.search('\.cpp$', filename):
            cpp_path = dirpath + '/' + filename
            main_func_def, comment = extract_example_info(cpp_path)
            section = dirpath.replace('./', '')
            sections[section]['examples'].append((filename, main_func_def, comment))


# examples/examples.h を出力

examples_path = 'examples.h'

with open(examples_path, 'w', encoding='utf_8_sig') as file_examples_h:
    file_examples_h.write('# pragma once\n\n')

    for section in sections:
        section_desc = sections[section]["desc"]
        file_examples_h.write(f'// ★ {section_desc} ( examples/{section}/ )\n')

        for filename, main_func_def, comment in sections[section]['examples']:
            file_examples_h.write(f'{main_func_def}; // {filename} : {comment.strip(" ")}\n')
        
        file_examples_h.write('\n')


# Main.cpp を出力

main_cpp_path = '../Main.cpp'

with open(main_cpp_path, 'w', encoding='utf_8_sig') as file_main_cpp:
    file_main_cpp.write('# include <Siv3D.hpp>\n\n# include "examples/examples.h"\n\nvoid Main()\n{\n\t// 実行したいサンプルの行をコメントアウトしてください\n\n')

    for section in sections:
        section_desc = sections[section]["desc"]
        file_main_cpp.write(f'\t// ★ {section_desc} ( examples/{section}/ )\n')

        for filename, main_func_def, comment in sections[section]['examples']:
            file_main_cpp.write(f'\t//{main_func_def.replace("void ", "")}; // {filename} : {comment.strip(" ")}\n')
        
        file_main_cpp.write('\n')
        
    file_main_cpp.write('}\n')
    

# README.partial.md を出力

readme_path = '../../README.partial.md'

with open(readme_path, 'w', encoding='utf_8_sig') as file_readme:
    for section in sections:
        section_desc = sections[section]['desc']
        file_readme.write(f'- {section_desc}\n')

        for filename, main_func_def, comment in sections[section]['examples']:
            if filename == '_tmp.cpp':
                continue
            
            src_path = f'voidproc-siv3d-examples-src/examples/{section}/{filename}'
            file_readme.write(f'  - [{comment}]({src_path})\n')
