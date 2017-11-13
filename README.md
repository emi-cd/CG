# OpenGLを使用した三次元プログラミング  

## 実行の仕方
- 動きを確認した環境  
    OS X El Capitan ver 10.11.6
- 実行コマンド
    gcc -framework GLUT -framework OpenGL main.cpp  
    これだと *'glutInitWindowSize' is deprecated: first deprecated in macOS 10.9* のような、関数glutInitWindowSizeは廃止予定ですよ!といったwarningだったりがたくさん出てしまうので、**cc main1.cpp -framework GLUT -framework OpenGL -mmacosx-version-min=10.8** として実行。

## プログラムについて
- test.cpp
  練習のために作ったもの。[こちらのページ](https://tokoik.github.io/opengl/libglut.html)を参考に作成。
