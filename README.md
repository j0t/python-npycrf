# [WIP]条件付確率場とベイズ階層言語モデルの統合による半教師あり形態素解析

修正版NPYCRFのC++実装です。

### Todo

- [x] NPYCRFの学習
- [ ] CRF単体の学習
- [ ] CRF単体の分割
- [ ] 評価

# 動作環境

- Boost 1.65
- Python 3
- C++14
- python3-config

# ビルド

以下のコマンドで`npycrf.so`が`/run/`に生成されます。

```bash
make install
```

`makefile`内のBoostのパスを環境に合わせて変更してください。

# 参考文献
- [条件付確率場とベイズ階層言語モデルの統合による半教師あり形態素解析](http://chasen.org/~daiti-m/paper/nlp2011semiseg.pdf)
- [半教師あり形態素解析 NPYCRF の修正](http://www.anlp.jp/proceedings/annual_meeting/2016/pdf_dir/D6-3.pdf)