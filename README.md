# cwm — Claude's Window Manager

X11 向けのシンプルなタイル型ウィンドウマネージャ。
[dwm](https://dwm.suckless.org/) の思想に基づき、C言語 + Xlib で実装。

## 特徴

- **タイル / モノクル / フローティング** の3レイアウト
- **9タグ** (仮想デスクトップ)
- **ステータスバー** (上部固定、`xsetroot -name` で更新可能)
- **マルチモニター対応** (Xinerama)
- **EWMH 対応** (NetWM準拠)
- シングルファイル (`cwm.c`) + 設定ファイル (`config.h`)
- 依存: Xlib, Xinerama のみ

---

## ビルド & インストール

```bash
# 依存パッケージ (Debian/Ubuntu)
sudo apt install libx11-dev libxinerama-dev

# ビルド
make

# インストール
sudo make install

# アンインストール
sudo make uninstall
```

---

## 起動方法

`~/.xinitrc` または `~/.xsession` に追記:

```bash
# ステータスバー更新 (時計)
while true; do
    xsetroot -name "$(date +'%Y-%m-%d %H:%M:%S')"
    sleep 1
done &

exec cwm
```

または既存のWMと入れ替え (`startx` 利用):

```bash
exec cwm
```

---

## キーバインド

| キー | 動作 |
|---|---|
| `Alt + Enter` | ターミナル起動 (`st`) |
| `Alt + Shift + Enter` | ターミナル起動 (`xterm`) |
| `Alt + d` | `dmenu_run` |
| `Alt + j / k` | フォーカス移動 |
| `Alt + Space` | フォーカスウィンドウをマスターへ |
| `Alt + h / l` | マスター幅 縮小/拡大 |
| `Alt + i / -` | マスター数 増加/減少 |
| `Alt + t` | タイルレイアウト |
| `Alt + m` | モノクルレイアウト |
| `Alt + f` | フローティングレイアウト |
| `Alt + b` | バー 表示/非表示 |
| `Alt + q` | フォーカスウィンドウを閉じる |
| `Alt + Shift + Space` | フローティング切替 |
| `Alt + F11` | フルスクリーン切替 |
| `Alt + 1〜9` | タグ切替 |
| `Alt + 0` | 全タグ表示 |
| `Alt + Shift + 1〜9` | ウィンドウを指定タグへ |
| `Alt + ,` | 前のモニターへフォーカス |
| `Alt + .` | 次のモニターへフォーカス |
| `Alt + Shift + q` | **WM 終了** |

### マウス

| 操作 | 動作 |
|---|---|
| `Alt + ドラッグ (左)` | ウィンドウ移動 |
| `Alt + ドラッグ (右)` | ウィンドウリサイズ |
| `Alt + 中クリック` | フローティング切替 |
| タグクリック | タグ切替 |
| レイアウトシンボルクリック | レイアウト切替 |

---

## カスタマイズ

`config.h` を編集してリビルドするだけ:

```bash
vim config.h
make clean && make
```

主な設定項目:

```c
static const char *font       = "...";     // フォント
static const char *col_sel_bg = "#005577"; // アクセントカラー
static const unsigned int borderpx = 2;   // ボーダー幅
static const float mfact      = 0.55;     // マスター幅割合
#define MODKEY Mod1Mask                    // Alt → Mod4Mask で Super キーに
```

---

## レイアウト

```
タイルレイアウト [T]        モノクルレイアウト [M]    フローティング [F]
┌──────┬──────┐            ┌────────────┐              ╔════╗
│      │  B   │            │            │          ╔════╝    ║
│  A   ├──────┤            │     A      │          ║    ╔════╝
│(マス)│  C   │            │  (最前面)  │          ╚════╝
│      ├──────┤            │            │              (自由配置)
│      │  D   │            └────────────┘
└──────┴──────┘
```

---

## ファイル構成

```
cwm/
├── cwm.c      # WM本体 (全機能実装)
├── config.h   # 設定 (フォント, カラー, キーバインド, ルール)
├── Makefile
└── README.md
```

---

## ライセンス

MIT / ISC (dwm 由来の部分は MIT License)
